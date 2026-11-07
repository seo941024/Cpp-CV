# Button1 · 코드로 만든 버튼 컨트롤

SDI 마법사 프로젝트의 뷰가 생성될 때 `CButton::Create`로 푸시 버튼·체크 박스·3상태 체크 박스·라디오 버튼·그룹 상자를 만들고, 푸시 버튼 클릭 시 각 버튼 상태를 메시지 상자로 출력하는 프로그램.

## 다룬 개념

| 개념 | 뜻과 사용 방법 |
|---|---|
| `CButton` | 버튼 컨트롤을 감싼 MFC 클래스. 뷰 클래스의 멤버 변수로 두어 뷰 객체와 함께 생성·소멸 |
| `CButton::Create` | 캡션·스타일·위치 사각형·부모 창·컨트롤 ID를 받아 실행 중에 버튼 창을 만드는 함수. `WS_CHILD \| WS_VISIBLE`에 버튼 종류 스타일을 더해 지정 |
| 버튼 스타일 | `BS_PUSHBUTTON` 누르는 버튼, `BS_AUTOCHECKBOX` 켜짐·꺼짐 체크 박스, `BS_AUTO3STATE` 켜짐·꺼짐·중간 상태 체크 박스, `BS_AUTORADIOBUTTON` 묶음 안에서 하나만 고르는 라디오 버튼, `BS_GROUPBOX` 테두리와 제목만 있는 그룹 상자 |
| `WS_GROUP` | 라디오 버튼 묶음의 시작을 표시하는 창 스타일. 첫 라디오 버튼에 지정해 두 라디오 버튼을 한 묶음으로 구성 |
| `WM_CREATE`와 `OnCreate` | 창이 만들어진 직후 오는 메시지와 그 처리 함수. 뷰 창이 생긴 뒤 자식 컨트롤을 만드는 시점으로 사용 |
| `SetCheck`·`GetCheck` | 버튼 선택 상태를 정하고 읽는 함수. 0 꺼짐, 1 켜짐, 2 중간 상태 |
| `ON_BN_CLICKED` | 버튼 클릭 알림을 처리 함수에 연결하는 메시지 맵 매크로. 리소스 ID 대신 `Create`에 넘긴 숫자 ID `101`로 연결 |

## 동작 흐름

| 사용자 동작 | 메시지 맵 항목 | 처리 함수 | 결과 |
|---|---|---|---|
| 프로그램 실행, 뷰 생성 | `ON_WM_CREATE()` | `CButton1View::OnCreate` | 버튼 컨트롤 생성 후 체크 박스 켜짐, 3상태 체크 박스 중간 상태, 라디오 버튼 2 선택으로 초기화 |
| 체크 박스·라디오 버튼 클릭 | 연결 없음 | - | 자동 스타일로 선택 상태만 전환 |
| 푸시 버튼 클릭 | `ON_BN_CLICKED(101, OnButtonClicked)` | `CButton1View::OnButtonClicked` | 체크 박스·3상태 체크 박스·라디오 버튼 1·2의 `GetCheck` 값을 `버튼 상태: %d, %d, %d, %d` 형식 메시지 상자로 출력 |
| 뷰에서 마우스 오른쪽 버튼 놓기 | `ON_WM_RBUTTONUP()` | `OnRButtonUp`, `OnContextMenu` | 편집 팝업 메뉴 `IDR_POPUP_EDIT` 표시 |

## 파일별 내용

| 파일 | 내용 | 핵심 코드 |
|---|---|---|
| [Button1View.cpp](Button1View.cpp) | `OnCreate`에서 버튼 컨트롤 생성과 초기 상태 지정, 푸시 버튼 클릭 시 상태 메시지 상자 출력 | `m_3state.Create(_T("3상태 체크 박스"), WS_CHILD \| WS_VISIBLE \| BS_AUTO3STATE, CRect(20, 100, 160, 130), this, 103);`, `m_3state.SetCheck(2);`, `str.Format(...)` |
| [Button1View.h](Button1View.h) | 뷰 클래스 선언. `CButton` 멤버 변수와 `OnCreate`·`OnButtonClicked` 선언 | `CButton m_pushbutton;`, `afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);` |
| [Button1.rc](Button1.rc) | 메뉴, 도구 모음, 정보 대화 상자, 문자열 리소스 | `IDR_MAINFRAME` |
| [Button1.cpp](Button1.cpp), [Button1.h](Button1.h), [Button1Doc.cpp](Button1Doc.cpp), [Button1Doc.h](Button1Doc.h), [MainFrm.cpp](MainFrm.cpp), [MainFrm.h](MainFrm.h) | MFC 마법사 생성 클래스. 애플리케이션 클래스의 SDI 문서 템플릿 등록, 문서 클래스, 메뉴 모음·도구 모음·상태 표시줄을 만드는 메인 프레임 | `new CSingleDocTemplate(...)` |
| [Resource.h](Resource.h), [framework.h](framework.h), [pch.h](pch.h), [pch.cpp](pch.cpp), [targetver.h](targetver.h), [Button1.slnx](Button1.slnx), [Button1.vcxproj](Button1.vcxproj), [Button1.vcxproj.filters](Button1.vcxproj.filters) | Visual Studio 프로젝트 생성 파일 | - |

`res/`: 아이콘, 도구 모음 비트맵, `Button1.rc2` 리소스.

## Button과 비교

| 구분 | [Button](../Button/README.md) | Button1 |
|---|---|---|
| 뷰 클래스 | `CFormView` | `CView` |
| 컨트롤 생성 | `.rc` 폼 템플릿에 배치 | `OnCreate`에서 `CButton::Create` 호출 |
| 컨트롤 ID | `resource.h`의 `IDC_CHECK2` 같은 상수 | 코드에 적은 숫자 `101`~`106` |
| 초기 상태 | 지정 없음 | `SetCheck`로 지정 |
| 클릭 처리 | 체크 박스 처리 함수 빈 틀 | 푸시 버튼 클릭 시 버튼 상태 메시지 상자 |
