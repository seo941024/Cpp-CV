#include <iostream>
using namespace std;

int main()
{
    unsigned long times1, times, days, hours, minutes, seconds;
    cout << "초 단위의 숫자를 입력하세요 : ";
    cin >> times1;

    days = times1 / 86400;
    times = times1 % 86400;

    hours = times / 3600;
    times = times % 3600;

    minutes = times / 60;
    seconds = times % 60;

    cout << "입력하신 " << times1 << "초는\n"
         << days << "일 " << hours << "시간 " << minutes << "분 " << seconds << "초 입니다.";
}