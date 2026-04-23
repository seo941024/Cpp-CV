#include <iostream>
#include <string>
using namespace std;

int main()
{
    string name;
    int age;
    string vision;
    int want;
    int current;
    int activity;

    std::cout << "이름을 입력하세요. ";
    cin >> name;
    std::cout << "나이를 입력하세요. ";
    cin >> age;
    std::cout << "나의 비전(한 단어)을 입력하세요. ";
    cin >> vision;
    std::cout << "목표 수치를 입력하세요(0~100). ";
    cin >> want;
    std::cout << "현재 진행 수치를 입력하세요(0~100). ";
    cin >> current;
    std::cout << "비전 활성화 여부 (1: 시작, 0: 대기). ";
    cin >> activity;

    double persentage = (double)current / want * 100;

    string activity_now;
    if (activity == true)
        activity_now = "진행 중";

    if (activity == false)
        activity_now = "대기 중";

    cout << "\n --- 나의 성장 비전 리포트 ---\n";
    cout << "성명 : " << name << "(" << age << "세)\n";
    cout << "목표 비전 : " << vision << "\n";
    cout << "진행도 : " << current << " / " << want << "\n";
    cout << "현재 달성률 : " << persentage << " %\n";
    cout << "운영 상태 : " << activity_now << "\n";
    cout << "------------------------------\n";

    return 0;
}