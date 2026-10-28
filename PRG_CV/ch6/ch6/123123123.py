import cv2
import numpy as np
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QVBoxLayout
from PyQt5.QtCore import Qt, QTimer
from PyQt5.QtGui import QImage, QPixmap
import sys
import os


def detect_sign(frame, templates, sift, kp_list, des_list):
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    kp2, des2 = sift.detectAndCompute(gray, None)

    if des2 is None:
        return frame

    bf = cv2.BFMatcher()

    for template, kp1, des1 in zip(templates, kp_list, des_list):

        matches = bf.knnMatch(des1, des2, k=2)
        good = [m for m, n in matches if m.distance < 0.8 * n.distance]

        if len(good) > 5:
            src_pts = np.float32([kp1[m.queryIdx].pt for m in good]).reshape(-1, 1, 2)
            dst_pts = np.float32([kp2[m.trainIdx].pt for m in good]).reshape(-1, 1, 2)

            M, mask = cv2.findHomography(src_pts, dst_pts, cv2.RANSAC, 5.0)

            if M is not None:
                inliers = int(mask.sum())

                if inliers > 4:
                    h, w = template.shape
                    pts = np.float32([[0,0],[0,h],[w,h],[w,0]]).reshape(-1, 1, 2)
                    dst = cv2.perspectiveTransform(pts, M)
                    frame = cv2.polylines(frame, [np.int32(dst)], True, (0,255,0), 3)

    return frame


class VideoApp(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("속도표지판(30) 탐지")
        self.resize(960, 540)

        # 스크립트 기준 절대경로
        BASE_DIR = os.path.dirname(os.path.abspath(__file__))

        # 템플릿
        self.templates = [
            cv2.imread(os.path.join(BASE_DIR, "speed30.png"), 0),
            cv2.imread(os.path.join(BASE_DIR, "speed30_B.png"), 0),
            cv2.imread(os.path.join(BASE_DIR, "speed30_C.png"), 0)
        ]

        for i, temp in enumerate(self.templates):
            if temp is None:
                raise FileNotFoundError(f"템플릿 {i} 로드 실패: {os.path.join(BASE_DIR, f'speed30.png' if i == 0 else f'speed30_{chr(66+i-1)}.png')}")

        self.sift = cv2.SIFT_create()

        self.kp_list = []
        self.des_list = []

        for temp in self.templates:
            kp, des = self.sift.detectAndCompute(temp, None)
            self.kp_list.append(kp)
            self.des_list.append(des)

        # UI
        self.label = QLabel(self)
        self.label.setAlignment(Qt.AlignCenter)
        layout = QVBoxLayout()
        layout.addWidget(self.label)
        self.setLayout(layout)

        # 영상 (스크립트와 같은 폴더 기준)
        video_path = os.path.join(BASE_DIR, "20260429_road.mp4")
        self.cap = cv2.VideoCapture(video_path)

        if not self.cap.isOpened():
            raise FileNotFoundError(f"영상 파일을 열 수 없습니다: {video_path}")

        # FPS
        self.fps = self.cap.get(cv2.CAP_PROP_FPS)
        if self.fps <= 0:
            self.fps = 30

        self.frame_jump = 1

        # 2배속 (타이머 15ms)
        self.timer = QTimer()
        self.timer.timeout.connect(self.update_frame)
        self.timer.start(15)

    def update_frame(self):
        ret, frame = self.cap.read()
        if not ret:
            self.timer.stop()
            return

        # 프레임 점프
        current_frame = self.cap.get(cv2.CAP_PROP_POS_FRAMES)
        self.cap.set(cv2.CAP_PROP_POS_FRAMES, current_frame + self.frame_jump)

        frame = detect_sign(frame, self.templates, self.sift, self.kp_list, self.des_list)

        rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        h, w, ch = rgb.shape
        qt_img = QImage(rgb.data, w, h, ch * w, QImage.Format_RGB888)

        self.label.setPixmap(
            QPixmap.fromImage(qt_img).scaled(
                self.label.width(),
                self.label.height(),
                Qt.KeepAspectRatio,
                Qt.SmoothTransformation
            )
        )

    def closeEvent(self, event):
        self.timer.stop()
        self.cap.release()
        event.accept()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = VideoApp()
    window.show()
    sys.exit(app.exec_())