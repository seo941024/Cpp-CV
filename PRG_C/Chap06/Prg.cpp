#include <iostream>
using namespace std;

// ① 함수 정의: dan을 받아서 해당 단의 가로 한 줄을 출력
void printDan(int dan)
{
    for (int i = 1; i <= 9; i++)
    {
        cout << dan << "x" << i << "=" << dan * i << "\t";
    }
    cout << endl;
}

int main()
{

    // ② 열 헤더 출력 (2단 ~ 9단)
    for (int dan = 2; dan <= 9; dan++)
    {
        cout << dan << "단\t";
    }
    cout << endl;

    // ③ 구구단 본문 출력
    for (int i = 1; i <= 9; i++)
    { // i: 곱하는 수 (1~9)
        for (int dan = 2; dan <= 9; dan++)
        { // dan: 단 (2~9)
            cout << dan << "x" << i << "=" << dan * i << "\t";
        }
        cout << endl; // 한 줄 끝나면 줄바꿈
    }

    return 0;
}

void func()
{
    static int count = 0; // 정적 지역변수
    count++;
    cout << count << endl;
}
int main()
{
    func(); // 출력: 1
    func(); // 출력: 2
    func(); // 출력: 3
}