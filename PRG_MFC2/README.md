# PRG_MFC2 · 윈도우 프로그래밍

Win32 API 창에서 시작해 MFC 메시지 맵, 문서·뷰 구조, 버튼 컨트롤, 대화 상자, 별도 스레드 추론 기반 웹캠 뷰어까지 구현한 Visual Studio 프로젝트 모음.

## 프로젝트 목록

| 프로젝트 | 주제 | 핵심 개념 |
|---|---|---|
| [HelloSDK](HelloSDK/README.md) | Win32 API 창 | `WNDCLASS` 등록, `CreateWindow`, 메시지 루프, `WndProc`의 `WM_PAINT`·`WM_LBUTTONDOWN` |
| [HelloMFC](HelloMFC/README.md) | 최소 MFC 창 | `CWinApp`·`CFrameWnd` 상속, 메시지 맵, `CPaintDC` |
| [Console](Console/README.md) | MFC 콘솔 | `AfxWinInit`, 문자열 리소스 `LoadString` |
| [App](App/README.md) | MDI 마법사 프로젝트 | 문서·뷰 구조, `CMultiDocTemplate`, 도킹 창 |
| [Button](Button/README.md) | 폼 뷰 버튼 컨트롤 | `CFormView`, 리소스 편집기로 체크 박스·라디오 버튼·그룹 상자 배치, `ON_BN_CLICKED` |
| [Button1](Button1/README.md) | 코드로 만든 버튼 컨트롤 | `CButton::Create`로 푸시·체크·3상태·라디오·그룹 상자 생성, `GetCheck` 상태를 메시지 상자로 출력 |
| [Diaglosbase](Diaglosbase/README.md) | 대화 상자 | 대화 상자 기반 애플리케이션, DDX, `CColorDialog`로 고른 색의 RGB·HEX 값 출력 |
| [WebCamViewer](WebCamViewer/README.md) | MFC 웹캠 뷰어와 YOLO 검출 | `SetTimer` 33ms 프레임 갱신, Picture Control에 DIB 출력, 별도 스레드에서 `readNetFromONNX`·`NMSBoxes` 추론, 화면 FPS 표시 |

## 공통 개념

| 개념 | 뜻과 사용 방법 |
|---|---|
| 메시지 | 클릭·다시 그리기·타이머 같은 사건을 운영체제가 창에 알리는 값. 모든 프로젝트가 메시지를 받아 처리하는 구조 |
| 메시지 맵 | MFC에서 메시지와 처리 함수를 연결하는 표. `BEGIN_MESSAGE_MAP`과 `END_MESSAGE_MAP` 사이에 `ON_WM_PAINT()`, `ON_BN_CLICKED(ID, 함수)`처럼 등록 |
| 리소스 | 메뉴·대화 상자·문자열·아이콘처럼 코드 밖 `.rc` 파일에 정의하는 화면 요소. `resource.h`의 ID로 코드에서 참조 |
| 문서·뷰 구조 | 데이터를 담는 문서 클래스와 화면을 그리는 뷰 클래스를 나누는 MFC 구조. App, Button, Button1이 사용 |
| 대화 상자 기반 구조 | 메인 창 자체가 대화 상자인 구조. Diaglosbase, WebCamViewer가 사용 |

## Visual Studio 프로젝트 생성 파일

각 폴더 README에서 한 줄로 묶은 파일의 역할.

| 파일 | 역할 |
|---|---|
| `pch.h`, `pch.cpp` | 미리 컴파일된 헤더. 자주 쓰는 헤더를 한 번만 컴파일해 빌드 시간 단축 |
| `framework.h` | MFC 핵심 헤더 `afxwin.h`, 확장 헤더 `afxext.h` 등을 포함하는 헤더 |
| `targetver.h` | 대상 Windows SDK 버전을 정하는 `SDKDDKVer.h` 포함 |
| `resource.h`, `Resource.h` | 리소스 ID 상수 정의 |
| `.rc`, `res/*.rc2` | 리소스 스크립트. 메뉴·대화 상자 템플릿·문자열 표·아이콘 연결 |
| `.slnx`, `.vcxproj`, `.vcxproj.filters` | 솔루션·프로젝트 설정과 솔루션 탐색기 폴더 구성 |
| `res/` | 아이콘, 도구 모음 비트맵 |

## 빌드

- Visual Studio에서 각 프로젝트 폴더의 `.slnx` 열기 후 빌드. 플랫폼 도구 집합 v145, 유니코드 문자 집합.
- `HelloSDK`를 제외한 프로젝트는 MFC 동적 연결. `HelloMFC`는 x64 디버그 구성에 MFC 동적 연결 설정.
- `WebCamViewer`는 OpenCV와 YOLO 모델 파일 준비 필요. 자세한 내용은 [WebCamViewer](WebCamViewer/README.md)의 빌드·실행 준비 항목.
