# Chap06 · 함수

표준 라이브러리 함수 활용, 사용자 정의 함수의 선언·정의·호출, 값 전달과 참조 전달, 기본 매개변수, 오버로딩, 변수 범위와 수명 예제와 정기 예금·적금 미래 가치 계산 구현.

## 다룬 개념

| 개념 | 뜻과 사용 방법 |
|---|---|
| 라이브러리 함수 | 표준 헤더에 미리 정의된 함수. `<cmath>`의 `abs`·`floor`·`ceil`·`log`·`pow`·`sqrt`·`sin`, `<cctype>`의 `isalpha`·`toupper`, `<ctime>`의 `time` 사용 |
| 난수 `rand`·`srand` | `rand`는 정수 난수를 만들고 `srand(time(0))`은 실행할 때마다 다른 난수가 나오도록 시작값 지정. `temp % (high - low + 1) + low`로 범위 조정 |
| 함수 선언과 정의 | 선언, 곧 프로토타입은 이름·매개변수·반환형만 알리고 정의는 실제 동작을 작성. `main` 위에 선언, 아래에 정의를 두는 구성 |
| `void` 함수와 반환값 함수 | `void` 함수는 값을 돌려주지 않고 출력 같은 부가 작용만 수행, 반환형이 있는 함수는 `return`으로 결과 전달. 입력·처리·출력을 각각 함수로 분리 |
| 값 전달 | 인수의 복사본을 매개변수로 받는 방식. 함수 안에서 바꿔도 호출한 쪽 변수는 그대로 |
| 참조 전달 | `int&`처럼 매개변수를 인수의 별칭으로 받는 방식. 함수 안에서 바꾸면 호출한 쪽 변수도 바뀌어 값 교환과 여러 결과 반환에 사용 |
| 기본 매개변수 | 인수를 생략했을 때 쓰는 값. 선언에만 `double hours = 40`을 적고 정의에서는 생략 |
| 함수 오버로딩 | 이름은 같고 매개변수 개수나 자료형이 다른 함수를 여러 개 두는 것. 인수 개수에 맞는 `max`가 호출되고, 매개변수가 많은 버전이 적은 버전을 재사용 |
| 셰도잉 | 안쪽 범위에 같은 이름의 변수를 선언하면 바깥 변수가 가려지는 현상. 블록 안 지역 변수, 전역 변수를 가리는 지역 변수 |
| 범위 해결 연산자 `::` | 가려진 전역 변수에 접근하는 연산자. `::num`으로 전역 변수 값 출력 |
| 자동·정적 지역 변수 | 자동 지역 변수는 호출마다 새로 만들어지고 초기화, `static` 지역 변수는 처음 한 번만 초기화되고 다음 호출까지 값 유지 |
| 변수 초기값 | 전역 변수와 정적 변수는 값을 주지 않으면 0으로 초기화, 자동 지역 변수는 초기화되지 않음 |

## 파일별 내용

| 파일 | 내용 | 핵심 코드 |
|---|---|---|
| [Prg6-1.cpp](Prg6-1.cpp) | `<cmath>` 수학 함수 결과 출력, 헤더 포함 방식 메모 주석 | `abs`, `floor`, `ceil`, `log10`, `exp`, `pow`, `sqrt` |
| [Prg6-2.cpp](Prg6-2.cpp) | 판별식으로 이차 방정식의 근 계산 | `pow(b, 2) - 4 * a * c`, `sqrt(term)` |
| [Prg6-3.cpp](Prg6-3.cpp) | 45도를 라디안으로 바꿔 삼각 함수 값 출력 | `PI / 4`, `sin`, `cos`, `tan` |
| [Prg6-4.cpp](Prg6-4.cpp) | 정다각형의 변 개수와 길이를 입력받아 둘레와 넓이 계산 | `tan(PI / n)`, `do-while` 입력 검증 |
| [Prg6-5.cpp](Prg6-5.cpp) | 입력 문자 중 알파벳 개수를 세고 대문자로 바꿔 출력 | `noskipws`, `isalpha`, `toupper` |
| [Prg6-6.cpp](Prg6-6.cpp) | `time(0)`의 경과 초로 현재 시·분·초 계산 | `elapsedSeconds % 60`, `elapsedHours % 24` |
| [Prg6-7.cpp](Prg6-7.cpp) | 범위 안 난수를 정해진 횟수 안에 맞히는 추측 게임 | `srand(time(0))`, `rand()`, `tryLimit` |
| [Prg6-8.cpp](Prg6-8.cpp) | 매개변수 없는 `void` 함수로 인사말 출력 | `void greeting()` |
| [Prg6-9.cpp](Prg6-9.cpp) | 크기를 매개변수로 받아 `*` 정사각형 출력 | `void pattern(int size)` |
| [Prg6-10.cpp](Prg6-10.cpp) | 양의 정수를 입력받아 반환하는 함수, 가장 오른쪽 숫자 출력 | `int getData()`, `number % 10` |
| [Prg6-11.cpp](Prg6-11.cpp) | 두 수 중 큰 수를 반환하는 함수 | `int larger(int fst, int snd)` |
| [Prg6-12.cpp](Prg6-12.cpp) | 입력·판정·출력 함수로 나눈 윤년 판정 | `int input()`, `bool process(int year)`, `void output(int year, bool result)` |
| [Prg6-13.cpp](Prg6-13.cpp) | 값 전달에서 매개변수를 바꿔도 인수가 그대로인 것 확인 | `void fun(int y)` |
| [Prg6-14.cpp](Prg6-14.cpp) | 참조 전달에서 매개변수 변경이 인수에 반영되는 것 확인 | `void fun(int& y)` |
| [Prg6-15.cpp](Prg6-15.cpp) | 참조 전달로 두 변수 값 교환 | `void swap(int& fst, int& snd)` |
| [Prg6-16.cpp](Prg6-16.cpp) | 짝수 여부를 불 값으로 반환 | `return ((y % 2) == 0);`, `boolalpha` |
| [Prg6-17.cpp](Prg6-17.cpp) | 점수 입력·학점 계산·결과 출력 함수로 성적 처리 | `getScore`, `findGrade`, `printResult` |
| [Prg6-18.cpp](Prg6-18.cpp) | 근무 시간을 생략하면 기본값 40시간으로 임금 계산 | `double calcEarnings(double rate, double hours = 40);` |
| [Prg6-19.cpp](Prg6-19.cpp) | 매개변수 개수가 다른 `max` 함수 오버로딩 | `return max(max(num1, num2), num3);` |
| [Prg6-20.cpp](Prg6-20.cpp) | 바깥 블록과 안쪽 블록의 같은 이름 변수 출력 | 블록 안 `int sum = 3;` |
| [Prg6-21.cpp](Prg6-21.cpp) | 지역 변수가 전역 변수를 가리는 셰도잉 | 전역 `int num = 5;`, 지역 `int num = 25;` |
| [Prg6-22.cpp](Prg6-22.cpp) | 범위 해결 연산자로 전역 변수 접근 | `::num` |
| [Prg6-23.cpp](Prg6-23.cpp) | 자동 지역 변수가 호출마다 다시 초기화되는 것 확인 | `int count = 0;`, `fun()` 반복 호출 |
| [Prg6-24.cpp](Prg6-24.cpp) | 정적 지역 변수가 호출 사이에 값을 유지하는 것 확인 | `static int count = 0;` |
| [Prg6-25.cpp](Prg6-25.cpp) | 전역·정적 지역·자동 지역 변수의 초기값 비교 | `int global;`, `static int sLocal;`, `int aLocal;` |
| [Prg6-26.cpp](Prg6-26.cpp) | 투자 금액·이율·기간을 입력받아 정기 예금 미래 가치 계산, 주요 함수와 부가 함수로 분리 | `input(double& invest, ...)`, `pow(factor, term)` |
| [Prg6-27.cpp](Prg6-27.cpp) | 매년 같은 금액을 넣는 정기 적금 미래 가치 계산 | `multiplier += pow(factor, i)` |
| [Prg.cpp](Prg.cpp) | 2단~9단 구구단을 곱하는 수 기준으로 나란히 출력하는 코드와 정적 지역 변수 호출 횟수 출력 코드를 한 파일에 둔 파일. `main` 함수가 두 개라 한 파일 그대로는 컴파일되지 않는 구성 | 중첩 `for`, `printDan(int dan)`, `static int count` |

## 값 전달과 참조 전달 비교

| 구분 | 값 전달 | 참조 전달 |
|---|---|---|
| 매개변수 선언 | `int y` | `int& y` |
| 함수가 받는 것 | 인수의 복사본 | 인수의 별칭 |
| 함수 안에서 변경 | 호출한 쪽 변수에 영향 없음 | 호출한 쪽 변수도 변경 |
| 예제 | [Prg6-13.cpp](Prg6-13.cpp) | [Prg6-14.cpp](Prg6-14.cpp), [Prg6-15.cpp](Prg6-15.cpp), [Prg6-26.cpp](Prg6-26.cpp) |
