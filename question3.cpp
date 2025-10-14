////openCV基础题2
//#include <opencv2/opencv.hpp>
//#include <iostream>
//#include <string>
//#include <chrono>
//
//using namespace std;
//using namespace cv;
//
//// 全局变量：滑动条要调的亮度、曝光值
//VideoCapture video;     // 摄像头对象
//int brightness = 15;  // 亮度初始值
//int exposure = 50;    // 曝光初始值
//bool isRecording = false;
//bool wasRecording = false;
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
//int main()
//{
//    // ----------打开摄像头 ----------
//    video.open(0);
//    if (!video.isOpened()) {
//        cout << "摄像头没打开" << endl;
//        return -1;
//    }
//
//    // 设置摄像头参数
//    video.set(CAP_PROP_FRAME_WIDTH, 640);
//    video.set(CAP_PROP_FRAME_HEIGHT, 480);
//    video.set(CAP_PROP_FPS, 30);
//    video.set(CAP_PROP_AUTOFOCUS, 0);  // 关闭自动对焦
//    video.set(CAP_PROP_AUTO_EXPOSURE, 0);  // 关闭自动曝光
//
//    // 先读一帧图像，确保能正常获取
//    Mat frame;
//    video >> frame;
//    if (frame.empty()) {
//        cout << "错误。" << endl;
//        return -1;
//    }
//
//    // ----------创建显示窗口和滑动条 ----------
//    namedWindow("我的摄像头窗口", WINDOW_NORMAL);  // 创建一个可以调整大小的窗口
//
//    // 创建亮度滑动条绑定到上面的窗口，范围0-100
//    createTrackbar("亮度调节", "我的摄像头窗口", &brightness, 100, onBrightness);
//
//    // 创建曝光滑动条绑定到窗口，范围0-100
//    createTrackbar("曝光调节", "我的摄像头窗口", &exposure, 100, onExposure);
//
//    // ----------设置视频保存 ----------
//    int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');  // 选较通用MJPG编码
//    double fps = 30.0;  // 设定保存的视频每秒多少帧
//    string savePath = "D:/images/now.avi";  // 视频保存的路径
//
//    VideoWriter writer;  // 视频写入对象
//    // 打开视频写入器：参数是“保存路径、编码、帧率、画面尺寸、是否彩色”
//    writer.open(savePath, codec, fps, frame.size(), true);
//
//    if (!writer.isOpened()) {  // 检查能不能开始保存视频
//        cout << "视频保存失败。可能是路径不对，或者编码不支持。" << endl;
//        return -1;
//    }
//    cout << "视频会保存到：" << savePath << endl;
//
//    // 用于帧率计算
//    auto lastTime = chrono::steady_clock::now();
//    int frameCount = 0;
//    double actualFps = 0.0;
//
//    // ----------循环读帧、显示、保存 ----------
//    while (true)
//    {
//        // 读一帧图像
//        video >> frame;
//        if (frame.empty()) {  // 如果没读到图像，说明摄像头可能断联
//            cout << "图像为空" << endl;
//            break;  // 退出循环
//        }
//        // 计算实时帧率
//        frameCount++;
//        auto currentTime = chrono::steady_clock::now();
//        auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(currentTime - lastTime).count();
//        if (elapsedTime >= 1000)
//        {  // 每1秒更新一次帧率显示
//            actualFps = frameCount * 1000.0 / elapsedTime;
//            frameCount = 0;
//            lastTime = currentTime;
//        }
//
//        // 在画面上显示信息
//        string info = "FPS: " + to_string(actualFps).substr(0, 4);
//        string recordInfo = isRecording ? "RECORDING" : "Not Recording";
//
//        putText(frame, info, Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
//        putText(frame, recordInfo, Point(10, 60), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 255), 2);
//
//        if (isRecording)
//        {
//            // 绘制红色录制指示圆
//            circle(frame, Point(frame.cols - 30, 30), 10, Scalar(0, 0, 255), -1);
//            writer.write(frame);
//        }
//    
//        // 显示画面
//        imshow("我的摄像头窗口", frame);
//
//        // 按键交互
//        char key = waitKey(1);  // 延迟1毫秒，让画面更流畅
//        if (key == 27)//ESC的ASCII码是27
//        {  // 按ESC键退出
//            cout << "按了ESC，程序结束～" << endl;
//            break;
//        }
//        else if (key == 'r' || key == 'R')
//        { // 按R键切换录制状态
//            isRecording = !isRecording;
//            if (isRecording)
//            {
//                cout << "开始录制" << endl;
//            }
//            else
//            {
//                cout << "停止录制" << endl;
//            }
//        }
//    }  // while循环结束
//
//    // ----------释放资源 ----------
//    video.release();        // 关闭摄像头
//    writer.release();     // 关闭视频写入器
//    destroyAllWindows();  // 关闭所有显示窗口
//
//    cout << "程序结束啦，资源已释放" << endl;
//    return 0;
//}