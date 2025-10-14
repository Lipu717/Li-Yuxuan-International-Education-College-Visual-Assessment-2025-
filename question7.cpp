////openCV赛事题装甲板识别
//#include <opencv2/opencv.hpp>
//#include <vector>
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//class ArmorDetector {
//private:
//    Mat srcImg,//原始图片
//        hsvImg, //HSV图片
//        binaryImg;//二值化图片
//    vector<RotatedRect> armorRects;//动态数组储存装甲板矩形
//
//public:
//    ArmorDetector(const Mat& img) : srcImg(img) {
//        cout << "已启动识别程序" << endl;
//    }
//
//    // 1.预处理：适配图片中亮蓝色灯条
//    bool preprocess() {
//        cvtColor(srcImg, hsvImg, COLOR_BGR2HSV);
//        // 调整蓝色HSV范围（匹配图片中偏亮的蓝色）
//        Scalar lowerBlue = Scalar(90, 80, 80);
//        Scalar upperBlue = Scalar(140, 255, 255);
//        inRange(hsvImg, lowerBlue, upperBlue, binaryImg);
//
//        //2. 形态学去噪（连接灯条、消除杂点）
//        Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
//        morphologyEx(binaryImg, binaryImg, MORPH_OPEN, kernel);
//        morphologyEx(binaryImg, binaryImg, MORPH_CLOSE, kernel);
//        return true;
//    }
//
//    // 3.检测并筛选装甲板灯条（适配图片中灯条的长度、比例）
//    bool detectArmor() {
//        vector<vector<Point>> contours;
//        vector<Vec4i> hierarchy;
//        findContours(binaryImg, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//
//        for (const auto& contour : contours) {
//            RotatedRect rect = minAreaRect(contour);
//            Size2f size = rect.size;
//            float length = max(size.width, size.height);
//            float width = min(size.width, size.height);
//
//            //4. 筛选条件：长度适中（排除长干扰灯）、长宽比符合短灯条特征
//            if (length > 30 && length < 150 && width > 10 && length / width > 1.5) {
//                armorRects.push_back(rect);
//            }
//        }
//        return !armorRects.empty();
//    }
//
//    // 5.绘制装甲板矩形和中心点
//    void drawResult(Mat& displayImg) {
//        for (const auto& rect : armorRects) {
//            Point2f vertices[4];
//            rect.points(vertices);
//            for (int i = 0; i < 4; ++i) {
//                line(displayImg,//画线
//                    vertices[i], vertices[(i + 1) % 4],//始终点
//                    Scalar(0, 255, 0),//颜色
//                    2);//线宽
//            }
//            Point center = Point(rect.center.x, rect.center.y);
//            circle(displayImg, center, 3, Scalar(0, 0, 255), -1);
//        }
//    }
//
//    //6. 整体流程：预处理 → 检测 → 绘制
//    bool process(Mat& displayImg) {
//        displayImg = srcImg.clone();
//        if (!preprocess()) return false;
//        if (!detectArmor()) return false;
//        drawResult(displayImg);
//        return true;
//    }
//};
//
//int main() {
//    Mat img = imread("D:/images/armor_image.jpg");
//    if (img.empty()) {
//        cerr << "无法读取图像！请检查路径。" << endl;
//        return -1;
//    }
//
//    ArmorDetector detector(img);
//    Mat resultImg;
//    bool success = detector.process(resultImg);
//	  //7. 显示结果
//    if (success) {
//        cout << "成功识别到装甲板！" << endl;
//    }
//    else {
//        cout << "未识别到，可调整HSV范围或筛选条件。" << endl;
//    }
//    imshow("装甲板识别结果", resultImg);
//    waitKey(0);  // 按任意键关闭窗口
//    return 0;
//}