import numpy as np
import tensorflow as tf
import tensorflow.keras.datasets as ds

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.optimizers import Adam

# 1. 데이터 로드 및 전처리
(x_train, y_train), (x_test, y_test) = ds.mnist.load_data()
x_train = x_train.reshape(60000, 784).astype(np.float32) / 255.0
x_test = x_test.reshape(10000, 784).astype(np.float32) / 255.0
y_train = tf.keras.utils.to_categorical(y_train, 10)
y_test = tf.keras.utils.to_categorical(y_test, 10)

# 2. 모델 구조 설계 (노드 수 확장 및 ReLU 변경)
mlp = Sequential()
mlp.add(Dense(units=1024, activation='relu', input_shape=(784,))) # 512 -> 1024, tanh -> relu
mlp.add(Dense(units=512, activation='relu'))                     # 은닉층 한 층 더 추가해서 깊게!
mlp.add(Dense(units=10, activation='softmax'))

# 3. 컴파일 (손실함수를 크로스 엔트로피로 변경, 학습률은 Adam 최적의 0.001 유지)
mlp.compile(loss='categorical_crossentropy', 
            optimizer=Adam(learning_rate=0.001), 
            metrics=['accuracy'])

# 4. 모델 학습 (수치가 부드럽게 올라가도록 배치 사이즈 조절 가능)
mlp.fit(x_train, y_train, batch_size=128, epochs=30, validation_data=(x_test, y_test), verbose=2)

# 5. 결과 출력
res = mlp.evaluate(x_test, y_test, verbose=0)
print('정확률 =', res[1] * 100)