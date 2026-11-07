# ch11 · 트랜스포머

주의 집중으로 영상 조각 사이 관계를 계산하는 트랜스포머 비전 모델. CIFAR-10 ViT 구성과 학습, 사전 학습 ViT 분류, DETR 물체 검출, CLIP 영상-문장 유사도 계산.

## 다룬 개념

| 개념 | 뜻과 사용 방법 |
|---|---|
| 트랜스포머와 자기 주의 | 입력 조각마다 다른 모든 조각과의 관련도를 계산해 그 가중합으로 표현을 바꾸는 신경망 구조. 여러 관점의 주의를 함께 계산하는 다중 헤드 주의 `layers.MultiHeadAttention` 사용 |
| ViT | 영상을 같은 크기 패치로 잘라 단어처럼 나열한 뒤 트랜스포머 인코더로 분류하는 모델. `tf.image.extract_patches`로 패치 분할, `Dense` 층으로 패치를 임베딩 벡터로 투영 |
| 위치 임베딩 | 패치의 순서 정보를 벡터로 바꿔 패치 임베딩에 더하는 처리. 트랜스포머는 입력 순서를 스스로 구분하지 못해 필요. `layers.Embedding`에 패치 번호 `tf.range` 입력 |
| 층 정규화와 지름길 연결 | 층 정규화는 샘플 하나의 특징값을 평균 0, 분산 1로 맞추는 처리. 지름길 연결은 블록 입력을 출력에 더해 깊은 신경망의 학습을 돕는 연결. `LayerNormalization`, `layers.Add` |
| 증대 층 | 학습 때만 무작위 변형을 적용하는 Keras 층. 영상을 72×72로 키운 뒤 `RandomFlip`, `RandomRotation`, `RandomZoom` 적용 |
| Hugging Face Transformers | 공개된 사전 학습 트랜스포머 모델을 이름으로 내려받아 쓰는 라이브러리. `from_pretrained`로 전처리기와 모델을 함께 불러오기 |
| DETR | CNN 특징 위에 트랜스포머를 붙여 물체 박스 집합을 한 번에 예측하는 검출 모델. 예측마다 부류 로짓과 영상 크기 대비 비율로 된 중심·크기 박스 반환, 물체 없음 부류인 91번 제외 |
| CLIP | 영상과 문장을 같은 벡터 공간에 넣어 둘이 얼마나 맞는지 점수를 내는 모델. 사진 한 장과 후보 문장들의 점수를 `softmax` 확률로 변환 |

## 파일별 내용

| 파일 | 내용 | 핵심 코드 |
|---|---|---|
| [11-1.py](11-1.py) | 4×4 패치, 64차원 임베딩, 다중 헤드 주의 인코더 블록으로 CIFAR-10 ViT 분류, 정확도·손실 그래프 표시 | `Patches`, `PatchEncoder`, `MultiHeadAttention` |
| [11-2.py](11-2.py) | 11-1에 72×72 확대, 6×6 패치, 뒤집기·회전·확대 증대 층 추가 | `layers.Resizing`, `RandomFlip`, `RandomZoom` |
| [11-3.py](11-3.py) | `google/vit-base-patch16-224` 사전 학습 ViT로 사진 세 장 분류, 1순위 부류와 확률 출력 | `AutoImageProcessor`, `ViTForImageClassification` |
| [11-4.py](11-4.py) | `facebook/detr-resnet-50`으로 사진 속 물체 검출, 박스와 부류·확률을 OpenCV로 표시 | `DetrForObjectDetection`, `pred_boxes`, `cv.rectangle` |
| [11-5.py](11-5.py) | `openai/clip-vit-base-patch32`로 사진 한 장과 문장 네 개의 일치 확률 출력 | `CLIPProcessor`, `CLIPModel`, `logits_per_image` |

`BSDS_242078.jpg`, `BSDS_361010.jpg`, `BSDS_376001.jpg`: 분류·검출·유사도 계산 입력 사진.
