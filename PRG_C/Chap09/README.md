# Chap09 · 참조·포인터·동적 메모리

변수의 별칭인 참조와 주소를 담는 포인터로 값 교환·배열 접근 구현, 힙 메모리 동적 할당과 해제로 가변 크기 배열·파스칼 삼각형·Course·Matrix 클래스 구현.

## 다룬 개념

| 개념 | 뜻과 사용 방법 |
|---|---|
| 참조 변수 | 이미 있는 변수에 붙이는 또 다른 이름. `int& rScore = score;`로 선언하고 참조로 읽거나 바꾸면 원래 변수에 그대로 반영 |
| 참조 반환 | 함수가 복사본 대신 객체 자체를 돌려주는 방식. `Fraction& larger(...)`가 두 분수 중 큰 객체를 반환 |
| 주소 연산자 `&`와 `sizeof` | `&변수`는 변수가 저장된 메모리 주소, `sizeof`는 자료형이 차지하는 바이트 수 |
| 포인터 | 다른 변수의 주소를 저장하는 변수. `int* pScore = &score;`로 주소를 담고 `*pScore`로 그 주소의 값에 간접 접근 |
| 포인터 전달 | 함수에 변수 주소를 넘기는 방식. `swap(&x, &y)`로 호출하고 함수 안에서 `*pX`로 원본 변경, 객체 포인터는 `->`로 멤버 호출 |
| 포인터 산술 | 포인터에 정수를 더하면 자료형 크기만큼 주소가 이동하는 규칙. 배열 이름이 첫 원소 주소이므로 `*(numbers + i)`가 `numbers[i]`와 같은 값 |
| 2차원 배열 포인터 | 행 하나를 가리키는 포인터 `int (*m)[4]`. 2차원 배열을 함수에 넘겨 `m[i][j]`로 접근 |
| 메모리 영역 | 전역·정적 변수는 프로그램이 끝날 때까지 남는 정적 메모리, 지역 변수는 함수가 끝나면 사라지는 스택, `new`로 만든 값은 `delete`로 해제할 때까지 남는 힙에 저장 |
| 동적 할당 `new`·`delete` | 실행 중에 필요한 크기만큼 힙 메모리를 잡고 다 쓰면 돌려주는 연산. `new int[size]`로 배열 생성, `delete[]`로 해제 |
| 래기드 배열 | 행마다 길이가 다른 2차원 배열. `int**`에 행 포인터 배열을 만들고 `i`행에 `new int[i + 1]` 할당 |
| 소멸자에서 힙 해제 | 생성자에서 `new`로 잡은 메모리를 소멸자에서 `delete[]`로 돌려주는 구조. 객체가 사라질 때 메모리와 열린 파일도 함께 정리 |

## 파일별 내용

| 파일 | 내용 | 핵심 코드 |
|---|---|---|
| [Prg9-1.cpp](Prg9-1.cpp) | 원래 변수와 참조 변수로 같은 값 출력 | `int& rScore = score;` |
| [Prg9-2.cpp](Prg9-2.cpp) | 참조 전달로 두 변수 값 교환 | `void swap(int& rX, int& rY)` |
| [Prg9-3.cpp](Prg9-3.cpp) | 두 분수 중 큰 객체를 참조로 반환받아 출력. 포함하는 `fraction.h`는 [`../Chap07`](../Chap07) 폴더에 있는 구성 | `Fraction& larger(Fraction&, Fraction&)` |
| [Prg9-4.cpp](Prg9-4.cpp) | `bool`·`int`·`double` 변수의 크기·값·주소 출력 | `sizeof(flag)`, `&flag` |
| [Prg9-5.cpp](Prg9-5.cpp) | 변수 값에 이름으로 접근, 포인터로 간접 접근 | `int* pScore = &score;`, `*pScore` |
| [Prg9-6.cpp](Prg9-6.cpp) | 포인터 전달로 두 변수 값 교환 | `swap(&x , &y)`, `*pX= *pY;` |
| [Prg9-7.cpp](Prg9-7.cpp) | 분수 객체 포인터를 받아 큰 쪽 포인터 반환. `fraction.h`는 [`../Chap07`](../Chap07) 폴더에 있는 구성 | `Fraction* larger(Fraction*, Fraction*)`, `->print()` |
| [Prg9-8.cpp](Prg9-8.cpp) | 배열 원소마다 포인터 산술 주소와 `&` 주소 출력 | `arr + i`, `&arr[i]` |
| [Prg9-9.cpp](Prg9-9.cpp) | 인덱스와 포인터 두 방식으로 배열 원소 출력 | `numbers[i]`, `*(numbers + i)` |
| [Prg9-10.cpp](Prg9-10.cpp) | 배열 포인터를 받아 원소 합계 계산 | `int getSum(const int* p, int size)`, `*(p++)` |
| [Prg9-11.cpp](Prg9-11.cpp) | 포인터로 앞뒤 원소를 바꿔 배열 뒤집기 | `*(pArr + i) = *(pArr + j);` |
| [Prg9-12.cpp](Prg9-12.cpp) | 2차원 배열을 행 포인터로 받아 출력 | `void print(int(*m)[4], int rows)` |
| [Prg9-13.cpp](Prg9-13.cpp) | 전역 변수·전역 정적 변수·지역 정적 변수 값 출력 | `static int second`, `static int third` |
| [Prg9-14.cpp](Prg9-14.cpp) | 입력한 크기의 배열을 힙에 만들고 포인터로 입력·출력 후 해제 | `pArray = new int[size];`, `delete [ ] pArray;` |
| [Prg9-15.cpp](Prg9-15.cpp) | 래기드 배열로 파스칼 삼각형을 만들어 `(x + y)^n`의 이항계수 출력 | `new int* [n + 1]`, `new int[i + 1]`, `pascal[i - 1][j - 1] + pascal[i - 1][j]` |
| [Prg9-16.cpp](Prg9-16.cpp) | 학생 성적을 처리하는 Course 클래스 선언 코드, `course.h` 내용. 클래스 안에 Student 구조체와 private 헬퍼 함수 선언 | `struct Student`, `Student* students;` |
| [Prg9-17.cpp](Prg9-17.cpp) | Course 생성자에서 파일 열기·힙 배열 할당·학점·평균·편차 계산·출력, 소멸자에서 배열 해제와 파일 닫기 | `students = new Student[numOfStds];`, `delete[] students;` |
| [Prg9-18.cpp](Prg9-18.cpp) | 학생 수와 `scores.dat` 경로를 넘겨 Course 객체를 만드는 애플리케이션 코드 | `Course course(10, "scores.dat");` |
| [Prg9-19.cpp](Prg9-19.cpp) | 행렬 크기와 `int**` 포인터를 가진 Matrix 클래스 선언 코드, `matrix.h` 내용 | `int** ptr;`, `add`, `subtract`, `multiply` |
| [Prg9-20.cpp](Prg9-20.cpp) | Matrix 생성자의 2차원 힙 배열 할당, 소멸자 해제, 난수 초기화, 덧셈·뺄셈·곱셈 정의 코드 | `ptr[i] = new int[colSize];`, `assert(colSize == second.rowSize);` |
| [Prg9-21.cpp](Prg9-21.cpp) | 3행 4열·4행 2열 행렬을 만들어 덧셈·뺄셈·곱셈 결과 출력하는 애플리케이션 코드 | `matrix1.multiply(matrix3, mulResult);` |

`scores.dat`: `Prg9-18`이 읽는 학번과 점수 목록.

`Prg9-16`~`Prg9-18`, `Prg9-19`~`Prg9-21`은 각각 `course.h`·`matrix.h` 인터페이스 파일과 구현·애플리케이션 파일로 나눠 저장해야 컴파일되는 코드 조각.

## 참조와 포인터 비교

| 구분 | 참조 | 포인터 |
|---|---|---|
| 선언 | `int& r = x;` | `int* p = &x;` |
| 값 접근 | `r` 그대로 사용 | `*p`로 간접 접근 |
| 교환 함수 호출 | `swap(x, y)` | `swap(&x, &y)` |
| 객체 멤버 호출 | `.` | `->` |
| 예제 | [Prg9-1.cpp](Prg9-1.cpp), [Prg9-2.cpp](Prg9-2.cpp), [Prg9-3.cpp](Prg9-3.cpp) | [Prg9-5.cpp](Prg9-5.cpp), [Prg9-6.cpp](Prg9-6.cpp), [Prg9-7.cpp](Prg9-7.cpp) |
