//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main() {
//    // 1. ��ȡԭʼͼ�����滻Ϊ���ͼƬ·����
//    Mat src = imread("your_image_path.png"); // ���� "shapes.png"
//    if (src.empty()) {
//        cout << "ͼƬ��ȡʧ�ܣ�����·����" << endl;
//        return -1;
//    }
//
//    // ����ͼ��ߴ�Ϊ 1280*720
//    resize(src, src, Size(1280, 720));
//
//    // 2. ��ɫ�ռ�ת����BGR �� HSV��HSV���ʺ���ɫ�ָ
//    Mat hsv;
//    cvtColor(src, hsv, COLOR_BGR2HSV);
//
//    // 3. ���塰��ɫ����HSV�еķ�Χ����ɫ�ֵ͡���ɫ���������䣩
//    Scalar red_lower1 = Scalar(0, 100, 100);   // ��ɫ���ɫ����
//    Scalar red_upper1 = Scalar(10, 255, 255);  // ��ɫ���ɫ����
//    Scalar red_lower2 = Scalar(170, 100, 100); // ��ɫ���ɫ����
//    Scalar red_upper2 = Scalar(180, 255, 255); // ��ɫ���ɫ����
//
//    // 4. ��ȡ���к�ɫ�������ɶ�ֵͼ����ɫΪ�ף�����Ϊ�ڣ�
//    Mat red_mask1, red_mask2, red_mask;
//    inRange(hsv, red_lower1, red_upper1, red_mask1); // ����ɫ���ɫ
//    inRange(hsv, red_lower2, red_upper2, red_mask2); // ����ɫ���ɫ
//    red_mask = red_mask1 | red_mask2;               // �ϲ�������ɫ����
//
//    // ================= ��������״ɸѡ��ֻ������ɫ�����Σ� =================
//    vector<vector<Point>> contours; // �洢��������
//    vector<Vec4i> hierarchy;        // �����Ĳ㼶��ϵ
//    // ���Һ�ɫ��ֵͼ�����������
//    findContours(red_mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//
//    Mat triangle_mask = Mat::zeros(red_mask.size(), CV_8UC1); // ������ר�����루��ʼȫ�ڣ�
//    for (size_t i = 0; i < contours.size(); i++) {
//        // ���������Ľ��ƶ���Σ�����Ϊ�����ܳ���2%���ɸ���Ч��΢����
//        double epsilon = 0.02 * arcLength(contours[i], true);
//        vector<Point> approx;
//        approxPolyDP(contours[i], approx, epsilon, true);
//
//        // ������Ϊ3 �� �ж�Ϊ�����Σ��������ϻ��Ƹ���������䣩
//        if (approx.size() == 3) {
//            drawContours(triangle_mask, contours, i, Scalar(255), FILLED);
//        }
//    }
//    // ======================================================================
//
//    // 5. Canny��Ե��⣨���ڡ����������롱��
//    Mat edges;
//    Canny(triangle_mask, edges, 50, 150); // ����ֵ50������ֵ150����΢����
//
//    // 6. ���ơ�ǳ��ɫ��Ե���������ڣ���Եǳ����
//    Mat edge_result = Mat::zeros(src.size(), CV_8UC3); // ��ɫ�����Ĳ�ɫͼ
//    Scalar light_blue = Scalar(255, 200, 100);         // BGR˳���ǳ��ɫ
//    edge_result.setTo(light_blue, edges);              // ��Ե����Ϳǳ��ɫ
//
//    // 7. ��ʾ����
//    imshow("ԭͼ", src);
//    imshow("���к�ɫ�Ķ�ֵͼ", red_mask);
//    imshow("��ɫ�����ε�����", triangle_mask);
//    imshow("��ɫ�����εı�Ե��ȡͼ", edge_result);
//
//    // 8. �����Եͼ������
//    imwrite("red_triangle_edges.jpg", edge_result);
//
//    waitKey(0); // �ȴ�������رմ���
//    return 0;
//}