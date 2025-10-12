//#include <opencv2/opencv.hpp>
//#include <iostream>
//#include <cmath>
//
//using namespace cv;
//using namespace std;
//
//int main() {
//    // 1. ��ȡͼ��
//    Mat img = imread("D:/images/apple.png"); // �滻Ϊ���ͼ��·��
//    if (img.empty()) {
//        cout << "�޷���ȡͼ��" << endl;
//        return -1;
//    }
//
//    // 2. ת��Ϊ HSV ��ɫ�ռ䣨���ʺ���ɫ�ָ
//    Mat hsv;
//    cvtColor(img, hsv, COLOR_BGR2HSV);
//
//    // 3. ����ƻ������ɫ���䣨��ɫ+��ɫ��
//    Scalar lower_red1 = Scalar(0, 40, 40);    // ��ɫ����1��H:0-10��
//    Scalar upper_red1 = Scalar(10, 255, 255);
//    Scalar lower_red2 = Scalar(170, 40, 40);   // ��ɫ����2��H:170-180��
//    Scalar upper_red2 = Scalar(180, 255, 255);
//    Scalar lower_yellow = Scalar(20, 40, 40);  // ��ɫ���䣨H:20-35��
//    Scalar upper_yellow = Scalar(35, 255, 255);
//
//    // 4. ���ɸ���ɫ��������벢�ϲ�
//    Mat mask_red1, mask_red2, mask_yellow, mask;
//    inRange(hsv, lower_red1, upper_red1, mask_red1);
//    inRange(hsv, lower_red2, upper_red2, mask_red2);
//    inRange(hsv, lower_yellow, upper_yellow, mask_yellow);
//    mask = mask_red1 + mask_red2 + mask_yellow; // �ϲ��졢������
//
//    // 5. ��̬ѧ�����㣺���ƻ���ڲ���϶�����Ӳ���������
//    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(7, 7));
//    morphologyEx(mask, mask, MORPH_CLOSE, kernel);
//
//    // 6. �������
//    vector<vector<Point>> contours;
//    vector<Vec4i> hierarchy;
//    findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//
//    // 7. ɸѡ��Բ�ζ���ߡ���������ƻ������Բ�Σ�
//    Mat result = img.clone();
//    int bestIdx = -1;
//    double bestCircularity = 0;
//
//    for (size_t i = 0; i < contours.size(); i++) {
//        double area = contourArea(contours[i]);
//        if (area < 100) continue; // ���˼�С��������㣩
//
//        double perimeter = arcLength(contours[i], true);
//        double circularity = 4 * CV_PI * area / (perimeter * perimeter); // Բ�ζȹ�ʽ
//
//        if (circularity > bestCircularity) {
//            bestCircularity = circularity;
//            bestIdx = i;
//        }
//    }
//
//    // 8. ����ƻ����������ο�
//    if (bestIdx != -1) {
//        drawContours(result, contours, bestIdx, Scalar(0, 255, 0), 2); // ��ɫ����
//        Rect bbox = boundingRect(contours[bestIdx]);
//        rectangle(result, bbox, Scalar(0, 0, 255), 2);               // ��ɫ���ο�
//    }
//
//    // 9. ��ʾ�뱣����
//    imshow("��ɫ����", mask);
//    imshow("���ս��", result);
//    imwrite("apple_full_shape.jpg", result);
//
//    waitKey(0);
//    destroyAllWindows();
//    return 0;
//}