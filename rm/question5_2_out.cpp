//#include <opencv2/opencv.hpp>
//#include <iostream>
//#include <cmath>
//
//using namespace cv;
//using namespace std;
//
//int main() {
//    // 1. 读取图像
//    Mat img = imread("D:/images/apple.png"); // 替换为你的图像路径
//    if (img.empty()) {
//        cout << "无法读取图像！" << endl;
//        return -1;
//    }
//
//    // 2. 转换为 HSV 颜色空间（更适合颜色分割）
//    Mat hsv;
//    cvtColor(img, hsv, COLOR_BGR2HSV);
//
//    // 3. 定义苹果的颜色区间（红色+黄色）
//    Scalar lower_red1 = Scalar(0, 40, 40);    // 红色区间1（H:0-10）
//    Scalar upper_red1 = Scalar(10, 255, 255);
//    Scalar lower_red2 = Scalar(170, 40, 40);   // 红色区间2（H:170-180）
//    Scalar upper_red2 = Scalar(180, 255, 255);
//    Scalar lower_yellow = Scalar(20, 40, 40);  // 黄色区间（H:20-35）
//    Scalar upper_yellow = Scalar(35, 255, 255);
//
//    // 4. 生成各颜色区间的掩码并合并
//    Mat mask_red1, mask_red2, mask_yellow, mask;
//    inRange(hsv, lower_red1, upper_red1, mask_red1);
//    inRange(hsv, lower_red2, upper_red2, mask_red2);
//    inRange(hsv, lower_yellow, upper_yellow, mask_yellow);
//    mask = mask_red1 + mask_red2 + mask_yellow; // 合并红、黄掩码
//
//    // 5. 形态学闭运算：填充苹果内部空隙，连接不连续区域
//    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(7, 7));
//    morphologyEx(mask, mask, MORPH_CLOSE, kernel);
//
//    // 6. 检测轮廓
//    vector<vector<Point>> contours;
//    vector<Vec4i> hierarchy;
//    findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//
//    // 7. 筛选“圆形度最高”的轮廓（苹果近似圆形）
//    Mat result = img.clone();
//    int bestIdx = -1;
//    double bestCircularity = 0;
//
//    for (size_t i = 0; i < contours.size(); i++) {
//        double area = contourArea(contours[i]);
//        if (area < 100) continue; // 过滤极小轮廓（噪点）
//
//        double perimeter = arcLength(contours[i], true);
//        double circularity = 4 * CV_PI * area / (perimeter * perimeter); // 圆形度公式
//
//        if (circularity > bestCircularity) {
//            bestCircularity = circularity;
//            bestIdx = i;
//        }
//    }
//
//    // 8. 绘制苹果轮廓与矩形框
//    if (bestIdx != -1) {
//        drawContours(result, contours, bestIdx, Scalar(0, 255, 0), 2); // 绿色轮廓
//        Rect bbox = boundingRect(contours[bestIdx]);
//        rectangle(result, bbox, Scalar(0, 0, 255), 2);               // 红色矩形框
//    }
//
//    // 9. 显示与保存结果
//    imshow("颜色掩码", mask);
//    imshow("最终结果", result);
//    imwrite("apple_full_shape.jpg", result);
//
//    waitKey(0);
//    destroyAllWindows();
//    return 0;
//}