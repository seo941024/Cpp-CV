# ch8 · 컨볼루션 신경망

컨볼루션층으로 영상의 지역 패턴을 학습하는 CNN 구성, 데이터 증대, 사전 학습 모델 분류, DenseNet121 전이 학습 견종 분류와 PyQt5 견종 인식 앱 구현.

## 다룬 개념

| 개념 | 뜻과 사용 방법 |
|---|---|
| 컨볼루션층 | 작은 필터를 영상 위로 옮기며 곱해 더해서 특징 맵을 만드는 층. 필터 가중치를 학습해 에지·질감 같은 지역 패턴 추출. `Conv2D`에 필터 수, 커널 크기, `padding` 지정 |
| 풀링층 | 특징 맵의 작은 구역마다 최댓값만 남겨 크기를 줄이는 층. 위치가 조금 바뀌어도 같은 값이 남는 특징 추출. `MaxPooling2D` |
| LeNet-5 구조 | 컨볼루션과 풀링을 번갈아 쌓은 초기 CNN 구조. 6·16·120 필터 컨볼루션층과 84 노드 완전연결층으로 MNIST 분류 |
| 드롭아웃 | 학습 중 노드 일부를 무작위로 꺼서 과적합을 줄이는 기법. 컨볼루션 묶음 뒤 `Dropout(0.25)`, 완전연결층 뒤 `Dropout(0.5)` |
| 데이터 증대 | 학습 영상을 회전·이동·뒤집기로 변형해 데이터를 늘리는 방법. `ImageDataGenerator`에 회전 20도, 가로·세로 이동 0.2, 좌우 뒤집기 지정 |
| 사전 학습 모델 | ImageNet 같은 큰 데이터셋으로 미리 학습해 공개된 모델. `ResNet50(weights='imagenet')`으로 사진의 상위 5개 부류와 확률 출력 |
| 전이 학습 | 사전 학습 모델의 특징 추출 부분을 가져와 새 출력층을 붙인 뒤 새 데이터로 다시 학습하는 방법. `DenseNet121(include_top=False)` 위에 120부류 출력층을 쌓아 Stanford Dogs 견종 분류 |
| 폴더 기반 데이터셋 | 하위 폴더 이름을 부류로 삼아 영상을 읽는 데이터셋 구성. `image_dataset_from_directory`에 `validation_split=0.2`로 학습·검증 분할 |
| 학습 진행 콜백 | 학습 중 에포크와 배치가 끝날 때마다 호출되는 함수. `Callback`을 상속한 `DetailedProgressCallback`으로 배치별 손실·정확도와 에포크 결과 출력 |

## 파일별 내용

| 파일 | 내용 | 핵심 코드 |
|---|---|---|
| [8-1.py](8-1.py) | LeNet-5 구조 CNN으로 MNIST 분류 | `Conv2D(6,(5,5))`, `MaxPooling2D`, `Dense(units=84)` |
| [8-2.py](8-2.py) | 컨볼루션 두 층씩 두 묶음과 드롭아웃을 둔 CNN으로 CIFAR-10 분류, 정확도·손실 그래프 표시 | `Conv2D(32,(3,3))`, `Dropout(0.25)`, `hist.history` |
| [8-3.py](8-3.py) | 8-2와 같은 구조의 CNN을 MNIST에 학습해 `cnn_v2.h5`로 저장 | `input_shape=(28,28,1)`, `cnn.save` |
| [8-4.py](8-4.py) | 7장 필기 숫자 인식 화면에 CNN 모델 적용, 입력을 28×28×1 형태로 변환 | `load_model('cnn_v2.h5')`, `reshape(5,28,28,1)` |
| [8-5.py](8-5.py) | CIFAR-10 앞 15장에 회전·이동·뒤집기 증대를 적용해 생성 결과를 세 번 표시 | `ImageDataGenerator`, `generator.flow`, `gen.next` |
| [8-6.py](8-6.py) | ResNet50으로 `rabbit.jpg` 분류, 상위 5개 부류와 확률을 영상에 표시 | `ResNet50`, `preprocess_input`, `decode_predictions` |
| [8-7.py](8-7.py) | DenseNet121 전이 학습으로 Stanford Dogs 견종 분류, 학습 모델과 견종 이름 목록 저장 | `DenseNet121`, `image_dataset_from_directory`, `pickle.dump` |
| [8-8.py](8-8.py) | 강아지 사진을 열고 품종 인식 버튼으로 상위 5개 견종과 확률 표시 | `QFileDialog`, `np.argsort`, `pickle.load` |

`rabbit.jpg`: 8-6 입력 사진. `dog_species_names.txt`: 8-7이 `pickle`로 저장한 견종 이름 목록, 확장자는 `.txt`지만 pickle 바이너리 파일.

`8-4.py`는 `8-3.py`의 `cnn_v2.h5`, `8-8.py`는 `8-7.py`의 `cnn_for_stanford_dogs.h5`를 불러 사용. 모델 파일과 `datasets/stanford_dogs` 데이터셋은 저장소에 없어 실행 전 별도 준비.
