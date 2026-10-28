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

    // 숫자와 연산자를 배열로 정리
    long long nums[4] = { a, b, c, d };
    char ops[3] = { op1, op2, op3 };
    int n = 4;

    // 곱셈, 나눗셈 먼저 처리: 계산한 값으로 두 숫자를 합치고 뒤를 한 칸씩 당김
    for (int i = 0; i < n - 1; )
    {
        if (ops[i] == '*' || ops[i] == '/')
        {
            nums[i] = calculate(nums[i], nums[i + 1], ops[i]);
            for (int j = i + 1; j < n - 1; j++)
                nums[j] = nums[j + 1];
            for (int j = i; j < n - 2; j++)
                ops[j] = ops[j + 1];
            n--;
        }
        else
            i++;
    }

    // 남은 덧셈, 뺄셈을 왼쪽부터 처리
    long long result = nums[0];
    for (int i = 0; i < n - 1; i++)
        result = calculate(result, nums[i + 1], ops[i]);

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