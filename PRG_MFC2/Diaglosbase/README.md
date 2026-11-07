# Diaglosbase · 대화 상자

대화 상자 기반 MFC 프로젝트에서 편집 상자와 정수 멤버 변수를 DDX로 연결하고, 버튼 클릭 시 색 대화 상자에서 고른 색의 RGB·HEX 값을 메시지 상자로 출력하는 프로그램.

## 다룬 개념

| 개념 | 뜻과 사용 방법 |
|---|---|
| 대화 상자 기반 애플리케이션 | 메인 창 자체가 대화 상자인 MFC 프로그램 형식. 컨트롤 배치는 `.rc` 대화 상자 템플릿, 동작은 `CDialogEx` 파생 클래스가 담당 |
| 모달 대화 상자 `DoModal` | 대화 상자가 닫힐 때까지 다른 창 조작을 막고 기다리는 방식. `InitInstance`에서 `dlg.DoModal()` 호출, 닫히면 `FALSE`를 반환해 프로그램 종료 |
| `OnInitDialog` | 대화 상자가 화면에 나타나기 직전에 호출되는 초기화 함수. 아이콘 설정과 `ShowWindow(SW_MINIMIZE)` 호출 |
| DDX | 대화 상자 데이터 교환. `DoDataExchange` 안의 `DDX_Text`로 편집 상자와 멤버 변수를 연결해 `UpdateData` 때 값을 주고받는 구조. 대화 상자가 열릴 때 생성자 초기값 `1`, `45`, `6`이 숫자1~숫자3 편집 상자에 표시 |
| 공용 대화 상자 `CColorDialog` | 윈도우가 제공하는 표준 색 선택 창. `DoModal`로 띄우고 `GetColor`로 고른 색 조회 |
| `COLORREF`와 `GetRValue` | `COLORREF`는 빨강·초록·파랑 값을 하나로 묶은 색 자료형, `GetRValue`·`GetGValue`·`GetBValue`는 각 성분을 꺼내는 매크로. `CString::Format`의 `%02X`로 두 자리 16진 표기 |

## 동작 흐름

| 사용자 동작 | 메시지 맵 항목 | 처리 함수 | 결과 |
|---|---|---|---|
| 프로그램 실행 | - | `CDiaglosbaseApp::InitInstance`, `CDiaglosbaseDlg::OnInitDialog` | 대화 상자를 최소화 상태로 표시, 편집 상자에 `1`, `45`, `6` 표시 |
| 컬러 색상표 대화상자 버튼 클릭 | `ON_BN_CLICKED(IDC_BUTTON2, &CDiaglosbaseDlg::OnBnClickedButton2)` | `OnBnClickedButton2` | 색 대화 상자 표시, 고른 색을 `선택한 색상 - RGB: (%d, %d, %d), HEX: #%02X%02X%02X` 형식 메시지 상자로 출력 |
| 시작 버튼, 목록 상자 | 연결 없음 | - | 템플릿에 배치한 컨트롤, 처리 함수 연결 없음 |

## 파일별 내용

| 파일 | 내용 | 핵심 코드 |
|---|---|---|
| [DiaglosbaseDlg.cpp](DiaglosbaseDlg.cpp) | 대화 상자 클래스 구현. 정수 멤버 초기값, 편집 상자 DDX 연결, 색 대화 상자 버튼 처리 | `DDX_Text(pDX, IDC_EDIT1, m_num1);`, `CColorDialog dlg;`, `GetRValue(color)`, `AfxMessageBox(strOutput);` |
| [DiaglosbaseDlg.h](DiaglosbaseDlg.h) | 대화 상자 클래스 선언. 정수 멤버 변수와 버튼 처리 함수 선언 | `int m_num1;`, `afx_msg void OnBnClickedButton2();` |
| [Diaglosbase.rc](Diaglosbase.rc) | 대화 상자 템플릿에 숫자1~숫자3 레이블과 편집 상자, 목록 상자, 시작 버튼, 컬러 색상표 대화상자 버튼 배치 | `EDITTEXT IDC_EDIT1`, `LISTBOX IDC_LIST2`, `PUSHBUTTON "컬러 색상표 대화상자",IDC_BUTTON2` |
| [Diaglosbase.cpp](Diaglosbase.cpp), [Diaglosbase.h](Diaglosbase.h) | MFC 마법사 생성 애플리케이션 클래스. 대화 상자를 모달로 띄우고 닫히면 종료 | `INT_PTR nResponse = dlg.DoModal();` |
| [resource.h](resource.h), [framework.h](framework.h), [pch.h](pch.h), [pch.cpp](pch.cpp), [targetver.h](targetver.h), [Diaglosbase.slnx](Diaglosbase.slnx), [Diaglosbase.vcxproj](Diaglosbase.vcxproj), [Diaglosbase.vcxproj.filters](Diaglosbase.vcxproj.filters) | Visual Studio 프로젝트 생성 파일. `resource.h`에 `IDC_EDIT1`~`IDC_EDIT3`, `IDC_LIST2`, `IDC_START`, `IDC_BUTTON2` 컨트롤 ID 정의 | - |

`res/`: 아이콘과 `Diaglosbase.rc2` 리소스.
