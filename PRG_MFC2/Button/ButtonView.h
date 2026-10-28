
// ButtonView.h: CButtonView 클래스의 인터페이스
//

#pragma once


class CButtonView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CButtonView() noexcept;
	DECLARE_DYNCREATE(CButtonView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_BUTTON_FORM };
#endif

// 특성입니다.
public:
	CButtonDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CButtonView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
};

#ifndef _DEBUG  // ButtonView.cpp의 디버그 버전
inline CButtonDoc* CButtonView::GetDocument() const
   { return reinterpret_cast<CButtonDoc*>(m_pDocument); }
#endif

