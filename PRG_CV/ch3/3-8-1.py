import cv2 as cv

img = cv.imread('rose.png')

# 50% 축소
resized = cv.resize(img, None, fx=0.5, fy=0.5)

# 모폴로지
kernel = cv.getStructuringElement(cv.MORPH_RECT, (5,5))

erosion = cv.erode(resized, kernel, iterations=1)
dilation = cv.dilate(resized, kernel, iterations=1)

# 30도 회전
(h, w) = resized.shape[:2]
center = (w // 2, h // 2)

M = cv.getRotationMatrix2D(center, -30, 1.0)
rotated = cv.warpAffine(resized, M, (w, h))

cv.imshow('Original', img)
cv.imshow('50% Resized', resized)
cv.imshow('Morphology1', dilation)
cv.imshow('Morphology2', erosion)
cv.imshow('30', rotated)

cv.waitKey(0)
cv.destroyAllWindows()