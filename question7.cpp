////openCV������װ�װ�ʶ��
//#include <opencv2/opencv.hpp>
//#include <vector>
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//class ArmorDetector {
//private:
//    Mat srcImg,//ԭʼͼƬ
//        hsvImg, //HSVͼƬ
//        binaryImg;//��ֵ��ͼƬ
//    vector<RotatedRect> armorRects;//��̬���鴢��װ�װ����
//
//public:
//    ArmorDetector(const Mat& img) : srcImg(img) {
//        cout << "������ʶ�����" << endl;
//    }
//
//    // 1.Ԥ��������ͼƬ������ɫ����
//    bool preprocess() {
//        cvtColor(srcImg, hsvImg, COLOR_BGR2HSV);
//        // ������ɫHSV��Χ��ƥ��ͼƬ��ƫ������ɫ��
//        Scalar lowerBlue = Scalar(90, 80, 80);
//        Scalar upperBlue = Scalar(140, 255, 255);
//        inRange(hsvImg, lowerBlue, upperBlue, binaryImg);
//
//        //2. ��̬ѧȥ�루���ӵ����������ӵ㣩
//        Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
//        morphologyEx(binaryImg, binaryImg, MORPH_OPEN, kernel);
//        morphologyEx(binaryImg, binaryImg, MORPH_CLOSE, kernel);
//        return true;
//    }
//
//    // 3.��Ⲣɸѡװ�װ����������ͼƬ�е����ĳ��ȡ�������
//    bool detectArmor() {
//        vector<vector<Point>> contours;
//        vector<Vec4i> hierarchy;
//        findContours(binaryImg, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//
//        for (const auto& contour : contours) {
//            RotatedRect rect = minAreaRect(contour);
//            Size2f size = rect.size;
//            float length = max(size.width, size.height);
//            float width = min(size.width, size.height);
//
//            //4. ɸѡ�������������У��ų������ŵƣ�������ȷ��϶̵�������
//            if (length > 30 && length < 150 && width > 10 && length / width > 1.5) {
//                armorRects.push_back(rect);
//            }
//        }
//        return !armorRects.empty();
//    }
//
//    // 5.����װ�װ���κ����ĵ�
//    void drawResult(Mat& displayImg) {
//        for (const auto& rect : armorRects) {
//            Point2f vertices[4];
//            rect.points(vertices);
//            for (int i = 0; i < 4; ++i) {
//                line(displayImg,//����
//                    vertices[i], vertices[(i + 1) % 4],//ʼ�յ�
//                    Scalar(0, 255, 0),//��ɫ
//                    2);//�߿�
//            }
//            Point center = Point(rect.center.x, rect.center.y);
//            circle(displayImg, center, 3, Scalar(0, 0, 255), -1);
//        }
//    }
//
//    //6. �������̣�Ԥ���� �� ��� �� ����
//    bool process(Mat& displayImg) {
//        displayImg = srcImg.clone();
//        if (!preprocess()) return false;
//        if (!detectArmor()) return false;
//        drawResult(displayImg);
//        return true;
//    }
//};
//
//int main() {
//    Mat img = imread("D:/images/armor_image.jpg");
//    if (img.empty()) {
//        cerr << "�޷���ȡͼ������·����" << endl;
//        return -1;
//    }
//
//    ArmorDetector detector(img);
//    Mat resultImg;
//    bool success = detector.process(resultImg);
//	  //7. ��ʾ���
//    if (success) {
//        cout << "�ɹ�ʶ��װ�װ壡" << endl;
//    }
//    else {
//        cout << "δʶ�𵽣��ɵ���HSV��Χ��ɸѡ������" << endl;
//    }
//    imshow("װ�װ�ʶ����", resultImg);
//    waitKey(0);  // ��������رմ���
//    return 0;
//}