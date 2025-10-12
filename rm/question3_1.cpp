//#include <opencv2/opencv.hpp>
//#include <iostream>
//#include <string>
//#include <chrono>
//
//using namespace std;
//using namespace cv;
//
//// 全局变量
//VideoCapture video;
//int brightness = 50;  // 调整初始值到中间位置
//bool isRecording = false;
//bool wasRecording = false;
//
//// 滑动条回调：调节亮度
//void onBrightness(int val, void*) {
//    // 将0-100的值映射到摄像头支持的亮度范围
//    double mappedVal = (val - 50) / 50.0;  // 映射到-1.0到1.0范围
//    video.set(CAP_PROP_BRIGHTNESS, mappedVal);
//}
//
//int main() {
//    // ---------- 步骤1：打开摄像头 ----------
//    video.open(0);
//    if (!video.isOpened()) {
//        cout << "摄像头没打开！检查一下摄像头是否插好～" << endl;
//        return -1;
//    }
//
//    // 设置摄像头参数（减少自动调整导致的卡顿）
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
//        cout << "没拿到图像！可能摄像头有问题。" << endl;
//        return -1;
//    }
//
//    // ---------- 步骤2：创建显示窗口和滑动条 ----------
//    namedWindow("我的摄像头窗口", WINDOW_AUTOSIZE);
//
//    // 创建亮度滑动条
//    createTrackbar("亮度调节", "我的摄像头窗口", &brightness, 100, onBrightness);
//
//    // 初始设置亮度
//    onBrightness(brightness, 0);
//
//    // ---------- 步骤3：视频保存相关变量 ----------
//    VideoWriter writer;
//    string savePath = "D:/images/output.avi";  // 使用相对路径，避免权限问题
//    bool writerInitialized = false;
//
//    // 使用更兼容的编码器
//    int codec = VideoWriter::fourcc('X', 'V', 'I', 'D');  // 使用更兼容的XVID编码
//    // 或者尝试：int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');
//    double fps = 20.0;  // 使用稍低的帧率保证稳定性
//
//    cout << "操作说明：" << endl;
//    cout << "ESC: 退出程序" << endl;
//    cout << "R: 开始/停止录制" << endl;
//    cout << "视频会保存到: " << savePath << endl;
//
//    // 用于帧率计算
//    auto lastTime = chrono::steady_clock::now();
//    int frameCount = 0;
//    double actualFps = 0.0;
//
//    // ---------- 步骤4：主循环 ----------
//    while (true) {
//        auto startTime = chrono::steady_clock::now();
//
//        // 读一帧图像
//        video >> frame;
//        if (frame.empty()) {
//            cout << "图像为空，可能摄像头掉了～" << endl;
//            break;
//        }
//
//        // 计算实时帧率
//        frameCount++;
//        auto currentTime = chrono::steady_clock::now();
//        auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(currentTime - lastTime).count();
//
//        if (elapsedTime >= 1000) {  // 每1秒更新一次帧率显示
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
//        if (isRecording) {
//            // 绘制红色录制指示圆
//            circle(frame, Point(frame.cols - 30, 30), 10, Scalar(0, 0, 255), -1);
//        }
//
//        // 显示画面
//        imshow("我的摄像头窗口", frame);
//
//        // 处理录制逻辑
//        if (isRecording) {
//            if (!writerInitialized) {
//                // 首次开始录制，初始化VideoWriter
//                writer.open(savePath, codec, fps, frame.size(), true);
//                if (writer.isOpened()) {
//                    cout << "开始录制视频..." << endl;
//                    writerInitialized = true;
//                }
//                else {
//                    cout << "无法开始录制！尝试使用其他编码器..." << endl;
//                    // 尝试备用编码器
//                    codec = VideoWriter::fourcc('M', 'J', 'P', 'G');
//                    writer.open(savePath, codec, fps, frame.size(), true);
//                    if (!writer.isOpened()) {
//                        cout << "录制失败！" << endl;
//                        isRecording = false;
//                    }
//                    else {
//                        writerInitialized = true;
//                        cout << "开始录制视频..." << endl;
//                    }
//                }
//            }
//
//            if (writerInitialized) {
//                writer.write(frame);
//            }
//        }
//        else if (wasRecording && !isRecording) {
//            // 刚刚停止录制
//            if (writerInitialized) {
//                writer.release();
//                writerInitialized = false;
//                cout << "停止录制，视频已保存到: " << savePath << endl;
//            }
//        }
//        wasRecording = isRecording;
//
//        // 按键处理
//        char key = waitKey(30);  // 适当增加延迟减少CPU占用
//        if (key == 27) {  // ESC退出
//            cout << "按了ESC，程序结束～" << endl;
//            break;
//        }
//        else if (key == 'r' || key == 'R') {  // R键切换录制状态
//            isRecording = !isRecording;
//            if (isRecording) {
//                cout << "开始录制..." << endl;
//            }
//            else {
//                cout << "停止录制..." << endl;
//            }
//        }
//
//        // 限制帧率，减少CPU占用
//        auto endTime = chrono::steady_clock::now();
//        auto processTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
//        if (processTime < 33) {  // 大约30fps
//            waitKey(33 - processTime);
//        }
//    }
//
//    // ---------- 步骤5：释放资源 ----------
//    if (writer.isOpened()) {
//        writer.release();
//    }
//    video.release();
//    destroyAllWindows();
//
//    cout << "程序结束啦，资源都释放好了～" << endl;
//    return 0;
//}