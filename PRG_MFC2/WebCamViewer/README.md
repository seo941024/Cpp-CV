# WebCamViewer · MFC 웹캠 뷰어와 YOLO 검출

대화 상자 기반 MFC 프로그램에서 OpenCV로 웹캠 영상을 받아 Picture Control에 표시하고, 별도 스레드의 YOLO ONNX 추론으로 찾은 물체 상자와 FPS를 영상 위에 그리는 뷰어.

## 다룬 개념

| 개념 | 뜻과 사용 방법 |
|---|---|
| `cv::VideoCapture` | 카메라나 영상 파일에서 프레임을 읽는 OpenCV 클래스. `open(0, cv::CAP_DSHOW)`로 기본 웹캠을 DirectShow 방식으로 열고 해상도 640×480 요청 |
| `SetTimer`와 `WM_TIMER` | 정한 간격마다 타이머 메시지를 보내게 하는 함수와 그 메시지. 33ms 간격으로 호출되는 `OnTimer`에서 프레임 한 장을 읽어 표시 |
| Picture Control 출력 | 대화 상자의 정적 컨트롤 `IDC_VIDIO` 영역에 영상을 그리는 방법. `cv::Mat`의 BGR 데이터를 `BITMAPINFO`로 감싸 `StretchDIBits`로 컨트롤 크기에 맞춰 확대·축소 |
| DIB 행 정렬 | 장치 독립 비트맵의 한 행 바이트 수는 4의 배수여야 하는 규칙. 맞지 않으면 `copyMakeBorder`로 오른쪽을 채우고, `biHeight`를 음수로 둬 위아래 뒤집힘 방지 |
| OpenCV DNN | OpenCV에 들어 있는 신경망 추론 모듈. `readNetFromONNX`로 `yolo11l.onnx`를 읽고, `blobFromImage`로 320×320 입력을 만든 뒤 CPU 백엔드에서 `forward` 실행 |
| YOLO 출력 해석 | 후보 상자마다 중심 좌표·폭·높이와 클래스별 점수가 한 줄로 나오는 출력. `transpose`로 상자별 행으로 바꾸고 최고 점수 0.4 이상만 남긴 뒤 원본 크기 비율로 좌표 환산 |
| NMS | 같은 물체에 겹친 상자 중 점수가 가장 높은 것만 남기는 후처리. `cv::dnn::NMSBoxes`에 겹침 임곗값 0.45 지정 |
| 작업 스레드 `std::thread` | 메인 흐름과 동시에 실행되는 별도 실행 흐름. 추론 함수를 따로 돌려 느린 추론이 화면 갱신을 막지 않는 구성 |
| `std::mutex`와 `std::lock_guard` | 두 스레드가 같은 데이터를 동시에 건드리지 못하게 막는 잠금과, 블록이 끝나면 자동으로 잠금을 푸는 객체. 추론 입력 프레임용 `m_inputMutex`, 검출 결과용 `m_resultMutex`를 따로 사용 |
| `std::atomic<bool>` | 잠금 없이도 스레드 사이에서 안전하게 읽고 쓰는 불 변수. 스레드 실행 여부 `m_threadRun`, 새 프레임 도착 여부 `m_newFrame` |
| FPS 계산 | 초당 처리 프레임 수. `cv::getTickCount`로 시간을 재고 0.5초 이상 지날 때마다 그동안 처리한 프레임 수를 경과 시간으로 나눠 갱신 |

## 스레드 구조

| 스레드 | 담당 함수 | 하는 일 | 공유 데이터 |
|---|---|---|---|
| UI 스레드 | `OnTimer`, `DrawBoxes`, `DisplayFrame` | 33ms마다 웹캠 프레임 읽기, FPS 계산, 프레임 복사본을 추론 입력으로 전달, 마지막 검출 결과와 FPS를 그려 화면 출력 | `m_detectInput` 쓰기, `m_lastBoxes`·`m_lastClassIds`·`m_lastConfs` 읽기 |
| 추론 스레드 | `DetectThreadFunc`, `Detect` | 새 프레임이 있으면 복사해 YOLO 추론과 NMS 실행 후 검출 결과 교체, 없으면 5ms 대기 | `m_detectInput` 읽기, `m_lastBoxes`·`m_lastClassIds`·`m_lastConfs` 쓰기 |

1. 시작 버튼을 누르면 `m_threadRun = true` 후 `std::thread(&CWebCamviewerDlg::DetectThreadFunc, this)`로 추론 스레드 시작, 이어서 `SetTimer(TIMER_ID, 33, nullptr)`.
2. UI 스레드는 타이머마다 `m_inputMutex` 잠금 안에서 `m_detectInput = m_frame.clone()`, `m_newFrame = true`로 최신 프레임만 넘김. 추론이 끝나지 않았으면 이전 입력을 덮어써 중간 프레임은 추론 대상에서 빠짐.
3. 추론 스레드는 `m_inputMutex` 잠금 안에서 프레임을 복사하고 `m_newFrame = false`로 바꾼 뒤 잠금을 풀고 `Detect` 실행. 잠금은 복사하는 동안만 걸려 UI 스레드가 추론 시간 동안 기다리지 않음.
4. `Detect`는 결과를 지역 벡터에 모은 뒤 `m_resultMutex` 잠금 안에서 한 번에 교체. `DrawBoxes`도 같은 잠금 안에서 읽어 반쯤 바뀐 결과를 그리지 않음.
5. 화면은 추론 완료를 기다리지 않고 직전 검출 결과를 현재 프레임에 겹쳐 그림.
6. 종료 버튼이나 창 닫기 때 `KillTimer`, `m_threadRun = false`, `join`으로 스레드 종료를 기다린 뒤 `m_cap.release()`.

## 동작 흐름

| 사용자 동작 | 메시지 맵 항목 | 처리 함수 | 결과 |
|---|---|---|---|
| 프로그램 실행 | - | `OnInitDialog`, `LoadModel` | 실행 파일 폴더의 `coco.names`와 `yolo11l.onnx` 읽기, 파일이 없으면 메시지 상자 표시 후 검출 없이 진행 |
| 시작 버튼 클릭 | `ON_BN_CLICKED(IDC_BTN_ATART, ...)` | `OnBnClickedBtnAtart` | 웹캠 열기, 추론 스레드 시작, 타이머 시작. 웹캠을 열지 못하면 안내 메시지 상자 |
| 타이머 발생 | `ON_WM_TIMER()` | `OnTimer` | 프레임 읽기, 추론 입력 전달, 상자·FPS 그리기, 화면 출력. 모델이 없으면 영상과 FPS만 표시 |
| 종료 버튼 클릭 | `ON_BN_CLICKED(IDC_BTN_END, ...)` | `OnBnClickedBtnEnd` | 타이머 정지, 추론 스레드 종료 대기, 웹캠 해제, 화면 다시 그리기 |
| 창 닫기 | `ON_WM_DESTROY()` | `OnDestroy` | 종료 버튼과 같은 자원 정리 |
| 시스템 메뉴의 정보 항목 | `ON_WM_SYSCOMMAND()` | `OnSysCommand` | 정보 대화 상자 표시 |

## 파일별 내용

| 파일 | 내용 | 핵심 코드 |
|---|---|---|
| [WebCamViewerDlg.cpp](WebCamViewerDlg.cpp) | 웹캠 열기·닫기, 타이머 프레임 갱신, DIB 화면 출력, 모델 로드, 추론 스레드 함수, YOLO 출력 해석과 NMS, 검출 상자 그리기, 종료 시 자원 정리 | `m_cap.open(0, cv::CAP_DSHOW)`, `SetTimer(TIMER_ID, 33, nullptr)`, `::StretchDIBits`, `cv::dnn::readNetFromONNX`, `cv::dnn::NMSBoxes`, `std::lock_guard<std::mutex>` |
| [WebCamViewerDlg.h](WebCamViewerDlg.h) | 대화 상자 클래스 선언. 캡처 객체, DNN 네트워크, 클래스 이름, FPS 변수, 검출 결과 벡터, 스레드·뮤텍스·원자 변수 멤버 | `cv::VideoCapture m_cap;`, `std::thread m_detectThread;`, `std::mutex m_inputMutex;`, `std::atomic<bool> m_newFrame;` |
| [WebCamviewer.rc](WebCamviewer.rc) | 메인 대화 상자에 검은 테두리 영상 영역과 시작·종료 버튼 배치, 정보 대화 상자 | `CONTROL "",IDC_VIDIO,"Static",SS_BLACKFRAME`, `PUSHBUTTON "시작",IDC_BTN_ATART` |
| [WebCamviewer.cpp](WebCamviewer.cpp), [WebCamviewer.h](WebCamviewer.h) | MFC 마법사 생성 애플리케이션 클래스. 대화 상자를 모달로 띄우고 닫히면 종료 | `INT_PTR nResponse = dlg.DoModal();` |
| [WebCamviewer.vcxproj](WebCamviewer.vcxproj) | x64 구성에 OpenCV 포함 경로 `C:\opencv\build\include`와 `opencv_world4120` 라이브러리 연결, MFC 동적 연결 | `opencv_world4120d.lib`, `opencv_world4120.lib` |
| [resource.h](resource.h), [framework.h](framework.h), [pch.h](pch.h), [pch.cpp](pch.cpp), [targetver.h](targetver.h), [WebCamviewer.slnx](WebCamviewer.slnx), [WebCamviewer.vcxproj.filters](WebCamviewer.vcxproj.filters) | Visual Studio 프로젝트 생성 파일. `resource.h`에 `IDC_VIDIO`, `IDC_BTN_ATART`, `IDC_BTN_END` 컨트롤 ID 정의 | - |

`res/`: 아이콘과 `WebCamviewer.rc2` 리소스.

## 빌드·실행 준비

- `C:\opencv\build` 경로의 OpenCV 4.12 빌드, x64 구성.
- 실행 파일과 같은 폴더에 `yolo11l.onnx`, `coco.names` 배치. 모델 파일은 저장소에 포함하지 않음.
