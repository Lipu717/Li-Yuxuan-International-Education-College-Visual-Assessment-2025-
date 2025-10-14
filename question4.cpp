////openCV������3
//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//// 1.����ȫ�ֱ���������Ƿ������϶���������㡢ԭͼ����ʱ��ʾͼ
//bool isDragging = false;
//Point startPoint;
//Mat image, tempImage;
//
//// 2.����¼��ص�����
//void mouseCallback(int event, int x, int y, int flags, void* userdata) {
//    if (event == EVENT_LBUTTONDOWN) {
//        // ������£���ǿ�ʼ�϶�����¼��㣬����ԭͼ����ʱͼ��
//        isDragging = true;
//        startPoint = Point(x, y);
//        image.copyTo(tempImage);
//    }
//    else if (event == EVENT_MOUSEMOVE && isDragging) {
//        // ����϶�������ʵʱ���Σ���ʾ��ǰ���ص������RGB
//        tempImage = image.clone(); // ÿ���϶������¸���ԭͼ����������ɾ���
//        Point endPoint(x, y);
//        rectangle(tempImage, startPoint, endPoint, Scalar(0, 255, 0), 2); // ��ɫ��̬����
//
//        // 3.�߽��飺ȷ�����������ͼ��Χ��
//        if (x >= 0 && x < tempImage.cols && y >= 0 && y < tempImage.rows) {
//            Vec3b pixel = tempImage.at<Vec3b>(y, x); // ��ȡ���ص�BGRֵ
//            string info = "����: (" + to_string(x) + ", " + to_string(y) + "), "
//                + "RGB: (" + to_string(pixel[2]) + ", " + to_string(pixel[1]) + ", " + to_string(pixel[0]) + ")";
//            putText(tempImage, info, Point(x + 10, y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
//        }
//    }
//    else if (event == EVENT_LBUTTONUP) {
//        // ����ͷţ�ֹͣ�϶����ü�ͼ�񲢱���
//        isDragging = false;
//        Point endPoint(x, y);
//
//        // 4.������ε���Ч��Χ
//        int x1 = min(startPoint.x, endPoint.x);
//        int y1 = min(startPoint.y, endPoint.y);
//        int x2 = max(startPoint.x, endPoint.x);
//        int y2 = max(startPoint.y, endPoint.y);
//
//        // 5.ȷ����������Ч�ߴ磨���߾�>0��
//        if (x1 < x2 && y1 < y2) {
//            Mat croppedImage = image(Rect(x1, y1, x2 - x1, y2 - y1)); // �ü�ͼ��
//            imshow("Cropped Image", croppedImage); // ��ʾ�ü����ͼ��
//            imwrite("D:/images/Ч��չʾ/cropped_cat.jpg", croppedImage); // ����ü����ͼ�񵽱���
//
//            //6. ���㲢���������������
//            Point center((x1 + x2) / 2, (y1 + y2) / 2);
//            cout << "����������������: (" << center.x << ", " << center.y << ")" << endl;
//
//            //7.��ԭͼ�ϻ������յĺ�ɫ���Σ���ѡ����ǿ�ѡ�����
//            rectangle(image, Point(x1, y1), Point(x2, y2), Scalar(0, 0, 255), 2);
//        }
//    }
//}
//
//int main() {
//    // 8. ��ȡͼ��
//    image = imread("D:/images/cat.png"); // è��ͼƬ·��
//    if (image.empty()) {
//        cout << "�޷���ȡͼ������·����" << endl;
//        return -1;
//    }
//    tempImage = image.clone(); // ��ʼ����ʱ��ʾͼ��
//
//    // 9. �������ڲ�ע�����ص�
//    namedWindow("Image");
//    setMouseCallback("Image", mouseCallback);
//
//    // 10. ѭ����ʾͼ�񣬵ȴ�ESC���˳�
//    while (true) {
//        imshow("Image", tempImage);
//        char key = waitKey(10);
//        if (key == 27) { // ESC����ASCII����27
//            break;
//        }
//    }
//
//    destroyAllWindows();
//    return 0;
//}