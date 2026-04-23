#include <iostream>
using namespace std;

// chcp 65001
int main()
{
    int num1;
    int num2;
    int sum;
    // 입력 받기
    cout << "Enter Num1 : ";
    cin >> num1;
    cout << "Enter Num2 : ";
    cin >> num2;
    // 계산과 결과 저장
    sum = num1 + num2;
    // 출력
    cout << "Num Sum is :" << sum;
    return 0;
}