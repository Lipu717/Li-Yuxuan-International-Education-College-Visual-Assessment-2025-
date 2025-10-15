// ʶ����Ƶ��ɫװ�װ�
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <chrono>
using namespace cv;
using namespace std;
using namespace chrono;

// �����ṹ��
struct LightBar {
    RotatedRect rrect; // ��ת����
    Point center;      // ���ĵ�
    double length;     // ���߳���
};

// װ�װ�ṹ��
struct Armor {
    RotatedRect rect; // װ�װ���ת����
    Point center;     // ���ĵ�
};

// ɸѡ��������
vector<LightBar> findLightBars(const Mat& mask) {
    vector<vector<Point>> contours;
    findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<LightBar> lightBars;
    for (const auto& contour : contours) {
        if (contour.size() < 4) continue; // ���˹�С����

        // �����ת���Σ���Ӧ��б������
        RotatedRect rrect = minAreaRect(contour);
        float length = max(rrect.size.width, rrect.size.height); // ����
        float width = min(rrect.size.width, rrect.size.height);  // �̱�

        // �ſ�ɸѡ��������Ӧ���С������
        if (length / width < 2 || length < 15 || width < 3)
            continue; // �����>2�����ȡ�15����ȡ�3

        lightBars.push_back({ rrect, (Point)rrect.center, length });
    }
    return lightBars;
}

// ƥ��װ�װ庯�����ſ�������
vector<Armor> matchArmors(const vector<LightBar>& lightBars) {
    vector<Armor> armors;
    for (size_t i = 0; i < lightBars.size(); i++) {
        for (size_t j = i + 1; j < lightBars.size(); j++) {
            const LightBar& lb1 = lightBars[i];
            const LightBar& lb2 = lightBars[j];

            // ����1���ǶȲ��25�㣨�������ƽ�У�
            if (abs(lb1.rrect.angle - lb2.rrect.angle) > 25) continue;

            // ����2�����ȱȡ�0.3�������Ȳ������
            double lengthRatio = min(lb1.length, lb2.length) / max(lb1.length, lb2.length);
            if (lengthRatio < 0.3) continue;

            // ����3�����ľ�Ϊ�������ȵ�0.7~4�������������
            double centerDist = norm(lb1.center - lb2.center);
            double avgLength = (lb1.length + lb2.length) / 2;
            if (centerDist / avgLength < 0.7 || centerDist / avgLength > 4.0) continue;

            // ����װ�װ����
            Point2f pts[8];
            lb1.rrect.points(pts);
            lb2.rrect.points(pts + 4);
            Point2f armorPts[4] = { pts[0], pts[2], pts[4], pts[6] };
            RotatedRect armorRect = minAreaRect(Mat(4, 1, CV_32FC2, armorPts));

            armors.push_back({ armorRect, armorRect.center });
        }
    }
    return armors;
}

int main() {
    // 1. ��ȡ������Ƶ
    VideoCapture cap("D:/images/װ�װ� - ��.mp4"); // �滻Ϊ�����Ƶ·��
    if (!cap.isOpened()) {
        cerr << "�޷�����Ƶ��" << endl;
        return -1;
    }

    Mat frame, resizedFrame, hsv, mask, mask1, mask2;
    // ��ɫHSV��ֵ���ſ��Ͷ�/�������ޣ���Ӧ��వ������
    Scalar lowerRed1(0, 60, 60), upperRed1(10, 255, 255);   // ������1
    Scalar lowerRed2(160, 60, 60), upperRed2(180, 255, 255); // ������2

    // ��̬ѧ�ˣ�5x5��ǿȥ��Ͳ�ȫ������
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    int frameCount = 0; // ֡��

    //��׽һ֡ 1.  �����Ƶ֡�Ƿ�Ϊ�գ����Ϊ��������ѭ��
    //         2.  ����ǰ֡�ĳߴ���Сһ�룬��Ⱥ͸߶ȶ�����2
    while (cap.read(frame)) {
        frameCount++;
        if (frame.empty()) break;

        // ��Сͼ��1/2�ߴ磩
        resize(frame, resizedFrame, Size(frame.cols / 2, frame.rows / 2));

        // ��ʱ��ʼ
        auto start = high_resolution_clock::now();

        // 1. BGRתHSV
        cvtColor(resizedFrame, hsv, COLOR_BGR2HSV);

        // 2. ��ȡ��ɫ��������
        inRange(hsv, lowerRed1, upperRed1, mask1);
        inRange(hsv, lowerRed2, upperRed2, mask2);
        mask = mask1 | mask2; // �ϲ���ɫ����

        // 3. ��̬ѧ����ȥ��+��ȫ��
        morphologyEx(mask, mask, MORPH_OPEN, kernel);  // ������ȥ��
        morphologyEx(mask, mask, MORPH_CLOSE, kernel); // �����㲹ȫ

        // 4. ɸѡ����
        vector<LightBar> lightBars = findLightBars(mask);

        // 5. ƥ��װ�װ�
        vector<Armor> armors = matchArmors(lightBars);

        // 6. ���ƽ��������+װ�װ�+���ĵ㣩
        Mat show = resizedFrame.clone();

        // ���Ƶ�������ѡ�����ڵ��Ե���ʶ��Ч����
        for (const auto& lb : lightBars) {
            Point2f pts[4];
            lb.rrect.points(pts);
            for (int i = 0; i < 4; i++) {
                line(show, pts[i], pts[(i + 1) % 4], Scalar(255, 0, 0), 2); // ��ɫ�߱�ǵ���
            }
        }

        // ����װ�װ����������ĵ㣨���ģ��޸�ԭ���������װ�װ�ѭ����ʹ��armor��
        for (const auto& armor : armors) {
            // ����װ�װ�����
            Point2f pts[4];
            armor.rect.points(pts);
            for (int i = 0; i < 4; i++) {
                line(show, pts[i], pts[(i + 1) % 4], Scalar(0, 255, 0), 2); // ��ɫ�߱��װ�װ�
            }
            // ����װ�װ����ĵ㣨��ɫʵ�ĵ㣩
            circle(show, armor.center, 3, Scalar(0, 0, 255), -1);
        }

        // 7. ��ʾ��ʱ��֡����
        auto end = high_resolution_clock::now();
        double elapsedMs = duration_cast<microseconds>(end - start).count() / 1000.0;
        putText(show, "��ʱ: " + to_string(elapsedMs) + " ms",
            Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 255), 2); // ��ɫ����
        putText(show, "֡��: " + to_string(frameCount),
            Point(10, 60), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 255), 2); // ��ɫ����

        // 8. ��ʾ���
        imshow("װ�װ�ʶ����", show);
        if (waitKey(30) == 27) break; // ESC���˳�
    }

    // �ͷ���Դ
    cap.release();
    destroyAllWindows();
    return 0;
}