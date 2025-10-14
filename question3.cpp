////openCV������2
//#include <opencv2/opencv.hpp>
//#include <iostream>
//#include <string>
//#include <chrono>
//
//using namespace std;
//using namespace cv;
//
//// ȫ�ֱ�����������Ҫ�������ȡ��ع�ֵ
//VideoCapture video;     // ����ͷ����
//int brightness = 15;  // ���ȳ�ʼֵ
//int exposure = 50;    // �ع��ʼֵ
//bool isRecording = false;
//bool wasRecording = false;
//
//// �������ص�����������
//void onBrightness(int val, void*) {
//    video.set(CAP_PROP_BRIGHTNESS, val);
//}
//
//// �������ص��������ع�
//void onExposure(int val, void*) {
//    video.set(CAP_PROP_EXPOSURE, val);
//}
//
//int main()
//{
//    // ----------������ͷ ----------
//    video.open(0);
//    if (!video.isOpened()) {
//        cout << "����ͷû��" << endl;
//        return -1;
//    }
//
//    // ��������ͷ����
//    video.set(CAP_PROP_FRAME_WIDTH, 640);
//    video.set(CAP_PROP_FRAME_HEIGHT, 480);
//    video.set(CAP_PROP_FPS, 30);
//    video.set(CAP_PROP_AUTOFOCUS, 0);  // �ر��Զ��Խ�
//    video.set(CAP_PROP_AUTO_EXPOSURE, 0);  // �ر��Զ��ع�
//
//    // �ȶ�һ֡ͼ��ȷ����������ȡ
//    Mat frame;
//    video >> frame;
//    if (frame.empty()) {
//        cout << "����" << endl;
//        return -1;
//    }
//
//    // ----------������ʾ���ںͻ����� ----------
//    namedWindow("�ҵ�����ͷ����", WINDOW_NORMAL);  // ����һ�����Ե�����С�Ĵ���
//
//    // �������Ȼ������󶨵�����Ĵ��ڣ���Χ0-100
//    createTrackbar("���ȵ���", "�ҵ�����ͷ����", &brightness, 100, onBrightness);
//
//    // �����ع⻬�����󶨵����ڣ���Χ0-100
//    createTrackbar("�ع����", "�ҵ�����ͷ����", &exposure, 100, onExposure);
//
//    // ----------������Ƶ���� ----------
//    int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');  // ѡ��ͨ��MJPG����
//    double fps = 30.0;  // �趨�������Ƶÿ�����֡
//    string savePath = "D:/images/now.avi";  // ��Ƶ�����·��
//
//    VideoWriter writer;  // ��Ƶд�����
//    // ����Ƶд�����������ǡ�����·�������롢֡�ʡ�����ߴ硢�Ƿ��ɫ��
//    writer.open(savePath, codec, fps, frame.size(), true);
//
//    if (!writer.isOpened()) {  // ����ܲ��ܿ�ʼ������Ƶ
//        cout << "��Ƶ����ʧ�ܡ�������·�����ԣ����߱��벻֧�֡�" << endl;
//        return -1;
//    }
//    cout << "��Ƶ�ᱣ�浽��" << savePath << endl;
//
//    // ����֡�ʼ���
//    auto lastTime = chrono::steady_clock::now();
//    int frameCount = 0;
//    double actualFps = 0.0;
//
//    // ----------ѭ����֡����ʾ������ ----------
//    while (true)
//    {
//        // ��һ֡ͼ��
//        video >> frame;
//        if (frame.empty()) {  // ���û����ͼ��˵������ͷ���ܶ���
//            cout << "ͼ��Ϊ��" << endl;
//            break;  // �˳�ѭ��
//        }
//        // ����ʵʱ֡��
//        frameCount++;
//        auto currentTime = chrono::steady_clock::now();
//        auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(currentTime - lastTime).count();
//        if (elapsedTime >= 1000)
//        {  // ÿ1�����һ��֡����ʾ
//            actualFps = frameCount * 1000.0 / elapsedTime;
//            frameCount = 0;
//            lastTime = currentTime;
//        }
//
//        // �ڻ�������ʾ��Ϣ
//        string info = "FPS: " + to_string(actualFps).substr(0, 4);
//        string recordInfo = isRecording ? "RECORDING" : "Not Recording";
//
//        putText(frame, info, Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
//        putText(frame, recordInfo, Point(10, 60), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 255), 2);
//
//        if (isRecording)
//        {
//            // ���ƺ�ɫ¼��ָʾԲ
//            circle(frame, Point(frame.cols - 30, 30), 10, Scalar(0, 0, 255), -1);
//            writer.write(frame);
//        }
//    
//        // ��ʾ����
//        imshow("�ҵ�����ͷ����", frame);
//
//        // ��������
//        char key = waitKey(1);  // �ӳ�1���룬�û��������
//        if (key == 27)//ESC��ASCII����27
//        {  // ��ESC���˳�
//            cout << "����ESC�����������" << endl;
//            break;
//        }
//        else if (key == 'r' || key == 'R')
//        { // ��R���л�¼��״̬
//            isRecording = !isRecording;
//            if (isRecording)
//            {
//                cout << "��ʼ¼��" << endl;
//            }
//            else
//            {
//                cout << "ֹͣ¼��" << endl;
//            }
//        }
//    }  // whileѭ������
//
//    // ----------�ͷ���Դ ----------
//    video.release();        // �ر�����ͷ
//    writer.release();     // �ر���Ƶд����
//    destroyAllWindows();  // �ر�������ʾ����
//
//    cout << "�������������Դ���ͷ�" << endl;
//    return 0;
//}