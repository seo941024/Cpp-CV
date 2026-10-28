
// ButtonView.cpp: CButtonView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Button.h"
#endif

#include "ButtonDoc.h"
#include "ButtonView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CButtonView

IMPLEMENT_DYNCREATE(CButtonView, CFormView)

BEGIN_MESSAGE_MAP(CButtonView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_CHECK2, &CButtonView::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CButtonView::OnBnClickedCheck3)
END_MESSAGE_MAP()

// CButtonView 생성/소멸

CButtonView::CButtonView() noexcept
	: CFormView(IDD_BUTTON_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CButtonView::~CButtonView()
{
}

void CButtonView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CButtonView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CButtonView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

void CButtonView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CButtonView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CButtonView 진단

#ifdef _DEBUG
void CButtonView::AssertValid() const
{
	CFormView::AssertValid();
}

void CButtonView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CButtonDoc* CButtonView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CButtonDoc)));
	return (CButtonDoc*)m_pDocument;
}
#endif //_DEBUG


// CButtonView 메시지 처리기

void CButtonView::OnBnClickedCheck2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CButtonView::OnBnClickedCheck3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
