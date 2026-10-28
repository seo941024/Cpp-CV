
// WebCamviewerDlg.h: 헤더 파일
//
#pragma once
#include <opencv2/opencv.hpp>
#include <thread>
#include <mutex>
#include <atomic>



// CWebCamviewerDlg 대화 상자
class CWebCamviewerDlg : public CDialogEx
{
// 생성입니다.
public:
	CWebCamviewerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WEBCAMVIEWER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	cv::VideoCapture m_cap;     // 웹캠 캡처 객체
	cv::Mat          m_frame;   // 현재 프레임
	UINT_PTR         m_timer;   // 프레임 갱신 타이머 ID

	cv::dnn::Net         m_net;        // YOLO DNN 네트워크
	std::vector<std::string> m_classes; // COCO 클래스 이름
	bool                 m_netLoaded;  // 모델 로드 여부
	int                  m_frameCount; // 프레임 카운터
	int64                m_tickLast;   // FPS 계산용 틱
	double               m_fps;        // 현재 FPS
	int                  m_fpsCount;   // 1초 안에 처리한 프레임 수

	// 마지막 검출 결과 저장
	std::vector<cv::Rect>        m_lastBoxes;
	std::vector<int>             m_lastClassIds;
	std::vector<float>           m_lastConfs;
	std::mutex                   m_resultMutex;  // 결과 보호

	// 백그라운드 추론 스레드
	std::thread                  m_detectThread;
	std::atomic<bool>            m_threadRun;
	cv::Mat                      m_detectInput;  // 추론용 입력 프레임
	std::mutex                   m_inputMutex;
	std::atomic<bool>            m_newFrame;     // 새 프레임 있음

	void DisplayFrame(const cv::Mat& img);
	void Detect(const cv::Mat& img);   // YOLO 검출만 (결과 저장)
	void DrawBoxes(cv::Mat& img);      // 저장된 결과 그리기
	void LoadModel();                  // 모델/클래스 로드
	void DetectThreadFunc();           // 백그라운드 추론 스레드 함수

public:
	afx_msg void OnBnClickedBtnAtart();
	afx_msg void OnBnClickedBtnEnd();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();


	DECLARE_MESSAGE_MAP()

};
