import numpy as np
import tensorflow as tf
import tensorflow.keras.datasets as ds

from tensorflow.keras.models import Sequential
# 배치 정규화(BatchNormalization)를 새로 불러와요! ⭐
from tensorflow.keras.layers import Dense, Dropout, BatchNormalization
from tensorflow.keras.optimizers import Adam 
# 정확도가 정체될 때 학습률을 자동으로 줄여줄 콜백 함수를 불러와요 📉
from tensorflow.keras.callbacks import ReduceLROnPlateau

# 1. 데이터 로드 및 전처리
(x_train, y_train), (x_test, y_test) = ds.mnist.load_data()
x_train = x_train.reshape(60000, 784).astype(np.float32) / 255.0
x_test = x_test.reshape(10000, 784).astype(np.float32) / 255.0
y_train = tf.keras.utils.to_categorical(y_train, 10)
y_test = tf.keras.utils.to_categorical(y_test, 10)

# 2. 다층 구조(Deep MLP) + 배치 정규화 모델 설계
mlp = Sequential()

# 첫 번째 은닉층 (1024 노드) + 배치 정규화 + 드롭아웃
mlp.add(Dense(units=1024, activation='relu', input_shape=(784,)))
mlp.add(BatchNormalization()) # 학습이 훨씬 깊고 안정적으로 되게 도와줘요! ✨
mlp.add(Dropout(0.3))

# 두 번째 은닉층 추가! (512 노드) + 배치 정규화 + 드롭아웃
mlp.add(Dense(units=512, activation='relu'))
mlp.add(BatchNormalization())
mlp.add(Dropout(0.3))

# 세 번째 은닉층 추가! (256 노드) + 배치 정규화 + 드롭아웃
mlp.add(Dense(units=256, activation='relu'))
mlp.add(BatchNormalization())
mlp.add(Dropout(0.3))

# 최종 출력층 (0~9 분류)
mlp.add(Dense(units=10, activation='softmax'))

# 3. 컴파일 설정
mlp.compile(loss='categorical_crossentropy',
            optimizer=Adam(learning_rate=0.001),
            metrics=['accuracy'])

# 4. 학습률 스케줄러 설정 (val_loss가 3번 넘게 안 떨어지면 학습률을 반(0.5배)으로 깎아요)
reduce_lr = ReduceLROnPlateau(monitor='val_loss', 
                              factor=0.5, 
                              patience=3, 
                              min_lr=0.00001, 
                              verbose=1)

# 5. 모델 학습 (30번만 돌려도 99%를 충분히 노릴 수 있어요)
mlp.fit(x_train, y_train, 
        batch_size=256, 
        epochs=30, 
        validation_data=(x_test, y_test), 
        callbacks=[reduce_lr], 
        verbose=2)

# 6. 최종 평가 및 출력
res = mlp.evaluate(x_test, y_test, verbose=0)
print('\n==============================')
print('최종 검증 정확률 =', res[1] * 100)
print('==============================')