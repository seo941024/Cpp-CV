# ch9 · 검출과 분할

영상 속 물체의 위치와 부류를 찾는 검출과 화소마다 부류를 정하는 분할. YOLO v3 물체 검출, U-net 분할 학습, DeepLabv3 의미 분할, Mask R-CNN 사례 분할, 사람 뒤 배경 흐림·색 변경 구현.

소스와 영상은 하위 폴더 [ch9/](ch9)에 위치.

## 다룬 개념

| 개념 | 뜻과 사용 방법 |
|---|---|
| 물체 검출 | 영상에서 물체를 감싸는 사각형과 부류, 신뢰도를 함께 찾는 작업 |
| YOLO v3 | 영상을 신경망에 한 번 통과시켜 여러 크기의 출력층에서 박스·신뢰도·부류 점수를 동시에 예측하는 검출 모델. `cv.dnn.readNet`으로 `yolov3.cfg`와 가중치를 읽고 `cv.dnn.blobFromImage`로 입력 변환, 출력 벡터마다 가장 높은 부류 점수를 고르고 중심·크기 값을 영상 좌표로 환산 |
| 비최대 억제 | 같은 물체에 겹친 여러 박스 중 신뢰도가 가장 높은 박스만 남기는 처리. `cv.dnn.NMSBoxes`에 신뢰도 0.5, 겹침 0.4 기준 지정 |
| 초당 프레임 수 | 1초에 처리하는 프레임 수로 나타낸 처리 속도. 처리한 프레임 수를 경과 시간으로 나눠 출력 |
| U-net | 영상을 줄이며 특징을 뽑는 축소 경로와 다시 키우며 화소 단위 예측을 만드는 확대 경로로 이루어진 분할 신경망. `SeparableConv2D`, `Conv2DTranspose`, `UpSampling2D`, 지름길 연결 `layers.add` |
| Sequence 데이터 공급 | 영상과 레이블 파일을 미니 배치 단위로 읽어 모델에 넘기는 클래스. `keras.utils.Sequence`를 상속한 `OxfordPets`에서 트라이맵 레이블 1·2·3을 0·1·2로 변환 |
| 의미 분할 | 화소마다 사람·도로·건물 같은 부류를 정하는 분할. 같은 부류의 여러 물체는 한 부류로 칠하는 방식. `pixellib`의 DeepLabv3 ADE20K 모델 |
| 사례 분할 | 같은 부류라도 물체 하나하나를 따로 구분해 화소 영역을 찾는 분할. `pixellib`의 Mask R-CNN COCO 모델, `select_target_classes`로 사람·책만 분할 |
| 배경 바꾸기 | 사람 영역을 분할한 뒤 나머지 배경만 흐리게 하거나 단색으로 바꾸는 처리. `pixellib.tune_bg.alter_bg`의 `blur_frame`, `color_frame` |

## 파일별 내용

| 파일 | 내용 | 핵심 코드 |
|---|---|---|
| [9-1.py](ch9/9-1.py) | YOLO v3로 사진 속 물체 검출, 부류별 색 사각형과 이름·신뢰도 표시 | `cv.dnn.readNet`, `cv.dnn.blobFromImage`, `cv.dnn.NMSBoxes` |
| [9-2.py](ch9/9-2.py) | 9-1 검출을 웹캠 프레임마다 적용 | `cv.VideoCapture`, `yolo_detect` |
| [9-3.py](ch9/9-3.py) | 9-2에 처리 프레임 수와 경과 시간 측정을 더해 초당 프레임 수 출력 | `time.time`, `n_frame` |
| [9-4.py](ch9/9-4.py) | Oxford Pets 영상으로 U-net 분할 모델 학습, 가장 좋은 모델 저장, 첫 검증 영상의 정답과 예측 표시 | `keras.utils.Sequence`, `Conv2DTranspose`, `ModelCheckpoint` |
| [9-5.py](ch9/9-5.py) | 거리 사진에 DeepLabv3 ADE20K 의미 분할, 분할 결과와 원본에 겹친 결과 표시 | `semantic_segmentation`, `segmentAsAde20k` |
| [9-6.py](ch9/9-6.py) | 웹캠 영상에 의미 분할을 적용해 겹친 결과를 표시하고 동영상 파일로 저장 | `process_camera_ade20k` |
| [9-7.py](ch9/9-7.py) | 거리 사진에 Mask R-CNN 사례 분할, 물체마다 영역과 박스 표시 | `instance_segmentation`, `segmentImage` |
| [9-8.py](ch9/9-8.py) | 웹캠 영상에서 사람과 책만 사례 분할 | `select_target_classes`, `process_camera` |
| [9-9.py](ch9/9-9.py) | PyQt5 콤보 상자에서 고른 방식으로 웹캠 영상 속 사람 뒤 배경을 세 단계로 흐리거나 단색으로 변경 | `alter_bg`, `blur_frame`, `color_frame` |

`soccer.jpg`, `busy_street.jpg`: 검출·분할 입력 사진. `coco_names.txt`: YOLO v3가 쓰는 COCO 부류 이름. `yolov3.cfg`: YOLO v3 신경망 구성 파일.

실행에 필요한 `yolov3.weights`, `deeplabv3_xception65_ade20k.h5`, `mask_rcnn_coco.h5`, `xception_pascalvoc.pb` 모델 파일과 `datasets/oxford_pets` 데이터셋은 저장소에 없어 실행 전 별도 준비.
