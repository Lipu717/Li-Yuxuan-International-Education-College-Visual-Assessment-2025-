//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main() {
//    // 1. 读取原始图像（请替换为你的图片路径）
//    Mat src = imread("your_image_path.png"); // 例如 "shapes.png"
//    if (src.empty()) {
//        cout << "图片读取失败！请检查路径。" << endl;
//        return -1;
//    }
//
//    // 调整图像尺寸为 1280*720
//    resize(src, src, Size(1280, 720));
//
//    // 2. 颜色空间转换：BGR → HSV（HSV更适合颜色分割）
//    Mat hsv;
//    cvtColor(src, hsv, COLOR_BGR2HSV);
//
//    // 3. 定义“红色”在HSV中的范围（红色分低、高色相两个区间）
//    Scalar red_lower1 = Scalar(0, 100, 100);   // 低色相红色下限
//    Scalar red_upper1 = Scalar(10, 255, 255);  // 低色相红色上限
//    Scalar red_lower2 = Scalar(170, 100, 100); // 高色相红色下限
//    Scalar red_upper2 = Scalar(180, 255, 255); // 高色相红色上限
//
//    // 4. 提取所有红色区域（生成二值图：红色为白，其他为黑）
//    Mat red_mask1, red_mask2, red_mask;
//    inRange(hsv, red_lower1, red_upper1, red_mask1); // 检测低色相红色
//    inRange(hsv, red_lower2, red_upper2, red_mask2); // 检测高色相红色
//    red_mask = red_mask1 | red_mask2;               // 合并两个红色区间
//
//    // ================= 新增：形状筛选（只保留红色三角形） =================
//    vector<vector<Point>> contours; // 存储所有轮廓
//    vector<Vec4i> hierarchy;        // 轮廓的层级关系
//    // 查找红色二值图的最外层轮廓
//    findContours(red_mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//
//    Mat triangle_mask = Mat::zeros(red_mask.size(), CV_8UC1); // 三角形专属掩码（初始全黑）
//    for (size_t i = 0; i < contours.size(); i++) {
//        // 计算轮廓的近似多边形（精度为轮廓周长的2%，可根据效果微调）
//        double epsilon = 0.02 * arcLength(contours[i], true);
//        vector<Point> approx;
//        approxPolyDP(contours[i], approx, epsilon, true);
//
//        // 顶点数为3 → 判定为三角形，在掩码上绘制该轮廓（填充）
//        if (approx.size() == 3) {
//            drawContours(triangle_mask, contours, i, Scalar(255), FILLED);
//        }
//    }
//    // ======================================================================
//
//    // 5. Canny边缘检测（基于“三角形掩码”）
//    Mat edges;
//    Canny(triangle_mask, edges, 50, 150); // 低阈值50，高阈值150（可微调）
//
//    // 6. 绘制“浅蓝色边缘”（背景黑，边缘浅蓝）
//    Mat edge_result = Mat::zeros(src.size(), CV_8UC3); // 黑色背景的彩色图
//    Scalar light_blue = Scalar(255, 200, 100);         // BGR顺序的浅蓝色
//    edge_result.setTo(light_blue, edges);              // 边缘区域涂浅蓝色
//
//    // 7. 显示窗口
//    imshow("原图", src);
//    imshow("所有红色的二值图", red_mask);
//    imshow("红色三角形的掩码", triangle_mask);
//    imshow("红色三角形的边缘提取图", edge_result);
//
//    // 8. 保存边缘图到本地
//    imwrite("red_triangle_edges.jpg", edge_result);
//
//    waitKey(0); // 等待按键后关闭窗口
//    return 0;
//}