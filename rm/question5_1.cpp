//#include <opencv2/opencv.hpp>
//#include <iostream>
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
//    // 2. �ֶ���ѡƻ���Ĵ������򣨵������ڽ���ѡ��
//    Rect rect = selectROI("ѡ��ƻ������", img, false);
//    if (rect.width == 0 || rect.height == 0) {
//        cout << "δѡ����Ч����" << endl;
//        return -1;
//    }
//
//    // 3. ��ʼ�� GrabCut �������
//    Mat mask, bgdModel, fgdModel;
//    mask.create(img.size(), CV_8UC1);   // ���루0=������1=ǰ����2=���ܱ�����3=����ǰ����
//    mask = Scalar::all(0);              // ��ʼ��Ϊȫ����
//
//    // 4. ִ�� GrabCut �ָ�þ��γ�ʼ��������5���Ż���
//    grabCut(img, mask, rect, bgdModel, fgdModel, 5, GC_INIT_WITH_RECT);
//
//    // 5. ��ȡǰ�����򣨺ϲ���ȷ��ǰ�����͡�����ǰ������
//    Mat foreground;
//    compare(mask, GC_PR_FGD, foreground, CMP_EQ); // ��ǡ�����ǰ������ֵΪ3��
//    compare(mask, GC_FGD, mask, CMP_EQ);          // ��ǡ�ȷ��ǰ������ֵΪ1��
//    foreground = foreground + mask;               // �ϲ�����ǰ��
//    foreground.convertTo(foreground, CV_8UC1);
//    bitwise_and(img, img, img, foreground);       // ֻ����ǰ������
//
//    // 6. ���ǰ�����������
//    vector<vector<Point>> contours;
//    vector<Vec4i> hierarchy;
//    findContours(foreground.clone(), contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//
//    // 7. ɸѡ�������������Ϊƻ����������
//    Mat result = img.clone();
//    if (!contours.empty()) {
//        int maxIdx = 0;
//        double maxArea = contourArea(contours[0]);
//        for (size_t i = 1; i < contours.size(); i++) {
//            double area = contourArea(contours[i]);
//            if (area > maxArea) {
//                maxArea = area;
//                maxIdx = i;
//            }
//        }
//        drawContours(result, contours, maxIdx, Scalar(0, 255, 0), 2); // ������ɫ����
//        Rect bbox = boundingRect(contours[maxIdx]);
//        rectangle(result, bbox, Scalar(0, 0, 255), 2);               // ���ƺ�ɫ���ο�
//    }
//
//    // 8. ��ʾ�뱣����
//    imshow("ԭʼͼ��", img);
//    imshow("ǰ������", foreground);
//    imshow("���ս��", result);
//    imwrite("apple_full_grabcut.jpg", result);
//
//    waitKey(0);
//    destroyAllWindows();
//    return 0;
//}