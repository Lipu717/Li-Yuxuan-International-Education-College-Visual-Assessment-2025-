//#include <opencv2/opencv.hpp>
//#include <iostream>
//#include <string>
//#include <chrono>
//
//using namespace std;
//using namespace cv;
//
//// ȫ�ֱ���
//VideoCapture video;
//int brightness = 50;  // ������ʼֵ���м�λ��
//bool isRecording = false;
//bool wasRecording = false;
//
//// �������ص�����������
//void onBrightness(int val, void*) {
//    // ��0-100��ֵӳ�䵽����ͷ֧�ֵ����ȷ�Χ
//    double mappedVal = (val - 50) / 50.0;  // ӳ�䵽-1.0��1.0��Χ
//    video.set(CAP_PROP_BRIGHTNESS, mappedVal);
//}
//
//int main() {
//    // ---------- ����1��������ͷ ----------
//    video.open(0);
//    if (!video.isOpened()) {
//        cout << "����ͷû�򿪣����һ������ͷ�Ƿ��á�" << endl;
//        return -1;
//    }
//
//    // ��������ͷ�����������Զ��������µĿ��٣�
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
//        cout << "û�õ�ͼ�񣡿�������ͷ�����⡣" << endl;
//        return -1;
//    }
//
//    // ---------- ����2��������ʾ���ںͻ����� ----------
//    namedWindow("�ҵ�����ͷ����", WINDOW_AUTOSIZE);
//
//    // �������Ȼ�����
//    createTrackbar("���ȵ���", "�ҵ�����ͷ����", &brightness, 100, onBrightness);
//
//    // ��ʼ��������
//    onBrightness(brightness, 0);
//
//    // ---------- ����3����Ƶ������ر��� ----------
//    VideoWriter writer;
//    string savePath = "D:/images/output.avi";  // ʹ�����·��������Ȩ������
//    bool writerInitialized = false;
//
//    // ʹ�ø����ݵı�����
//    int codec = VideoWriter::fourcc('X', 'V', 'I', 'D');  // ʹ�ø����ݵ�XVID����
//    // ���߳��ԣ�int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');
//    double fps = 20.0;  // ʹ���Ե͵�֡�ʱ�֤�ȶ���
//
//    cout << "����˵����" << endl;
//    cout << "ESC: �˳�����" << endl;
//    cout << "R: ��ʼ/ֹͣ¼��" << endl;
//    cout << "��Ƶ�ᱣ�浽: " << savePath << endl;
//
//    // ����֡�ʼ���
//    auto lastTime = chrono::steady_clock::now();
//    int frameCount = 0;
//    double actualFps = 0.0;
//
//    // ---------- ����4����ѭ�� ----------
//    while (true) {
//        auto startTime = chrono::steady_clock::now();
//
//        // ��һ֡ͼ��
//        video >> frame;
//        if (frame.empty()) {
//            cout << "ͼ��Ϊ�գ���������ͷ���ˡ�" << endl;
//            break;
//        }
//
//        // ����ʵʱ֡��
//        frameCount++;
//        auto currentTime = chrono::steady_clock::now();
//        auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(currentTime - lastTime).count();
//
//        if (elapsedTime >= 1000) {  // ÿ1�����һ��֡����ʾ
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
//        if (isRecording) {
//            // ���ƺ�ɫ¼��ָʾԲ
//            circle(frame, Point(frame.cols - 30, 30), 10, Scalar(0, 0, 255), -1);
//        }
//
//        // ��ʾ����
//        imshow("�ҵ�����ͷ����", frame);
//
//        // ����¼���߼�
//        if (isRecording) {
//            if (!writerInitialized) {
//                // �״ο�ʼ¼�ƣ���ʼ��VideoWriter
//                writer.open(savePath, codec, fps, frame.size(), true);
//                if (writer.isOpened()) {
//                    cout << "��ʼ¼����Ƶ..." << endl;
//                    writerInitialized = true;
//                }
//                else {
//                    cout << "�޷���ʼ¼�ƣ�����ʹ������������..." << endl;
//                    // ���Ա��ñ�����
//                    codec = VideoWriter::fourcc('M', 'J', 'P', 'G');
//                    writer.open(savePath, codec, fps, frame.size(), true);
//                    if (!writer.isOpened()) {
//                        cout << "¼��ʧ�ܣ�" << endl;
//                        isRecording = false;
//                    }
//                    else {
//                        writerInitialized = true;
//                        cout << "��ʼ¼����Ƶ..." << endl;
//                    }
//                }
//            }
//
//            if (writerInitialized) {
//                writer.write(frame);
//            }
//        }
//        else if (wasRecording && !isRecording) {
//            // �ո�ֹͣ¼��
//            if (writerInitialized) {
//                writer.release();
//                writerInitialized = false;
//                cout << "ֹͣ¼�ƣ���Ƶ�ѱ��浽: " << savePath << endl;
//            }
//        }
//        wasRecording = isRecording;
//
//        // ��������
//        char key = waitKey(30);  // �ʵ������ӳټ���CPUռ��
//        if (key == 27) {  // ESC�˳�
//            cout << "����ESC�����������" << endl;
//            break;
//        }
//        else if (key == 'r' || key == 'R') {  // R���л�¼��״̬
//            isRecording = !isRecording;
//            if (isRecording) {
//                cout << "��ʼ¼��..." << endl;
//            }
//            else {
//                cout << "ֹͣ¼��..." << endl;
//            }
//        }
//
//        // ����֡�ʣ�����CPUռ��
//        auto endTime = chrono::steady_clock::now();
//        auto processTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
//        if (processTime < 33) {  // ��Լ30fps
//            waitKey(33 - processTime);
//        }
//    }
//
//    // ---------- ����5���ͷ���Դ ----------
//    if (writer.isOpened()) {
//        writer.release();
//    }
//    video.release();
//    destroyAllWindows();
//
//    cout << "�������������Դ���ͷź��ˡ�" << endl;
//    return 0;
//}