import cv2
import os

# 파일 기준 경로 (VS Code에서도 안정적으로)
base_dir = os.path.dirname(__file__)
img_path = os.path.join(base_dir, 'apples.jpg')

# 이미지 읽기
img = cv2.imread(img_path)
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# --- Sobel ---
sobelx = cv2.Sobel(gray, cv2.CV_64F, 1, 0, ksize=3)
sobely = cv2.Sobel(gray, cv2.CV_64F, 0, 1, ksize=3)

# 보기 좋게 변환 (중요!)
sobelx = cv2.convertScaleAbs(sobelx)
sobely = cv2.convertScaleAbs(sobely)

# --- Canny ---
canny = cv2.Canny(gray, 100, 200)

# --- Contour ---
contours, _ = cv2.findContours(canny, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
contour_img = img.copy()
cv2.drawContours(contour_img, contours, -1, (0, 255, 0), 2)

scale = 0.5

img_show = cv2.resize(img, None, fx=scale, fy=scale)
gray_show = cv2.resize(gray, None, fx=scale, fy=scale)
sobelx_show = cv2.resize(sobelx, None, fx=scale, fy=scale)
sobely_show = cv2.resize(sobely, None, fx=scale, fy=scale)
canny_show = cv2.resize(canny, None, fx=scale, fy=scale)
contour_show = cv2.resize(contour_img, None, fx=scale, fy=scale)

# --- 화면 출력 ---
cv2.imshow('Original', img_show)
cv2.imshow('Gray', gray_show)
cv2.imshow('Sobel X', sobelx_show)
cv2.imshow('Sobel Y', sobely_show)
cv2.imshow('Canny', canny_show)
cv2.imshow('Contour', contour_show)

# 키 입력 대기 (이거 없으면 창 바로 꺼짐)
cv2.waitKey(0)
cv2.destroyAllWindows()

# --- 파일 저장 ---
cv2.imwrite(os.path.join(base_dir, 'sobelx.jpg'), sobelx)
cv2.imwrite(os.path.join(base_dir, 'sobely.jpg'), sobely)
cv2.imwrite(os.path.join(base_dir, 'canny.jpg'), canny)
cv2.imwrite(os.path.join(base_dir, 'contour.jpg'), contour_img)