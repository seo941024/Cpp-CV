import cv2 as cv
import sys

img=cv.imread('soccer.jpg')

if img is None:
    sys.exit("파일을 찾을 수 없습니다.")

small=cv.resize(img,dsize=(0,0),fx=0.5,fy=0.5)
gray=cv.cvtColor(img,cv.COLOR_RGB2GRAY)

cv.rectangle(small, (50, 50), (200, 200), (0, 255, 0), 2)

cv.imshow('Color image',img)
cv.imshow('Gray image',gray)

cv.waitKey()
cv.destroyAllWindows()