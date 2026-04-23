import skimage
from skimage import graph, segmentation, data  # 필요한 서브 모듈 직접 임포트함
import numpy as np
import cv2 as cv
import time

# 샘플 데이터 로드함
coffee = data.coffee()

start = time.time()

# SLIC 알고리즘으로 슈퍼픽셀 분할함
slic = segmentation.slic(coffee, compactness=20, n_segments=600, start_label=1)

# RAG(Region Adjacency Graph) 생성함 (future 경로 제거함)
g = graph.rag_mean_color(coffee, slic, mode="similarity")

# 정규화 절단(Normalized Cut) 수행함 (future 경로 제거함)
ncut = graph.cut_normalized(slic, g)

print(coffee.shape, " Coffee 영상을 분할하는데 ", time.time() - start, "초 소요됨")

# 분할 경계선을 영상에 표시함
marking = segmentation.mark_boundaries(coffee, ncut)
ncut_coffee = np.uint8(marking * 255.0)

# 결과 화면 출력함 (RGB를 BGR로 변환함)
cv.imshow("Normalized cut", cv.cvtColor(ncut_coffee, cv.COLOR_RGB2BGR))

cv.waitKey()
cv.destroyAllWindows()
