# Button · 폼 뷰 버튼 컨트롤

SDI 마법사 프로젝트의 폼 뷰에 리소스 편집기로 푸시 버튼·체크 박스·그룹 상자·라디오 버튼을 배치한 화면.

## 다룬 개념

| 개념 | 뜻과 사용 방법 |
|---|---|
| 컨트롤 | 버튼·편집 상자처럼 사용자 입력을 받는 작은 자식 창. 클릭되면 부모 창에 알림 메시지 전송 |
| 버튼 종류 | 같은 `Button` 창 클래스에 스타일만 달리한 컨트롤. `PUSHBUTTON` 푸시 버튼, `BS_AUTOCHECKBOX` 체크 박스, `GROUPBOX` 그룹 상자, `BS_AUTORADIOBUTTON` 라디오 버튼 |
| 자동 스타일 | 클릭하면 운영체제가 선택 상태를 알아서 바꾸는 버튼 스타일. 체크 박스는 켜짐·꺼짐 전환, 라디오 버튼은 같은 묶음에서 하나만 선택 |
| 폼 뷰 `CFormView` | 대화 상자 템플릿을 뷰 화면으로 쓰는 뷰 클래스. `IDD_BUTTON_FORM` 템플릿에 그려 둔 컨트롤이 실행 시 그 배치대로 표시 |
| 리소스 편집기 배치 | 컨트롤 종류·캡션·위치를 `.rc` 파일의 대화 상자 템플릿에 적어 두는 방식. 코드 없이 화면 구성 |
| `ON_BN_CLICKED` | 버튼 클릭 알림 `BN_CLICKED`를 처리 함수에 연결하는 메시지 맵 매크로. `IDC_CHECK2`, `IDC_CHECK3`에 처리 함수 연결 |
| SDI | 한 번에 문서 하나만 여는 문서·뷰 구조. `CSingleDocTemplate`으로 문서·메인 프레임·뷰 연결 |

## 동작 흐름

| 사용자 동작 | 메시지 맵 항목 | 처리 함수 | 결과 |
|---|---|---|---|
| 프로그램 실행 | - | `CButtonView::OnInitialUpdate` | 폼 크기에 맞춰 프레임 크기 조정 |
| Button2 푸시 버튼, Check1, Radio1~Radio5 클릭 | 연결 없음 | - | 체크 박스·라디오 버튼은 자동 스타일로 상태만 전환, 푸시 버튼은 처리 함수 없음 |
| Check2·Check3 클릭 | `ON_BN_CLICKED(IDC_CHECK2, ...)`, `ON_BN_CLICKED(IDC_CHECK3, ...)` | `OnBnClickedCheck2`, `OnBnClickedCheck3` | 체크 상태 전환, 처리 함수 본문은 빈 틀 |
| 뷰에서 마우스 오른쪽 버튼 놓기 | `ON_WM_RBUTTONUP()` | `OnRButtonUp`, `OnContextMenu` | 편집 팝업 메뉴 `IDR_POPUP_EDIT` 표시 |

## 파일별 내용

| 파일 | 내용 | 핵심 코드 |
|---|---|---|
| [ButtonView.cpp](ButtonView.cpp), [ButtonView.h](ButtonView.h) | 폼 뷰 클래스 `CButtonView`. 체크 박스 클릭 처리 함수 연결, 폼 크기 맞춤, 오른쪽 클릭 팝업 메뉴 | `CFormView(IDD_BUTTON_FORM)`, `ON_BN_CLICKED(IDC_CHECK2, &CButtonView::OnBnClickedCheck2)`, `ResizeParentToFit()` |
| [Button.rc](Button.rc) | 폼 템플릿 `IDD_BUTTON_FORM`에 푸시 버튼 하나, 체크 박스 Check1~Check3, 그룹 상자, 라디오 버튼 Radio1~Radio5 배치. 메뉴·도구 모음·문자열 리소스 | `PUSHBUTTON "Button2",IDC_BUTTON1`, `BS_AUTOCHECKBOX`, `GROUPBOX`, `BS_AUTORADIOBUTTON` |
| [Button.cpp](Button.cpp), [Button.h](Button.h), [ButtonDoc.cpp](ButtonDoc.cpp), [ButtonDoc.h](ButtonDoc.h), [MainFrm.cpp](MainFrm.cpp), [MainFrm.h](MainFrm.h) | MFC 마법사 생성 클래스. 애플리케이션 클래스의 SDI 문서 템플릿 등록, 문서 클래스, 메뉴 모음·도구 모음·상태 표시줄을 만드는 메인 프레임 | `new CSingleDocTemplate(...)`, `class CMainFrame : public CFrameWndEx` |
| [resource.h](resource.h), [framework.h](framework.h), [pch.h](pch.h), [pch.cpp](pch.cpp), [targetver.h](targetver.h), [Button.slnx](Button.slnx), [Button.vcxproj](Button.vcxproj), [Button.vcxproj.filters](Button.vcxproj.filters) | Visual Studio 프로젝트 생성 파일. `resource.h`에 `IDC_CHECK1`~`IDC_CHECK3`, `IDC_RADIO1`~`IDC_RADIO5` 같은 컨트롤 ID 정의 | - |

`res/`: 아이콘, 도구 모음 비트맵, `Button.rc2` 리소스.

같은 버튼을 코드로 만드는 방식은 [Button1](../Button1/README.md).
