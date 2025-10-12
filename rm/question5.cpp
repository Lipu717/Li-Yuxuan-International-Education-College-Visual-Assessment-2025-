//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main() {
//    // 1. ��ȡͼ��
//    Mat img = imread("D:/images/apple.png"); // �滻Ϊ���ƻ��ͼƬ·��
//    if (img.empty()) {
//        cout << "�޷���ȡͼ������·����" << endl;
//        return -1;
//    }
//
//    // 2. ת��ΪHSV��ɫ�ռ䣨���ʺ���ɫ�ָ
//    Mat hsv;
//    cvtColor(img, hsv, COLOR_BGR2HSV);
//
//    // 3. �����ɫ��HSV��Χ����ɫ��HSV�����������䣺0-10��170-180��
//    Scalar lower_red1 = Scalar(0, 40, 40);   // ��H��S��V��ֵ
//    Scalar upper_red1 = Scalar(10, 255, 255); // ��H��S��V��ֵ
//    Scalar lower_red2 = Scalar(170, 40, 40);
//    Scalar upper_red2 = Scalar(180, 255, 255);
//
//    // 4. ���ɺ�ɫ����Ķ�ֵ����
//    Mat mask1, mask2, mask;
//    inRange(hsv, lower_red1, upper_red1, mask1); // ɸѡ��һ����ɫ����
//    inRange(hsv, lower_red2, upper_red2, mask2); // ɸѡ�ڶ�����ɫ����
//    mask = mask1 + mask2; // �ϲ��������������
//
//    // 5. ��̬ѧ�����Ż����루ȥ��㡢��ն���
//    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(5, 5)); // 5��5��Բ�νṹԪ��
//    morphologyEx(mask, mask, MORPH_OPEN, kernel);  // �����㣺�ȸ�ʴ�����ͣ�ȥС��㣩
//    morphologyEx(mask, mask, MORPH_CLOSE, kernel); // �����㣺�����ͺ�ʴ����С�ն���
//
//    // 6. ��������
//    vector<vector<Point>> contours;
//    vector<Vec4i> hierarchy;
//    findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//
//    // 7. ɸѡ�����������������Ϊƻ����
//    int maxAreaIdx = -1;
//    double maxArea = 0;
//    for (size_t i = 0; i < contours.size(); i++) {
//        double area = contourArea(contours[i]);
//        if (area > maxArea) {
//            maxArea = area;
//            maxAreaIdx = i;
//        }
//    }
//
//    // 8. ������������ο�
//    Mat result = img.clone(); // ����ԭͼ���ڻ��ƽ��
//    if (maxAreaIdx != -1) {
//        drawContours(result, contours, maxAreaIdx, Scalar(0, 255, 0), 2); // ������ɫ����
//        Rect bbox = boundingRect(contours[maxAreaIdx]); // ������С��Χ����
//        rectangle(result, bbox, Scalar(0, 0, 255), 2);   // ���ƺ�ɫ���ο�
//    }
//
//    // 9. ��ʾ�뱣����
//    imshow("Original", img);
//    imshow("Mask", mask);
//    imshow("Result", result);
//    imwrite("apple_result.jpg", result); // ���������ļ�
//
//    waitKey(0);   // �ȴ�����
//    destroyAllWindows(); // �ر����д���
//    return 0;
//}