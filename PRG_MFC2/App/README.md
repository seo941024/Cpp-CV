# App · MDI 마법사 프로젝트

MFC 애플리케이션 마법사로 생성한 MDI 형식 프로젝트. 문서·뷰 구조, 메뉴 모음·도구 모음·상태 표시줄, 클래스 뷰·파일 뷰·출력·속성 도킹 창 구성.

모든 소스가 마법사 생성 코드 그대로인 프로젝트로, 문서 저장과 화면 그리기 함수는 빈 틀 상태.

## 다룬 개념

| 개념 | 뜻과 사용 방법 |
|---|---|
| MFC 애플리케이션 마법사 | Visual Studio가 고른 형식에 맞춰 MFC 프로젝트 뼈대를 만들어 주는 도구. 이 프로젝트는 MDI 형식, 도킹 창 포함 구성 |
| 문서·뷰 구조 | 데이터를 담는 문서 클래스와 화면에 보여 주는 뷰 클래스를 나누는 MFC 구조. `CAppDoc::Serialize`가 저장·불러오기, `CAppView::OnDraw`가 그리기 담당 |
| MDI | 메인 창 하나 안에 여러 문서 창을 동시에 여는 방식. `CMultiDocTemplate`이 문서·자식 프레임·뷰 클래스를 묶고, 메인 창은 `CMDIFrameWndEx`, 문서 창은 `CMDIChildWndEx` |
| 문서 템플릿 | 문서·프레임·뷰 클래스 조합을 등록해 두는 객체. `InitInstance`에서 `AddDocTemplate`으로 등록하면 새로 만들기 때마다 세 객체를 함께 생성 |
| 도킹 창 | 메인 창 가장자리에 붙이거나 떼어 띄울 수 있는 창. `CDockablePane`을 상속한 클래스 뷰·파일 뷰·출력·속성 창을 `EnableDocking`과 `DockPane`으로 배치 |
| 메뉴 모음·도구 모음·상태 표시줄 | 메인 창 위아래의 막대. `CMFCMenuBar`, `CMFCToolBar`, `CMFCStatusBar`를 `CMainFrame::OnCreate`에서 생성 |
| 명령 범위 연결 | 연속된 메뉴 ID 여러 개를 처리 함수 하나에 연결하는 메시지 맵 항목. `ON_COMMAND_RANGE`로 애플리케이션 모양 메뉴 전체를 `OnApplicationLook`에 연결 |

## 동작 흐름

| 사용자 동작 | 처리 함수 | 결과 |
|---|---|---|
| 프로그램 실행 | `CAppApp::InitInstance` | 문서 템플릿 등록, 메인 프레임 생성, 명령줄에 따라 새 문서 창 열기 |
| 파일 메뉴의 새로 만들기 | `CWinAppEx::OnFileNew` | 문서·자식 프레임·뷰 묶음 하나 추가 |
| 보기 메뉴의 애플리케이션 모양 선택 | `CMainFrame::OnApplicationLook` | Windows·Office·Visual Studio 테마로 화면 모양 변경 |
| 뷰에서 마우스 오른쪽 버튼 놓기 | `CAppView::OnRButtonUp`, `OnContextMenu` | 편집 팝업 메뉴 `IDR_POPUP_EDIT` 표시 |
| 도움말 메뉴의 App 정보 | `CAppApp::OnAppAbout` | 정보 대화 상자 표시 |

## 파일별 내용

| 파일 | 내용 | 핵심 코드 |
|---|---|---|
| [App.cpp](App.cpp), [App.h](App.h) | 애플리케이션 클래스 `CAppApp`. OLE 초기화, 문서 템플릿 등록, 파일 형식 등록, 정보 대화 상자 | `new CMultiDocTemplate(IDR_AppTYPE, ...)`, `RegisterShellFileTypes(TRUE)` |
| [AppDoc.cpp](AppDoc.cpp), [AppDoc.h](AppDoc.h) | 문서 클래스 `CAppDoc`. 저장·불러오기 함수 틀 | `void CAppDoc::Serialize(CArchive& ar)` |
| [AppView.cpp](AppView.cpp), [AppView.h](AppView.h) | 뷰 클래스 `CAppView`. 그리기·인쇄·팝업 메뉴 처리 | `OnDraw`, `AFXPrintPreview(this)`, `ShowPopupMenu(IDR_POPUP_EDIT, ...)` |
| [MainFrm.cpp](MainFrm.cpp), [MainFrm.h](MainFrm.h) | MDI 메인 프레임 `CMainFrame`. 메뉴·도구 모음·상태 표시줄과 도킹 창 생성, 테마 변경 | `CreateDockingWindows()`, `DockPane(&m_wndOutput)`, `ON_COMMAND_RANGE` |
| [ChildFrm.cpp](ChildFrm.cpp), [ChildFrm.h](ChildFrm.h) | 문서 하나를 담는 MDI 자식 프레임 `CChildFrame` | `class CChildFrame : public CMDIChildWndEx` |
| [ClassView.cpp](ClassView.cpp), [ClassView.h](ClassView.h) | 클래스 뷰 도킹 창. 예시 클래스 트리와 정렬 도구 모음 | `FillClassView()`, `InsertItem(_T("FakeApp 클래스"), 0, 0)` |
| [FileView.cpp](FileView.cpp), [FileView.h](FileView.h) | 파일 뷰 도킹 창. 예시 소스·헤더·리소스 파일 트리 | `FillFileView()` |
| [OutputWnd.cpp](OutputWnd.cpp), [OutputWnd.h](OutputWnd.h) | 출력 도킹 창. 빌드·디버그·찾기 탭과 목록 상자 | `m_wndTabs.AddTab`, `FillBuildWindow()` |
| [PropertiesWnd.cpp](PropertiesWnd.cpp), [PropertiesWnd.h](PropertiesWnd.h) | 속성 도킹 창. 모양·창 크기·글꼴 예시 속성 그리드 | `InitPropList()`, `CMFCPropertyGridProperty` |
| [ViewTree.cpp](ViewTree.cpp), [ViewTree.h](ViewTree.h) | 클래스 뷰·파일 뷰가 쓰는 트리 컨트롤 파생 클래스 | `class CViewTree : public CTreeCtrl` |
| [App.rc](App.rc) | 메뉴, 도구 모음, 정보 대화 상자, 도킹 창 이름·탭 이름 문자열 리소스 | `POPUP "애플리케이션 모양(&A)"`, `IDS_OUTPUT_WND "출력"` |
| [App.reg](App.reg) | 문서 확장자와 실행 명령을 등록하는 레지스트리 스크립트 | `HKEY_CLASSES_ROOT\.App = App.Document` |
| [Resource.h](Resource.h), [framework.h](framework.h), [pch.h](pch.h), [pch.cpp](pch.cpp), [targetver.h](targetver.h), [App.slnx](App.slnx), [App.vcxproj](App.vcxproj), [App.vcxproj.filters](App.vcxproj.filters) | Visual Studio 프로젝트 생성 파일. 리소스 ID, MFC 헤더 포함, 미리 컴파일된 헤더, MFC 동적 연결 설정 | - |

`res/`: 아이콘, 도구 모음·도킹 창 비트맵, `App.rc2` 리소스.
