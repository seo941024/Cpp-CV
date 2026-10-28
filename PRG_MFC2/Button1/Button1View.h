// Button1View.h: CButton1View 클래스의 인터페이스
#pragma once

class CButton1Doc; // Forward 선언

class CButton1View : public CView
{
protected: // serialization에서만 만들어집니다.
	CButton1View() noexcept;
	DECLARE_DYNCREATE(CButton1View)

	// 특성입니다.
public:
	CButton1Doc* GetDocument() const;

	// 컨트롤 멤버 변수들을 한곳으로 모았습니다.
	CButton m_pushbutton;
	CButton m_checkbox;
	CButton m_3state;
	CButton m_radio1;
	CButton m_radio2;
	CButton m_groupbox;

	// 작업입니다.
public:

	// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// 구현입니다.
public:
	virtual ~CButton1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct); // OnCreate 선언
	DECLARE_MESSAGE_MAP()

public:
	void OnButtonClicked();
};

#ifndef _DEBUG  // Button1View.cpp의 디버그 버전
inline CButton1Doc* CButton1View::GetDocument() const
{
	return reinterpret_cast<CButton1Doc*>(m_pDocument);
}
#endif