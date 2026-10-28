
// WebCamviewerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "WebCamviewer.h"
#include "WebCamviewerDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define TIMER_ID  1   

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWebCamviewerDlg 대화 상자



CWebCamviewerDlg::CWebCamviewerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WEBCAMVIEWER_DIALOG, pParent)
	, m_netLoaded(false)
	, m_frameCount(0)
	, m_tickLast(0)
	, m_fps(0.0)
	, m_fpsCount(0)
	, m_threadRun(false)
	, m_newFrame(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWebCamviewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWebCamviewerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BTN_ATART, &CWebCamviewerDlg::OnBnClickedBtnAtart)
	ON_BN_CLICKED(IDC_BTN_END, &CWebCamviewerDlg::OnBnClickedBtnEnd)
	ON_WM_TIMER()
	ON_WM_DESTROY()

END_MESSAGE_MAP()


// CWebCamviewerDlg 메시지 처리기

BOOL CWebCamviewerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_timer = 0;
	LoadModel();
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CWebCamviewerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CWebCamviewerDlg::OnPaint()
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
HCURSOR CWebCamviewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CWebCamviewerDlg::OnBnClickedBtnAtart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_cap.isOpened())
		return;   // 이미 실행 중

	// 0번 장치(기본 웹캠) 열기. CAP_DSHOW는 Windows에서 안정적임
	if (!m_cap.open(0, cv::CAP_DSHOW))
	{
		AfxMessageBox(_T("웹캠을 열 수 없음. 장치 연결을 확인하기 바람."));
		return;
	}

	// 해상도 지정(선택 사항)
	m_cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
	m_cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

	// 추론 스레드 시작
	m_threadRun = true;
	m_detectThread = std::thread(&CWebCamviewerDlg::DetectThreadFunc, this);

	// 약 30fps → 33ms 간격으로 프레임 갱신
	m_timer = SetTimer(TIMER_ID, 33, nullptr);
}


void CWebCamviewerDlg::OnBnClickedBtnEnd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_timer)
	{
		KillTimer(m_timer);
		m_timer = 0;
	}
	// 추론 스레드 종료
	m_threadRun = false;
	if (m_detectThread.joinable())
		m_detectThread.join();

	if (m_cap.isOpened())
		m_cap.release();

	// 화면 잔상 지우기
	Invalidate();
	UpdateWindow();
}

void CWebCamviewerDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_ID && m_cap.isOpened())
	{
		m_cap >> m_frame;
		if (!m_frame.empty())
		{
			// FPS 계산 (1초 동안 실제 처리한 프레임 수)
			int64 now = cv::getTickCount();
			m_fpsCount++;
			if (m_tickLast == 0) m_tickLast = now;
			double elapsed = (now - m_tickLast) / cv::getTickFrequency();
			if (elapsed >= 0.5)
			{
				m_fps = m_fpsCount / elapsed;
				m_fpsCount = 0;
				m_tickLast = now;
			}

			// 추론 스레드에 프레임 전달
			if (m_netLoaded)
			{
				{
					std::lock_guard<std::mutex> lk(m_inputMutex);
					m_detectInput = m_frame.clone();
					m_newFrame = true;
				}
				DrawBoxes(m_frame);
			}

			// FPS 좌측 상단 표시
			char fpsStr[32];
			sprintf_s(fpsStr, "FPS: %.1f", m_fps);
			{
				int bl = 0;
				cv::Size ts = cv::getTextSize(fpsStr, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, &bl);
				cv::rectangle(m_frame, cv::Point(6, 6), cv::Point(14 + ts.width, 14 + ts.height), cv::Scalar(0, 0, 0), cv::FILLED);
				cv::putText(m_frame, fpsStr, cv::Point(10, 10 + ts.height),
					cv::FONT_HERSHEY_SIMPLEX, 1.2, cv::Scalar(0, 255, 0), 2);
			}

			DisplayFrame(m_frame);
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


// ★ cv::Mat → Picture Control 영역에 그리기
//   OpenCV의 BGR 순서는 Windows DIB와 동일하므로 색 변환 없이 그대로 사용 가능
void  CWebCamviewerDlg::DisplayFrame(const cv::Mat& img)
{
	CWnd* pWnd = GetDlgItem(IDC_VIDIO);
	if (!pWnd || img.empty())
		return;

	CDC* pDC = pWnd->GetDC();
	CRect rc;
	pWnd->GetClientRect(&rc);

	// 8비트 3채널이 아니면 변환
	cv::Mat show;
	if (img.channels() == 3)
		show = img;
	else
		cv::cvtColor(img, show, cv::COLOR_GRAY2BGR);

	// DIB 한 행은 4바이트 정렬 필요 → 폭을 4의 배수로 맞춤
	cv::Mat aligned;
	if (show.cols % 4 != 0)
	{
		int pad = 4 - (show.cols * 3) % 4;
		if (pad == 4) pad = 0;
		cv::copyMakeBorder(show, aligned, 0, 0, 0,
			(pad == 0 ? 0 : (pad + 2) / 3),
			cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
		show = aligned;
	}

	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = show.cols;
	bmi.bmiHeader.biHeight = -show.rows;   // 음수 = top-down(상하 반전 방지)
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biCompression = BI_RGB;

	SetStretchBltMode(pDC->GetSafeHdc(), COLORONCOLOR);

	// Picture Control 크기에 맞춰 확대/축소 출력
	::StretchDIBits(pDC->GetSafeHdc(),
		0, 0, rc.Width(), rc.Height(),     // 대상 영역
		0, 0, show.cols, show.rows,        // 원본 영역
		show.data, &bmi, DIB_RGB_COLORS, SRCCOPY);

	pWnd->ReleaseDC(pDC);
}


void CWebCamviewerDlg::LoadModel()
{
	// exe와 같은 폴더에 yolov8m.onnx, coco.names 있어야 함
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(nullptr, szPath, MAX_PATH);
	CString exeDir(szPath);
	exeDir = exeDir.Left(exeDir.ReverseFind('\\') + 1);

	std::string modelPath = CT2A(exeDir + _T("yolo11l.onnx"));
	std::string namesPath = CT2A(exeDir + _T("coco.names"));

	// coco.names 로드
	std::ifstream ifs(namesPath);
	if (!ifs.is_open()) { AfxMessageBox(_T("coco.names 없음")); return; }
	std::string line;
	while (std::getline(ifs, line))
		if (!line.empty()) m_classes.push_back(line);

	// ONNX 모델 로드
	m_net = cv::dnn::readNetFromONNX(modelPath);
	if (m_net.empty()) { AfxMessageBox(_T("yolov8m.onnx 없음")); return; }
	m_net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
	m_net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
	m_netLoaded = true;
}

void CWebCamviewerDlg::DetectThreadFunc()
{
	while (m_threadRun)
	{
		cv::Mat frame;
		{
			std::lock_guard<std::mutex> lk(m_inputMutex);
			if (m_newFrame)
			{
				frame = m_detectInput.clone();
				m_newFrame = false;
			}
		}
		if (frame.empty()) { std::this_thread::sleep_for(std::chrono::milliseconds(5)); continue; }
		Detect(frame);
	}
}

void CWebCamviewerDlg::Detect(const cv::Mat& img)
{
	const float CONF_THRESH = 0.4f;
	const int   INPUT_SZ    = 320;

	int origW = img.cols, origH = img.rows;

	cv::Mat blob;
	cv::dnn::blobFromImage(img, blob, 1.0 / 255.0,
		cv::Size(INPUT_SZ, INPUT_SZ), cv::Scalar(), true, false);
	m_net.setInput(blob);

	std::vector<cv::Mat> outs;
	m_net.forward(outs, m_net.getUnconnectedOutLayersNames());

	// yolo11/v8 출력: [1, 84, 8400] → transpose → [8400, 84]
	cv::Mat output = outs[0];
	output = output.reshape(1, output.size[1]);
	cv::transpose(output, output);

	float xScale = (float)origW / INPUT_SZ;
	float yScale = (float)origH / INPUT_SZ;

	std::vector<cv::Rect> boxes;
	std::vector<float>    confidences;
	std::vector<int>      classIds;

	for (int i = 0; i < output.rows; i++)
	{
		float* row = output.ptr<float>(i);
		cv::Mat scores(1, (int)m_classes.size(), CV_32F, row + 4);
		cv::Point classId;
		double conf;
		cv::minMaxLoc(scores, nullptr, &conf, nullptr, &classId);
		if (conf < CONF_THRESH) continue;

		float cx = row[0] * xScale;
		float cy = row[1] * yScale;
		float  w = row[2] * xScale;
		float  h = row[3] * yScale;

		boxes.push_back(cv::Rect((int)(cx - w/2), (int)(cy - h/2), (int)w, (int)h));
		confidences.push_back((float)conf);
		classIds.push_back(classId.x);
	}

	std::vector<int> indices;
	cv::dnn::NMSBoxes(boxes, confidences, CONF_THRESH, 0.45f, indices);

	std::lock_guard<std::mutex> lk(m_resultMutex);
	m_lastBoxes.clear();
	m_lastClassIds.clear();
	m_lastConfs.clear();
	for (int idx : indices)
	{
		m_lastBoxes.push_back(boxes[idx]);
		m_lastClassIds.push_back(classIds[idx]);
		m_lastConfs.push_back(confidences[idx]);
	}
}

void CWebCamviewerDlg::DrawBoxes(cv::Mat& img)
{
	std::lock_guard<std::mutex> lk(m_resultMutex);
	for (int i = 0; i < (int)m_lastBoxes.size(); i++)
	{
		cv::Rect box = m_lastBoxes[i];
		std::string label = (m_lastClassIds[i] < (int)m_classes.size())
			? m_classes[m_lastClassIds[i]] : "?";
		label += " " + std::to_string((int)(m_lastConfs[i] * 100)) + "%";

		cv::rectangle(img, box, cv::Scalar(0, 255, 0), 2);
		int baseLine = 0;
		cv::Size ts = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.7, 2, &baseLine);
		cv::rectangle(img,
			cv::Point(box.x, box.y - ts.height - 8),
			cv::Point(box.x + ts.width + 4, box.y),
			cv::Scalar(0, 0, 0), cv::FILLED);
		cv::putText(img, label, cv::Point(box.x + 2, box.y - 4),
			cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 255, 0), 2);
	}
}

// ★ 창 닫힐 때 자원 정리
void  CWebCamviewerDlg::OnDestroy()
{
	if (m_timer)
	{
		KillTimer(m_timer);
		m_timer = 0;
	}
	m_threadRun = false;
	if (m_detectThread.joinable())
		m_detectThread.join();
	if (m_cap.isOpened())
		m_cap.release();

	CDialogEx::OnDestroy();
}

