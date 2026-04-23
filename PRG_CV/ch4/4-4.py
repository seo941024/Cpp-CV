import cv2 as cv
import numpy as np

img = cv.imread('apples.jpg')
output = img.copy()

# 1. HSV 변환
hsv = cv.cvtColor(img, cv.COLOR_BGR2HSV)

# 2. 빨간색 마스크 (두 구간)
lower_red1 = np.array([0, 100, 100])
upper_red1 = np.array([10, 255, 255])

lower_red2 = np.array([160, 100, 100])
upper_red2 = np.array([180, 255, 255])

mask1 = cv.inRange(hsv, lower_red1, upper_red1)
mask2 = cv.inRange(hsv, lower_red2, upper_red2)
mask = mask1 + mask2

# 3. 노이즈 제거
kernel = np.ones((5,5), np.uint8)
mask = cv.morphologyEx(mask, cv.MORPH_CLOSE, kernel)
mask = cv.morphologyEx(mask, cv.MORPH_OPEN, kernel)

# 4. 블러
mask = cv.GaussianBlur(mask, (9,9), 2)

# 5. Contour 찾기
contours, _ = cv.findContours(mask, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE)

apple_count = 0

for cnt in contours:
    area = cv.contourArea(cnt)

    # 6. 너무 작은 영역 제거
    if area < 2000:
        continue

    # 7. 원형도 계산 (circularity)
    perimeter = cv.arcLength(cnt, True)
    if perimeter == 0:
        continue

    circularity = 4 * np.pi * (area / (perimeter * perimeter))

    # 8. 원에 가까운 것만 선택
    if circularity > 0.7:
        (x, y), radius = cv.minEnclosingCircle(cnt)

        if radius > 30:
            center = (int(x), int(y))
            radius = int(radius)

            cv.circle(output, center, radius, (0,255,0), 2)
            cv.circle(output, center, 3, (0,0,255), -1)

            apple_count += 1

# 9. 개수 출력
cv.putText(output, f'Apples: {apple_count}', (30, 50),
           cv.FONT_HERSHEY_SIMPLEX, 1.2, (0,0,255), 3)

# 10. 결과 출력
cv.imshow("Mask", mask)
cv.imshow("Apple Detection (Contour)", output)

cv.waitKey(0)
cv.destroyAllWindows()