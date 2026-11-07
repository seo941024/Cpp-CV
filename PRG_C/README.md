# PRG_C · C++ 문법 예제

프로그램 구조와 입출력부터 선택문·반복문·함수·클래스·배열·포인터·동적 메모리까지 장별 C++ 콘솔 프로그램과 과제 구현.

## 장 목록

| 장 | 폴더 | 주제 | 핵심 개념 |
|---|---|---|---|
| 2장 | 이 폴더 | 프로그램 구조 | `main`, `cout`, `cin`, 두 수 합, 성장 비전 리포트 과제, 숫자 4개 계산기 |
| 3장 | [Chap03](Chap03/README.md) | 표현식과 자료형 | 리터럴, 연산자 우선순위·결합 방향, 복합 할당, 암묵적·명시적 형 변환, 오버플로우, 입출력 조정자 |
| 4장 | [Chap04](Chap04/README.md) | 선택문 | `if-else` 중첩, 다중 분기 학점, 논리 연산 윤년 판정, `switch` 낙하 실행, 조건 연산자, 누진 세율 |
| 5장 | [Chap05](Chap05/README.md) | 반복문 | 카운터·센티넬·EOF 제어 `while`, `ifstream` 파일 합계, `do-while` 입력 검증, 중첩 반복 달력·곱셈표, all·any 판정 |
| 6장 | [Chap06](Chap06/README.md) | 함수 | `<cmath>`·`<cctype>`·`<ctime>`, 난수 추측 게임, 값 전달과 참조 전달, 기본 매개변수, 오버로딩, 셰도잉, `static` 지역 변수 |
| 7장 | [Chap07](Chap07/README.md) | 클래스 | 생성자·복사 생성자·소멸자, 접근자·설정자, `static` 객체 수, `assert` 불변 조건, 헤더 분리, `makefile` 분할 컴파일 |
| 8장 | [Chap08](Chap08/README.md) | 배열 | 역순 출력, 파일 입출력, 객체 배열, 배열 매개변수, 병렬 배열, 2차원 배열, 빈도 히스토그램, 선형 변환 |
| 9장 | [Chap09](Chap09/README.md) | 참조·포인터·동적 메모리 | 참조 변수, 포인터 전달, 포인터 산술, 힙 배열, 래기드 배열 이항계수, 소멸자에서 힙 해제, Matrix 연산 |
| 과제 6 | [HW6](HW6/README.md) | 제품 등록 수 관리 | `static` 멤버 변수·함수, 생성자 증가·소멸자 감소, 블록 종료 시 소멸 시점, `assert` 가격 검증 |

## 다룬 개념

이 폴더 바로 아래 파일 기준.

| 개념 | 뜻과 사용 방법 |
|---|---|
| `main` 함수 | 프로그램이 시작되는 함수. `int main()`이 `0`을 반환하면 정상 종료 |
| `#include`와 `using namespace std` | `#include`는 헤더 파일을 불러오는 전처리 지시문, `using namespace std`는 `std::` 접두어를 생략하게 하는 선언. `Prg2-1.cpp`는 `std::cout`, 나머지는 `using namespace std` 사용 |
| 표준 입출력 `cout`·`cin` | `cout <<`로 화면에 출력하고 `cin >>`로 키보드 입력을 변수에 저장. `endl`로 줄바꿈 |
| `string` | 문자열을 담는 표준 라이브러리 클래스. 이름과 비전 입력에 사용 |
| 명시적 형 변환 | 원하는 자료형을 지정하는 변환. `(double)current`로 정수 나눗셈 대신 실수 나눗셈 수행 |
| 연산자 우선순위 처리 | 곱셈·나눗셈을 덧셈·뺄셈보다 먼저 계산하는 규칙. `Calc.cpp`에서 숫자 배열과 연산자 배열로 구현 |
| 범위 검사 `INT_MAX`·`INT_MIN` | `<climits>`에 정의된 `int` 최대·최소값. `long long`으로 받은 결과가 이 범위를 넘으면 오버플로우로 처리 |
| `bitset`과 `hex` | `bitset<32>`는 정수를 32비트 2진수로 출력, `hex`·`uppercase`는 대문자 16진수로 출력 |

## 파일별 내용

| 파일 | 내용 | 핵심 코드 |
|---|---|---|
| [hello.cpp](hello.cpp) | `Hello world!` 출력 | `cout << "Hello world!" << endl;` |
| [Prg2-1.cpp](Prg2-1.cpp) | 프로그램 구조 안내 문장 출력, `std::` 접두어 사용 | `std::cout`, `std::endl` |
| [Prg2-2.cpp](Prg2-2.cpp) | `*` 줄을 여러 번 출력해 사각형 모양 표시 | `cout << "******" << endl;` |
| [prg2-3.cpp](prg2-3.cpp) | 두 정수를 입력받아 합 출력 | `cin >> num1;`, `sum = num1 + num2;` |
| [Homework.cpp](Homework.cpp) | 이름·나이·비전·목표 수치·현재 수치·활성화 여부를 입력받아 달성률과 운영 상태를 담은 성장 비전 리포트 출력 | `string name;`, `(double)current / want * 100`, `if (activity == true)` |
| [Calc.cpp](Calc.cpp) | 숫자 4개와 연산자 3개를 입력받아 곱셈·나눗셈 우선 규칙으로 계산, 결과를 2진·10진·16진으로 출력 | `long long nums[4]`, `calculate`, `INT_MAX`, `bitset<32>` |
| [cpp_class.cpp](cpp_class.cpp) | 빈 파일 | - |

## Calc.cpp 계산 순서

1. 입력한 숫자는 `nums`, 연산자는 `ops` 배열에 정리.
2. 왼쪽부터 `*`·`/`를 만나면 앞뒤 두 숫자를 계산 결과 하나로 합치고 뒤쪽 원소를 한 칸씩 당김.
3. 남은 `+`·`-`를 왼쪽부터 적용.
4. `long long` 결과가 `INT_MIN`~`INT_MAX` 밖이면 `오버/언더플로우 발생` 출력, 범위 안이면 `Bin`·`Dec`·`Hex` 출력.

## 빌드

MSYS2 MinGW-w64 g++ 기준.

```bash
cd PRG_C/Chap05
g++ Prg5-11.cpp -o Prg5-11.exe
./Prg5-11.exe
```

- 한글 출력이 깨지면 PowerShell에서 `chcp 65001` 실행 후 실행.
- 분할 컴파일 예제는 [Chap07](Chap07/README.md), [HW6](HW6/README.md)의 빌드 설명 참고.
