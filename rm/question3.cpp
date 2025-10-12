//#include <opencv2/opencv.hpp>
//#include <iostream>
//#include <string>
//
//using namespace std;
//using namespace cv;
//
//// 全局变量：滑动条要调的亮度、曝光值
//VideoCapture video;     // 摄像头对象（全局，这样回调函数能用到）
//int brightness = 15;  // 亮度初始值（0到100之间）
//int exposure = 50;    // 曝光初始值（0到100之间）
//
//// 滑动条回调：调节亮度
//void onBrightness(int val, void*) {
//    video.set(CAP_PROP_BRIGHTNESS, val);
//}
//
//// 滑动条回调：调节曝光
//void onExposure(int val, void*) {
//    video.set(CAP_PROP_EXPOSURE, val);
//}
//
//int main() {
//    // ---------- 步骤1：打开摄像头 ----------
//    video.open(0);  // 打开电脑默认摄像头（ID是0）
//    if (!video.isOpened()) {  // 检查摄像头有没有打开成功
//        cout << "摄像头没打开！检查一下摄像头是否插好～" << endl;
//        return -1;  // 打开失败，就结束程序
//    }
//
//    // 先读一帧图像，确保能正常获取
//    Mat frame;
//    video >> frame;
//    if (frame.empty()) {
//        cout << "没拿到图像！可能摄像头有问题。" << endl;
//        return -1;
//    }
//
//    // ---------- 步骤2：创建显示窗口和滑动条 ----------
//    namedWindow("我的摄像头窗口", WINDOW_NORMAL);  // 创建一个可以调整大小的窗口
//
//    // 创建亮度滑动条（绑定到上面的窗口，范围0-100）
//    createTrackbar("亮度调节", "我的摄像头窗口", &brightness, 100, onBrightness);
//
//    // 创建曝光滑动条（绑定到窗口，范围0-100）
//    createTrackbar("曝光调节", "我的摄像头窗口", &exposure, 100, onExposure);
//
//    // ---------- 步骤3：设置视频保存 ----------
//    int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');  // 选MJPG编码（比较通用）
//    double fps = 30.0;  // 设定保存的视频每秒多少帧
//    string savePath = "D:/images/now.avi";  // 视频保存的路径（要确保D:/images文件夹存在！）
//
//    VideoWriter writer;  // 视频写入对象
//    // 打开视频写入器：参数是“保存路径、编码、帧率、画面尺寸、是否彩色”
//    writer.open(savePath, codec, fps, frame.size(), true);
//
//    if (!writer.isOpened()) {  // 检查能不能开始保存视频
//        cout << "视频保存失败！可能是路径不对，或者编码不支持。" << endl;
//        return -1;
//    }
//    cout << "视频会保存到：" << savePath << endl;
//
//    // ---------- 步骤4：循环读帧、显示、保存 ----------
//    while (true)
//    {
//        // 读一帧图像
//        video >> frame;
//        if (frame.empty()) {  // 如果没读到图像，说明摄像头可能断了
//            cout << "图像为空，可能摄像头掉了～" << endl;
//            break;  // 退出循环
//        }
//
//        // 在画面上显示摄像头的参数（尺寸、帧率）
//        int width = video.get(CAP_PROP_FRAME_WIDTH);
//        int height = video.get(CAP_PROP_FRAME_HEIGHT);
//        double realFps = video.get(CAP_PROP_FPS);
//        // 处理帧率为 0 的情况：如果为 0，显示“Unknown”，否则显示实际值
//        string fpsStr = (realFps > 0) ? to_string(realFps) : "Unknown";
//
//        // 用英文拼接信息（避免中文乱码）
//        string info = "Size: " + to_string(width) + "x" + to_string(height) +
//            "  FPS: " + fpsStr;
//
//        // 绘制文字（和之前一样）
//        putText(frame, info, Point(10, 30),
//            FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
//
//        // 显示画面
//        imshow("我的摄像头窗口", frame);
//
//        // 5. 按键交互（ESC退出；按R切换“是否录制”）
//        char key = waitKey(1);  // 延迟1毫秒，让画面更流畅
//        if (key == 27) {  // 按ESC键退出（ASCII码27）
//            cout << "按了ESC，程序结束～" << endl;
//            break;
//        }
//    }
//    // ---------- 步骤5：释放资源（很重要！） ----------
//    video.release();        // 关闭摄像头
//    writer.release();     // 关闭视频写入器
//    destroyAllWindows();  // 关闭所有显示窗口
//
//    cout << "程序结束啦，资源已释放" << endl;
//    return 0;
//}