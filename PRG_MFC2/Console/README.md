# Console · MFC 콘솔

창 없는 콘솔 프로그램에서 MFC를 초기화하고 문자열 리소스를 읽어 출력하는 MFC 콘솔 애플리케이션.

## 다룬 개념

| 개념 | 뜻과 사용 방법 |
|---|---|
| MFC 콘솔 애플리케이션 | 창 없이 명령 창에서 실행하면서 `CString` 같은 MFC 클래스를 쓰는 프로그램. 하위 시스템 Console, 시작 함수 `main` |
| `AfxWinInit` | 창 프로그램이 아닌 곳에서 MFC를 쓸 수 있도록 초기화하는 함수. `GetModuleHandle(nullptr)`로 얻은 실행 파일 핸들을 넘기고, 실패하면 오류 문구 출력 후 반환 코드 1 |
| 문자열 리소스 | 화면 문구를 코드 대신 `.rc` 파일의 문자열 표에 두고 ID로 꺼내 쓰는 방식. `IDS_TEST`에 `연습용입니다.` 저장 |
| `CString::LoadString` | 리소스 ID로 문자열 표의 문구를 읽어 `CString`에 담는 함수 |
| `_tprintf`와 `_T` | 유니코드·멀티바이트 설정에 맞춰 바뀌는 출력 함수와 문자열 매크로. `_T("Hello from %s!\n")` 형식으로 리소스 문구 출력 |

## 실행 흐름

1. `GetModuleHandle(nullptr)`로 실행 파일 핸들 확인.
2. `AfxWinInit`로 MFC 초기화.
3. `str.LoadString(IDS_TEST)`로 문자열 리소스 읽기.
4. `_tprintf`로 `Hello from %s!` 형식 출력.
5. `getchar()`로 키 입력을 기다린 뒤 종료.

## 파일별 내용

| 파일 | 내용 | 핵심 코드 |
|---|---|---|
| [Console.cpp](Console.cpp) | 전역 `CWinApp theApp`, MFC 초기화, 문자열 리소스 출력 | `AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0)`, `str.LoadString(IDS_TEST)` |
| [Console.rc](Console.rc) | 문자열 표에 `IDS_APP_TITLE`, `IDS_TEST` 정의 | `STRINGTABLE`, `IDS_TEST "연습용입니다."` |
| [Console.h](Console.h) | `Resource.h` 포함 | `#include "Resource.h"` |
| [Resource.h](Resource.h), [framework.h](framework.h), [pch.h](pch.h), [pch.cpp](pch.cpp), [targetver.h](targetver.h), [Console.slnx](Console.slnx), [Console.vcxproj](Console.vcxproj), [Console.vcxproj.filters](Console.vcxproj.filters) | Visual Studio 프로젝트 생성 파일. `Resource.h`에 리소스 ID, `framework.h`에 MFC 헤더 포함, 하위 시스템 Console, MFC 동적 연결 | - |
