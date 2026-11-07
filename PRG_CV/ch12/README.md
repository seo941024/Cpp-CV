# ch12 · 3차원 비전

3차원 물체 메시에서 뽑은 점 구름 시각화와 PointNet 점 구름 분류.

## 다룬 개념

| 개념 | 뜻과 사용 방법 |
|---|---|
| 점 구름 | 물체 표면 위 3차원 좌표 점의 집합. `trimesh.load`로 메시 파일을 읽고 `sample`로 표면 점을 뽑아 matplotlib 3차원 산점도로 표시 |
| ModelNet10 | 욕조·침대·의자·모니터 같은 실내 물체 10부류의 3차원 CAD 메시 데이터셋. `tf.keras.utils.get_file`로 내려받아 부류별 `train`, `test` 폴더의 `.off` 파일 사용 |
| PointNet | 점마다 같은 신경망을 적용한 뒤 최댓값 풀링으로 하나로 묶어 점 순서와 관계없이 분류하는 신경망. 커널 크기 1인 `Conv1D`와 `GlobalMaxPooling1D`로 구성 |
| T-Net | 입력 점이나 특징을 정렬하는 변환 행렬을 예측하는 작은 신경망. 예측 행렬을 입력에 곱하고, `OrthogonalRegularizer`로 행렬이 직교 행렬에 가깝도록 규제 |
| 배치 정규화 묶음 | 층 출력에 배치 정규화와 ReLU를 이어 붙인 반복 단위. `conv_bn`, `dense_bn` 함수로 정의 |

## 파일별 내용

| 파일 | 내용 | 핵심 코드 |
|---|---|---|
| [12-1.py](12-1.py) | ModelNet10 부류마다 첫 학습 메시에서 표면 점을 뽑아 3차원 산점도로 나란히 표시 | `trimesh.load`, `mesh.sample`, `projection="3d"` |
| [12-2.py](12-2.py) | 메시를 점 구름으로 바꿔 PointNet 분류 모델 학습, 무작위 테스트 샘플의 예측과 정답을 3차원 산점도로 표시 | `tnet`, `Conv1D`, `GlobalMaxPooling1D` |
