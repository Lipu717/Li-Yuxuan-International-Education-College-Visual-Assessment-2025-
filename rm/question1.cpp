//#include <iostream>
//#include <cmath>
//#include <iomanip>
//using namespace std;
//
//// ���������ṹ��
//struct Point {
//    double x, y;
//    Point(double x = 0, double y = 0) : x(x), y(y) {}
//};
//
////Rect�ṹ��
//struct Rect {
//    int id;         // ����ID
//    int color;      // װ�װ���ɫ��0Ϊ��ɫ��1Ϊ��ɫ��
//    Point point;    // ���Ͻ�����
//    double width;   // ���
//    double height;  // �߶�
//
//    Rect(int id_val, int color_val, double x, double y, double width_val, double height_val)
//        : id(id_val), color(color_val), point(x, y), width(width_val), height(height_val)
//    {
//    }
//};
//
////Armor��
//class Armor {
//private:
//    Rect rect;  // װ�װ�� Rect �ṹ��
//
//public:
//    // Armor ��Ĺ��캯��
//    Armor(int id, int color, double x, double y, double width, double height)
//        : rect(id, color, x, y, width, height) {
//    }
//
//    // ����װ�װ���������ĺ���
//    Point Central_Point() {
//        double centerX = rect.point.x + rect.width / 2;
//        double centerY = rect.point.y + rect.height / 2;
//        return Point(centerX, centerY);
//    }
//
//    // ����װ�װ�Խ��߳��ȵĺ�����������λС����
//    double Diagonal() {
//        double diagonal = sqrt(pow(rect.width, 2) + pow(rect.height, 2));
//        return round(diagonal * 100) / 100;
//    }
//
//    // ���װ�װ� 4 ������ĺ����������Ͻ����꿪ʼ˳ʱ�������
//    void Armor_Point()
//    {
//        Point topLeft = rect.point;
//        Point topRight(rect.point.x + rect.width, rect.point.y);
//        Point bottomRight(rect.point.x + rect.width, rect.point.y + rect.height);
//        Point bottomLeft(rect.point.x, rect.point.y + rect.height);
//
//        cout << topLeft.x << " " << topLeft.y << " "
//            << topRight.x << " " << topRight.y << " "
//            << bottomRight.x << " " << bottomRight.y << " "
//            << bottomLeft.x << " " << bottomLeft.y << endl;
//    }
//
//    // ���װ�װ���ɫ�Ĺ���
//    string Armor_Color() {
//        string color;
//        if (rect.color == 0) {
//            color = "��ɫ";
//        }
//        else {
//            color = "��ɫ";
//        }
//        return color;
//    }
//
//    // ��ȡװ�װ�� ID
//    int GetId() {
//        return rect.id;
//    }
//};
//
//int main() {
//    int id, color;
//    double x, y, width, height;
//
//    // ��������ID����ɫ
//    cin >> id >> color;
//
//    // �������Ͻǵ�����Ϳ����
//    cin >> x >> y >> width >> height;
//
//    // ���� Armor ����
//    Armor armor(id, color, x, y, width, height);
//
//    // �������ID����ɫ
//    cout << armor.GetId() << " " << (color == 0 ? "��ɫ" : "��ɫ") << endl;
//
//    // ���װ�װ���������ͶԽ��߳���
//    Point center = armor.Central_Point();
//    double diagonal = armor.Diagonal();
//    cout << center.x << " " << center.y << " " << diagonal << endl;
//
//    // ���װ�װ� 4 ������
//    armor.Armor_Point();
//
//    return 0;
//}