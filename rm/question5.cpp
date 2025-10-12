//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main() {
//    // 1. 读取图像
//    Mat img = imread("D:/images/apple.png"); // 替换为你的苹果图片路径
//    if (img.empty()) {
//        cout << "无法读取图像，请检查路径！" << endl;
//        return -1;
//    }
//
//    // 2. 转换为HSV颜色空间（更适合颜色分割）
//    Mat hsv;
//    cvtColor(img, hsv, COLOR_BGR2HSV);
//
//    // 3. 定义红色的HSV范围（红色在HSV中是两个区间：0-10和170-180）
//    Scalar lower_red1 = Scalar(0, 40, 40);   // 低H、S、V阈值
//    Scalar upper_red1 = Scalar(10, 255, 255); // 高H、S、V阈值
//    Scalar lower_red2 = Scalar(170, 40, 40);
//    Scalar upper_red2 = Scalar(180, 255, 255);
//
//    // 4. 生成红色区域的二值掩码
//    Mat mask1, mask2, mask;
//    inRange(hsv, lower_red1, upper_red1, mask1); // 筛选第一个红色区间
//    inRange(hsv, lower_red2, upper_red2, mask2); // 筛选第二个红色区间
//    mask = mask1 + mask2; // 合并两个区间的掩码
//
//    // 5. 形态学操作优化掩码（去噪点、填空洞）
//    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(5, 5)); // 5×5椭圆形结构元素
//    morphologyEx(mask, mask, MORPH_OPEN, kernel);  // 开运算：先腐蚀后膨胀（去小噪点）
//    morphologyEx(mask, mask, MORPH_CLOSE, kernel); // 闭运算：先膨胀后腐蚀（填小空洞）
//
//    // 6. 查找轮廓
//    vector<vector<Point>> contours;
//    vector<Vec4i> hierarchy;
//    findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//
//    // 7. 筛选面积最大的轮廓（假设为苹果）
//    int maxAreaIdx = -1;
//    double maxArea = 0;
//    for (size_t i = 0; i < contours.size(); i++) {
//        double area = contourArea(contours[i]);
//        if (area > maxArea) {
//            maxArea = area;
//            maxAreaIdx = i;
//        }
//    }
//
//    // 8. 绘制轮廓与矩形框
//    Mat result = img.clone(); // 复制原图用于绘制结果
//    if (maxAreaIdx != -1) {
//        drawContours(result, contours, maxAreaIdx, Scalar(0, 255, 0), 2); // 绘制绿色轮廓
//        Rect bbox = boundingRect(contours[maxAreaIdx]); // 计算最小包围矩形
//        rectangle(result, bbox, Scalar(0, 0, 255), 2);   // 绘制红色矩形框
//    }
//
//    // 9. 显示与保存结果
//    imshow("Original", img);
//    imshow("Mask", mask);
//    imshow("Result", result);
//    imwrite("apple_result.jpg", result); // 保存结果到文件
//
//    waitKey(0);   // 等待按键
//    destroyAllWindows(); // 关闭所有窗口
//    return 0;
//}