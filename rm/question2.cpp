//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main() {
//    // 1. ��ȡԭʼͼ���滻Ϊ���ͼƬ·������ "shapes.jpg"��
//    Mat src = imread("D:/images/shapes.png");
//    if (src.empty()) {
//        cout << "ͼƬ��ȡʧ�ܣ�����·����" << endl;
//        return -1;
//    }
//
//    // ����ͼ��ߴ�Ϊ 1280*720
//    resize(src, src, Size(1280, 720));
//
//    // 2. ��ɫ�ռ�ת����BGR �� HSV��HSV ���ʺ���ɫ�ָ
//    Mat hsv;
//    cvtColor(src, hsv, COLOR_BGR2HSV);
//
//    // 3. ���塰��ɫ���� HSV �еķ�Χ����ɫ��**��ɫ��**��**��ɫ��**�������䣩
//    Scalar red_lower1 = Scalar(0, 100, 100);   // ��ɫ���ɫ������
//    Scalar red_upper1 = Scalar(10, 255, 255);  // ��ɫ���ɫ������
//    Scalar red_lower2 = Scalar(170, 100, 100); // ��ɫ���ɫ������
//    Scalar red_upper2 = Scalar(180, 255, 255); // ��ɫ���ɫ������
//
//    // 4. ��ȡ��ɫ�������ɶ�ֵͼ����ɫΪ�ף�����Ϊ�ڣ�
//    Mat red_mask1, red_mask2, red_mask;
//    inRange(hsv, red_lower1, red_upper1, red_mask1); // ����ɫ���ɫ
//    inRange(hsv, red_lower2, red_upper2, red_mask2); // ����ɫ���ɫ
//    red_mask = red_mask1 | red_mask2;               // �ϲ�������ɫ����Ľ��
//
//    // 5. Canny ��Ե��⣨�Ӻ�ɫ��ֵͼ����ȡ��Ե��
//    Mat edges;
//    Canny(red_mask, edges, 50, 150); // ����ֵ 50������ֵ 150���ɸ���Ч��΢����
//
//    // 6. ���ơ�ǳ��ɫ��Ե���������ڣ���Եǳ����
//    Mat edge_result = Mat::zeros(src.size(), CV_8UC3); // ������ɫ�����Ĳ�ɫͼ
//    Scalar light_blue = Scalar(255, 200, 100);         // ǳ��ɫ�� BGR ֵ��OpenCV ����ɫΪ BGR ˳��
//    edge_result.setTo(light_blue, edges);              // ��Ե����Ϳǳ��ɫ
//
//    // 7. ��ʾ��������
//    imshow("ԭͼ", src);
//    imshow("��ɫ��ֵͼ", red_mask);
//    imshow("��Ե��ȡͼ", edge_result);
//
//    // 8. �����Եͼ������
//    imwrite("edge_result.jpg", edge_result);
//
//    waitKey(0); // �ȴ�������رմ���
//    return 0;
//}