// 识别视频红色装甲板
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <chrono>
using namespace cv;
using namespace std;
using namespace chrono;

// 灯条结构体
struct LightBar {
    RotatedRect rrect; // 旋转矩形
    Point center;      // 中心点
    double length;     // 长边长度
};

// 装甲板结构体
struct Armor {
    RotatedRect rect; // 装甲板旋转矩形
    Point center;     // 中心点
};

// 筛选灯条函数
vector<LightBar> findLightBars(const Mat& mask) {
    vector<vector<Point>> contours;
    findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<LightBar> lightBars;
    for (const auto& contour : contours) {
        if (contour.size() < 4) continue; // 过滤过小轮廓

        // 拟合旋转矩形（适应倾斜灯条）
        RotatedRect rrect = minAreaRect(contour);
        float length = max(rrect.size.width, rrect.size.height); // 长边
        float width = min(rrect.size.width, rrect.size.height);  // 短边

        // 放宽筛选条件（适应左侧小灯条）
        if (length / width < 2 || length < 15 || width < 3)
            continue; // 长宽比>2，长度≥15，宽度≥3

        lightBars.push_back({ rrect, (Point)rrect.center, length });
    }
    return lightBars;
}

// 匹配装甲板函数（放宽条件）
vector<Armor> matchArmors(const vector<LightBar>& lightBars) {
    vector<Armor> armors;
    for (size_t i = 0; i < lightBars.size(); i++) {
        for (size_t j = i + 1; j < lightBars.size(); j++) {
            const LightBar& lb1 = lightBars[i];
            const LightBar& lb2 = lightBars[j];

            // 条件1：角度差≤25°（允许更不平行）
            if (abs(lb1.rrect.angle - lb2.rrect.angle) > 25) continue;

            // 条件2：长度比≥0.3（允许长度差异更大）
            double lengthRatio = min(lb1.length, lb2.length) / max(lb1.length, lb2.length);
            if (lengthRatio < 0.3) continue;

            // 条件3：中心距为灯条长度的0.7~4倍（允许间距更灵活）
            double centerDist = norm(lb1.center - lb2.center);
            double avgLength = (lb1.length + lb2.length) / 2;
            if (centerDist / avgLength < 0.7 || centerDist / avgLength > 4.0) continue;

            // 生成装甲板矩形
            Point2f pts[8];
            lb1.rrect.points(pts);
            lb2.rrect.points(pts + 4);
            Point2f armorPts[4] = { pts[0], pts[2], pts[4], pts[6] };
            RotatedRect armorRect = minAreaRect(Mat(4, 1, CV_32FC2, armorPts));

            armors.push_back({ armorRect, armorRect.center });
        }
    }
    return armors;
}

int main() {
    // 1. 读取本地视频
    VideoCapture cap("D:/images/装甲板 - 红.mp4"); // 替换为你的视频路径
    if (!cap.isOpened()) {
        cerr << "无法打开视频！" << endl;
        return -1;
    }

    Mat frame, resizedFrame, hsv, mask, mask1, mask2;
    // 红色HSV阈值（放宽饱和度/亮度下限，适应左侧暗灯条）
    Scalar lowerRed1(0, 60, 60), upperRed1(10, 255, 255);   // 红区间1
    Scalar lowerRed2(160, 60, 60), upperRed2(180, 255, 255); // 红区间2

    // 形态学核（5x5增强去噪和补全能力）
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    int frameCount = 0; // 帧数

    //捕捉一帧 1.  检查视频帧是否为空，如果为空则跳出循环
    //         2.  将当前帧的尺寸缩小一半，宽度和高度都除以2
    while (cap.read(frame)) {
        frameCount++;
        if (frame.empty()) break;

        // 缩小图像（1/2尺寸）
        resize(frame, resizedFrame, Size(frame.cols / 2, frame.rows / 2));

        // 计时开始
        auto start = high_resolution_clock::now();

        // 1. BGR转HSV
        cvtColor(resizedFrame, hsv, COLOR_BGR2HSV);

        // 2. 提取红色区域掩码
        inRange(hsv, lowerRed1, upperRed1, mask1);
        inRange(hsv, lowerRed2, upperRed2, mask2);
        mask = mask1 | mask2; // 合并红色区域

        // 3. 形态学处理（去噪+补全）
        morphologyEx(mask, mask, MORPH_OPEN, kernel);  // 开运算去噪
        morphologyEx(mask, mask, MORPH_CLOSE, kernel); // 闭运算补全

        // 4. 筛选灯条
        vector<LightBar> lightBars = findLightBars(mask);

        // 5. 匹配装甲板
        vector<Armor> armors = matchArmors(lightBars);

        // 6. 绘制结果（灯条+装甲板+中心点）
        Mat show = resizedFrame.clone();

        // 绘制灯条（可选：用于调试灯条识别效果）
        for (const auto& lb : lightBars) {
            Point2f pts[4];
            lb.rrect.points(pts);
            for (int i = 0; i < 4; i++) {
                line(show, pts[i], pts[(i + 1) % 4], Scalar(255, 0, 0), 2); // 蓝色线标记灯条
            }
        }

        // 绘制装甲板轮廓和中心点（核心：修复原代码错误，在装甲板循环中使用armor）
        for (const auto& armor : armors) {
            // 绘制装甲板轮廓
            Point2f pts[4];
            armor.rect.points(pts);
            for (int i = 0; i < 4; i++) {
                line(show, pts[i], pts[(i + 1) % 4], Scalar(0, 255, 0), 2); // 绿色线标记装甲板
            }
            // 绘制装甲板中心点（红色实心点）
            circle(show, armor.center, 3, Scalar(0, 0, 255), -1);
        }

        // 7. 显示耗时和帧计数
        auto end = high_resolution_clock::now();
        double elapsedMs = duration_cast<microseconds>(end - start).count() / 1000.0;
        putText(show, "耗时: " + to_string(elapsedMs) + " ms",
            Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 255), 2); // 黄色文字
        putText(show, "帧号: " + to_string(frameCount),
            Point(10, 60), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 255), 2); // 黄色文字

        // 8. 显示结果
        imshow("装甲板识别结果", show);
        if (waitKey(30) == 27) break; // ESC键退出
    }

    // 释放资源
    cap.release();
    destroyAllWindows();
    return 0;
}