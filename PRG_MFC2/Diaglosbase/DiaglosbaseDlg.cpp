
// DiaglosbaseDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Diaglosbase.h"
#include "DiaglosbaseDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDiaglosbaseDlg 대화 상자



CDiaglosbaseDlg::CDiaglosbaseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIAGLOSBASE_DIALOG, pParent)
	, m_num1(1)
	, m_num2(45)
	, m_num3(6)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDiaglosbaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_num1);
	DDX_Text(pDX, IDC_EDIT2, m_num2);
	DDX_Text(pDX, IDC_EDIT3, m_num3);
}

BEGIN_MESSAGE_MAP(CDiaglosbaseDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CDiaglosbaseDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDiaglosbaseDlg 메시지 처리기

BOOL CDiaglosbaseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	ShowWindow(SW_MINIMIZE);

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CDiaglosbaseDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CDiaglosbaseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDiaglosbaseDlg::OnBnClickedButton2()
{
	CColorDialog dlg;
	dlg.DoModal();
	COLORREF color = dlg.GetColor();

	// 1. COLORREF에서 R, G, B 값 각각 추출
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);

	// 2. 출력할 문자열 포맷팅
	CString strOutput;
	strOutput.Format(_T("선택한 색상 - RGB: (%d, %d, %d), HEX: #%02X%02X%02X\n"), r, g, b, r, g, b);

	AfxMessageBox(strOutput);

}
