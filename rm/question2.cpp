//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main() {
//    // 1. 读取原始图像（替换为你的图片路径，如 "shapes.jpg"）
//    Mat src = imread("D:/images/shapes.png");
//    if (src.empty()) {
//        cout << "图片读取失败！请检查路径。" << endl;
//        return -1;
//    }
//
//    // 调整图像尺寸为 1280*720
//    resize(src, src, Size(1280, 720));
//
//    // 2. 颜色空间转换：BGR → HSV（HSV 更适合颜色分割）
//    Mat hsv;
//    cvtColor(src, hsv, COLOR_BGR2HSV);
//
//    // 3. 定义“红色”在 HSV 中的范围（红色分**低色相**和**高色相**两个区间）
//    Scalar red_lower1 = Scalar(0, 100, 100);   // 低色相红色的下限
//    Scalar red_upper1 = Scalar(10, 255, 255);  // 低色相红色的上限
//    Scalar red_lower2 = Scalar(170, 100, 100); // 高色相红色的下限
//    Scalar red_upper2 = Scalar(180, 255, 255); // 高色相红色的上限
//
//    // 4. 提取红色区域（生成二值图：红色为白，其他为黑）
//    Mat red_mask1, red_mask2, red_mask;
//    inRange(hsv, red_lower1, red_upper1, red_mask1); // 检测低色相红色
//    inRange(hsv, red_lower2, red_upper2, red_mask2); // 检测高色相红色
//    red_mask = red_mask1 | red_mask2;               // 合并两个红色区间的结果
//
//    // 5. Canny 边缘检测（从红色二值图中提取边缘）
//    Mat edges;
//    Canny(red_mask, edges, 50, 150); // 低阈值 50，高阈值 150（可根据效果微调）
//
//    // 6. 绘制“浅蓝色边缘”（背景黑，边缘浅蓝）
//    Mat edge_result = Mat::zeros(src.size(), CV_8UC3); // 创建黑色背景的彩色图
//    Scalar light_blue = Scalar(255, 200, 100);         // 浅蓝色的 BGR 值（OpenCV 中颜色为 BGR 顺序）
//    edge_result.setTo(light_blue, edges);              // 边缘区域涂浅蓝色
//
//    // 7. 显示三个窗口
//    imshow("原图", src);
//    imshow("红色二值图", red_mask);
//    imshow("边缘提取图", edge_result);
//
//    // 8. 保存边缘图到本地
//    imwrite("edge_result.jpg", edge_result);
//
//    waitKey(0); // 等待按键后关闭窗口
//    return 0;
//}