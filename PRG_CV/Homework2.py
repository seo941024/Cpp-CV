'''요구사항 중 4~5번 가로세로 비율 축소, 텍스트 삽입 후
영상 저장유무를 몰라 출력만 하는걸로 설정했습니다.

파일 파일 변환 후 저장하는 코딩까지 할 시,

cv.imwrite('santorini_small_text.jpg',img_small)
cv.imwrite('santorini_small_gray_text.jpg',img_small_gray)

을 활성화합니다.
'''

import cv2 as cv
import sys

image=cv.imread('santorini.jpg')

#파일 찾지 못할 시, 프로그램 종료
if image is None:
    sys.exit("파일을 찾을 수 없어 프로그램을 종료합니다.")
    cv.destroyAllWindows()


#터미널에 데이터 타입, 이미지 크기 띄우기
print("데이터 타입: ", type(image))
print("이미지 크기 (세로, 가로, 채널) : ", image.shape)

#흑백처리
gray=cv.cvtColor(image, cv.COLOR_BGR2GRAY)

#크기조정
img_small=cv.resize(image, dsize=(0,0),fx=0.5,fy=0.5)
img_small_gray=cv.resize(gray, dsize=(0,0),fx=0.5,fy=0.5)

#retangle 이미지 사각형 출력(보색)
cv.rectangle(img_small, (5, 250), (150, 293), (192, 255, 244), 2)
cv.rectangle(img_small_gray, (5, 250), (150, 293), (255, 255, 255), 2)

#사진에 텍스트 "2026.03.20"입력(보색)
cv.putText(img_small, "2026.03.20", (15, 280),\
           cv.FONT_HERSHEY_SIMPLEX, 0.7, (192, 255, 244), 2)
cv.putText(img_small_gray, "2026.03.20", (15, 280),\
           cv.FONT_HERSHEY_SIMPLEX, 0.7, (255, 255, 255), 2)

#변환 후 출력
cv.imshow('Color image small',img_small)
cv.imshow('Gray image small',img_small_gray)

#변환 후 저장
#cv.imwrite('santorini_small_text.jpg',img_small)
#cv.imwrite('santorini_small_gray_text.jpg',img_small_gray)

cv.waitKey()
cv.destroyAllWindows()