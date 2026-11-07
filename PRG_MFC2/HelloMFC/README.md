# HelloMFC · 최소 MFC 창

마법사 없이 `CWinApp`·`CFrameWnd`를 상속한 클래스와 메시지 맵만으로 HelloSDK와 같은 동작을 하는 MFC 창 구현.

## 다룬 개념

| 개념 | 뜻과 사용 방법 |
|---|---|
| MFC | Win32 API를 C++ 클래스로 감싼 마이크로소프트 라이브러리. 창 클래스 등록과 메시지 루프를 프레임워크가 대신 처리 |
| 애플리케이션 클래스 `CWinApp` | 프로그램 하나를 나타내는 클래스. 전역 객체 `theApp`이 하나 있어야 하고, 시작할 때 호출되는 `InitInstance`를 재정의해 메인 창 생성 |
| 프레임 창 `CFrameWnd` | 제목 표시줄과 테두리를 가진 메인 창 클래스. 생성자에서 `Create(NULL, _T("HelloMFC"))`로 창 생성 |
| 메시지 맵 | 메시지와 처리 함수를 연결하는 표. 클래스 선언에 `DECLARE_MESSAGE_MAP()`, 구현 쪽 `BEGIN_MESSAGE_MAP`과 `END_MESSAGE_MAP` 사이에 `ON_WM_PAINT()`처럼 항목 등록 |
| 메시지 처리 함수 | 메시지가 오면 프레임워크가 호출하는 `afx_msg` 멤버 함수. `ON_WM_PAINT()`는 `OnPaint`, `ON_WM_LBUTTONDOWN()`은 `OnLButtonDown`과 연결 |
| `CPaintDC` | `WM_PAINT` 처리용 디바이스 컨텍스트 클래스. 생성자와 소멸자가 `BeginPaint`·`EndPaint`를 대신 호출 |

## 동작 흐름

| 사용자 동작 | 메시지 맵 항목 | 처리 함수 | 결과 |
|---|---|---|---|
| 프로그램 실행 | - | `CHelloApp::InitInstance` | `new CMainFrame`으로 메인 창 생성, `ShowWindow`로 표시 |
| 창이 화면에 그려질 때 | `ON_WM_PAINT()` | `CMainFrame::OnPaint` | 창 안 `(100, 100)` 위치에 `Hello, MFC` 출력 |
| 창 안에서 마우스 왼쪽 버튼 클릭 | `ON_WM_LBUTTONDOWN()` | `CMainFrame::OnLButtonDown` | `마우스 클릭!` 메시지 상자 표시 |

## 파일별 내용

| 파일 | 내용 | 핵심 코드 |
|---|---|---|
| [HelloMFC.cpp](HelloMFC.cpp) | 애플리케이션 클래스 `CHelloApp`, 메인 창 클래스 `CMainFrame`, 전역 객체 `theApp`, 메시지 맵을 한 파일에 작성 | `class CHelloApp : public CWinApp`, `class CMainFrame : public CFrameWnd`, `BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)` |
| [HelloMFC.slnx](HelloMFC.slnx), [HelloMFC.vcxproj](HelloMFC.vcxproj), [HelloMFC.vcxproj.filters](HelloMFC.vcxproj.filters) | Visual Studio 프로젝트 생성 파일. MFC 동적 연결은 x64 디버그 구성에 설정 | - |

## HelloSDK와 비교

| 구분 | [HelloSDK](../HelloSDK/README.md) | HelloMFC |
|---|---|---|
| 시작 지점 | `WinMain` 작성 | `CWinApp::InitInstance` 재정의 |
| 창 등록·생성 | `RegisterClass`, `CreateWindow` | `CFrameWnd::Create` |
| 메시지 루프 | `GetMessage`·`DispatchMessage` 반복문 작성 | 프레임워크가 처리 |
| 메시지 분기 | `WndProc`의 `switch` | 메시지 맵 매크로 |
| 그리기 | `BeginPaint`·`TextOut`·`EndPaint` | `CPaintDC dc(this)`, `dc.TextOut` |
