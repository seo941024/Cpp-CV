#include <iostream>
#include <bitset>
#include <climits>
using namespace std;

// 연산 함수
long long calculate(long long a, long long b, char op)
{
    if (op == '+')
        return a + b;
    else if (op == '-')
        return a - b;
    else if (op == '*')
        return a * b;
    else if (op == '/')
        return a / b;

    return 0;
}

int main()
{
    int a, b, c, d;
    char op1, op2, op3;

    cout << "첫 번째 숫자를 입력하세요: ";
    cin >> a;

    cout << "첫 번째 연산자를 입력하세요 (+, -, *, /): ";
    cin >> op1;

    cout << "두 번째 숫자를 입력하세요: ";
    cin >> b;

    cout << "두 번째 연산자를 입력하세요 (+, -, *, /): ";
    cin >> op2;

    cout << "세 번째 숫자를 입력하세요: ";
    cin >> c;

    cout << "세 번째 연산자를 입력하세요 (+, -, *, /): ";
    cin >> op3;

    cout << "네 번째 숫자를 입력하세요: ";
    cin >> d;

    // 중간 계산용 변수
    long long first = 0;
    long long second = 0;
    long long result = 0;

    char opA, opB;

    // 곱셈, 나눗셈 먼저 처리
    // a op1 b
    if (op1 == '*' || op1 == '/')
    {
        first = calculate(a, b, op1);
        opA = op2;
    }
    else
    {
        first = a;
        opA = op1;
    }

    // op2 c
    if (op2 == '*' || op2 == '/')
    {
        if (op1 == '*' || op1 == '/')
            first = calculate(first, c, op2);
        else
            first = calculate(b, c, op2);

        opB = op3;
    }
    else
    {
        if (op1 == '+' || op1 == '-')
            second = b;

        opB = op2;
    }

    // c op3 d
    if (op3 == '*' || op3 == '/')
    {
        second = calculate(c, d, op3);
    }
    else
    {
        second = c;
    }

    // 남은 연산자 처리

    if (op1 == '+' || op1 == '-')
        result = calculate(a, second, op1);
    else
        result = first;

    if (op2 == '+' || op2 == '-')
    {
        if (op3 == '*' || op3 == '/')
            result = calculate(result, second, op2);
        else
            result = calculate(result, c, op2);
    }

    if (op3 == '+' || op3 == '-')
        result = calculate(result, d, op3);

    // 오버/언더플로우 발생
    if (result > INT_MAX || result < INT_MIN)
    {
        cout << "오버/언더플로우 발생" << endl;
        return 0;
    }

    int finalResult = (int)result;

    // 출력
    cout << "\n[결과]" << endl;

    cout << "Bin : " << bitset<32>(finalResult) << endl;
    cout << "Dec : " << finalResult << endl;
    cout << "Hex : 0x" << hex << uppercase << finalResult << endl;

    return 0;
}