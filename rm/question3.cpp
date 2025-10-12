//#include <opencv2/opencv.hpp>
//#include <iostream>
//#include <string>
//
//using namespace std;
//using namespace cv;
//
//// ȫ�ֱ�����������Ҫ�������ȡ��ع�ֵ
//VideoCapture video;     // ����ͷ����ȫ�֣������ص��������õ���
//int brightness = 15;  // ���ȳ�ʼֵ��0��100֮�䣩
//int exposure = 50;    // �ع��ʼֵ��0��100֮�䣩
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
//int main() {
//    // ---------- ����1��������ͷ ----------
//    video.open(0);  // �򿪵���Ĭ������ͷ��ID��0��
//    if (!video.isOpened()) {  // �������ͷ��û�д򿪳ɹ�
//        cout << "����ͷû�򿪣����һ������ͷ�Ƿ��á�" << endl;
//        return -1;  // ��ʧ�ܣ��ͽ�������
//    }
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
//    namedWindow("�ҵ�����ͷ����", WINDOW_NORMAL);  // ����һ�����Ե�����С�Ĵ���
//
//    // �������Ȼ��������󶨵�����Ĵ��ڣ���Χ0-100��
//    createTrackbar("���ȵ���", "�ҵ�����ͷ����", &brightness, 100, onBrightness);
//
//    // �����ع⻬�������󶨵����ڣ���Χ0-100��
//    createTrackbar("�ع����", "�ҵ�����ͷ����", &exposure, 100, onExposure);
//
//    // ---------- ����3��������Ƶ���� ----------
//    int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');  // ѡMJPG���루�Ƚ�ͨ�ã�
//    double fps = 30.0;  // �趨�������Ƶÿ�����֡
//    string savePath = "D:/images/now.avi";  // ��Ƶ�����·����Ҫȷ��D:/images�ļ��д��ڣ���
//
//    VideoWriter writer;  // ��Ƶд�����
//    // ����Ƶд�����������ǡ�����·�������롢֡�ʡ�����ߴ硢�Ƿ��ɫ��
//    writer.open(savePath, codec, fps, frame.size(), true);
//
//    if (!writer.isOpened()) {  // ����ܲ��ܿ�ʼ������Ƶ
//        cout << "��Ƶ����ʧ�ܣ�������·�����ԣ����߱��벻֧�֡�" << endl;
//        return -1;
//    }
//    cout << "��Ƶ�ᱣ�浽��" << savePath << endl;
//
//    // ---------- ����4��ѭ����֡����ʾ������ ----------
//    while (true)
//    {
//        // ��һ֡ͼ��
//        video >> frame;
//        if (frame.empty()) {  // ���û����ͼ��˵������ͷ���ܶ���
//            cout << "ͼ��Ϊ�գ���������ͷ���ˡ�" << endl;
//            break;  // �˳�ѭ��
//        }
//
//        // �ڻ�������ʾ����ͷ�Ĳ������ߴ硢֡�ʣ�
//        int width = video.get(CAP_PROP_FRAME_WIDTH);
//        int height = video.get(CAP_PROP_FRAME_HEIGHT);
//        double realFps = video.get(CAP_PROP_FPS);
//        // ����֡��Ϊ 0 ����������Ϊ 0����ʾ��Unknown����������ʾʵ��ֵ
//        string fpsStr = (realFps > 0) ? to_string(realFps) : "Unknown";
//
//        // ��Ӣ��ƴ����Ϣ�������������룩
//        string info = "Size: " + to_string(width) + "x" + to_string(height) +
//            "  FPS: " + fpsStr;
//
//        // �������֣���֮ǰһ����
//        putText(frame, info, Point(10, 30),
//            FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
//
//        // ��ʾ����
//        imshow("�ҵ�����ͷ����", frame);
//
//        // 5. ����������ESC�˳�����R�л����Ƿ�¼�ơ���
//        char key = waitKey(1);  // �ӳ�1���룬�û��������
//        if (key == 27) {  // ��ESC���˳���ASCII��27��
//            cout << "����ESC�����������" << endl;
//            break;
//        }
//    }
//    // ---------- ����5���ͷ���Դ������Ҫ���� ----------
//    video.release();        // �ر�����ͷ
//    writer.release();     // �ر���Ƶд����
//    destroyAllWindows();  // �ر�������ʾ����
//
//    cout << "�������������Դ���ͷ�" << endl;
//    return 0;
//}