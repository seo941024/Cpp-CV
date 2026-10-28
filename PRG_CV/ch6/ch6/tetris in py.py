import sys
import random
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget, QLabel, QVBoxLayout, QHBoxLayout
from PyQt5.QtCore import Qt, QTimer
from PyQt5.QtGui import QPainter, QColor, QFont

COLS = 10
ROWS = 20
BLOCK = 30

SHAPES = [
    [[1,1,1,1]],
    [[1,1],[1,1]],
    [[0,1,0],[1,1,1]],
    [[1,0],[1,0],[1,1]],
    [[0,1],[0,1],[1,1]],
    [[0,1,1],[1,1,0]],
    [[1,1,0],[0,1,1]],
]

COLORS = [
    QColor(0,255,255),    # I - cyan
    QColor(255,255,0),    # O - yellow
    QColor(255,0,255),    # T - magenta
    QColor(255,165,0),    # L - orange
    QColor(0,0,255),      # J - blue
    QColor(0,255,0),      # S - green
    QColor(255,0,0),      # Z - red
]

def rotate(shape):
    return [list(row) for row in zip(*shape[::-1])]

def new_piece():
    idx = random.randint(0, len(SHAPES)-1)
    return {'shape': SHAPES[idx], 'color': COLORS[idx],
            'x': COLS//2-1, 'y': 0, 'idx': idx}

def valid(board, piece, ox=0, oy=0, shape=None):
    s = shape if shape else piece['shape']
    for r, row in enumerate(s):
        for c, cell in enumerate(row):
            if cell:
                nx = piece['x'] + c + ox
                ny = piece['y'] + r + oy
                if nx < 0 or nx >= COLS or ny >= ROWS:
                    return False
                if ny >= 0 and board[ny][nx] is not None:
                    return False
    return True

def place(board, piece):
    for r, row in enumerate(piece['shape']):
        for c, cell in enumerate(row):
            if cell:
                board[piece['y']+r][piece['x']+c] = piece['color']

def clear_lines(board):
    new_board = [row for row in board if any(cell is None for cell in row)]
    cleared = ROWS - len(new_board)
    new_board = [[None]*COLS for _ in range(cleared)] + new_board
    return new_board, cleared


class BoardWidget(QWidget):
    def __init__(self):
        super().__init__()
        self.setFixedSize(COLS*BLOCK, ROWS*BLOCK)
        self.setStyleSheet("background-color: #111111;")
        self.board = [[None]*COLS for _ in range(ROWS)]
        self.piece = new_piece()
        self.next_piece = new_piece()
        self.score = 0
        self.level = 1
        self.lines = 0
        self.game_over = False

        self.timer = QTimer()
        self.timer.timeout.connect(self.tick)
        self.timer.start(500)

    def tick(self):
        if self.game_over:
            return
        if valid(self.board, self.piece, oy=1):
            self.piece['y'] += 1
        else:
            self.land()
        self.update()

    def land(self):
        place(self.board, self.piece)
        self.board, cleared = clear_lines(self.board)
        self.lines += cleared
        self.score += [0,100,300,500,800][cleared] * self.level
        self.level = self.lines // 10 + 1
        self.timer.setInterval(max(100, 500 - (self.level-1)*40))
        self.piece = self.next_piece
        self.next_piece = new_piece()
        if self.board[0][4] is not None:
            self.game_over = True
        self.window().update_ui()

    def ghost_y(self):
        gy = self.piece['y']
        while valid(self.board, {**self.piece, 'y': gy+1}):
            gy += 1
        return gy

    def paintEvent(self, e):
        p = QPainter(self)

        # 격자
        p.setPen(QColor(30,30,30))
        for x in range(COLS):
            p.drawLine(x*BLOCK, 0, x*BLOCK, ROWS*BLOCK)
        for y in range(ROWS):
            p.drawLine(0, y*BLOCK, COLS*BLOCK, y*BLOCK)

        # 보드
        for r in range(ROWS):
            for c in range(COLS):
                if self.board[r][c]:
                    p.fillRect(c*BLOCK+1, r*BLOCK+1, BLOCK-2, BLOCK-2, self.board[r][c])

        # 고스트
        gy = self.ghost_y()
        ghost_color = QColor(self.piece['color'])
        ghost_color.setAlpha(60)
        for r, row in enumerate(self.piece['shape']):
            for c, cell in enumerate(row):
                if cell:
                    p.fillRect((self.piece['x']+c)*BLOCK+1,
                                (gy+r)*BLOCK+1, BLOCK-2, BLOCK-2, ghost_color)

        # 현재 피스
        for r, row in enumerate(self.piece['shape']):
            for c, cell in enumerate(row):
                if cell:
                    p.fillRect((self.piece['x']+c)*BLOCK+1,
                                (self.piece['y']+r)*BLOCK+1,
                                BLOCK-2, BLOCK-2, self.piece['color'])

        # 게임오버
        if self.game_over:
            p.fillRect(0, ROWS*BLOCK//2-50, COLS*BLOCK, 100, QColor(0,0,0,180))
            p.setFont(QFont("Arial", 28, QFont.Bold))
            p.setPen(QColor(255,0,0))
            p.drawText(self.rect(), Qt.AlignCenter, "GAME OVER\nR키로 재시작")

    def keyPressEvent(self, e):
        if self.game_over:
            if e.key() == Qt.Key_R:
                self.reset()
            return                    # ← this return blocks R during normal play!
        
        if e.key() == Qt.Key_R:      # ← add this here
            self.reset()
            return
        
        if e.key() == Qt.Key_Left:
            if valid(self.board, self.piece, ox=-1):
                self.piece['x'] -= 1
        elif e.key() == Qt.Key_Right:
            if valid(self.board, self.piece, ox=1):
                self.piece['x'] += 1
        elif e.key() == Qt.Key_Down:
            if valid(self.board, self.piece, oy=1):
                self.piece['y'] += 1
        elif e.key() == Qt.Key_Up:
            rotated = rotate(self.piece['shape'])
            if valid(self.board, self.piece, shape=rotated):
                self.piece['shape'] = rotated
        elif e.key() == Qt.Key_Space:
            self.piece['y'] = self.ghost_y()
            self.land()
        self.update()

    def reset(self):
        self.board = [[None]*COLS for _ in range(ROWS)]
        self.piece = new_piece()
        self.next_piece = new_piece()
        self.score = 0
        self.level = 1
        self.lines = 0
        self.game_over = False
        self.timer.setInterval(500)
        self.window().update_ui()
        self.update()


class TetrisWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Tetris - PyQt5")
        self.setStyleSheet("background-color: #222222;")

        self.board = BoardWidget()

        # 우측 UI
        self.next_label = QLabel("NEXT")
        self.next_label.setStyleSheet("color: white; font-size: 16px; font-weight: bold;")
        self.next_label.setAlignment(Qt.AlignCenter)

        self.next_widget = NextWidget()

        self.score_label = QLabel("Score: 0")
        self.level_label = QLabel("Level: 1")
        self.lines_label = QLabel("Lines: 0")

        for lbl in [self.score_label, self.level_label, self.lines_label]:
            lbl.setStyleSheet("color: white; font-size: 14px;")
            lbl.setAlignment(Qt.AlignCenter)

        ctrl1 = QLabel("← → : 이동")
        ctrl2 = QLabel("↑ : 회전")
        ctrl3 = QLabel("↓ : 내리기")
        ctrl4 = QLabel("Space : 즉시낙하")
        ctrl5 = QLabel("R : 재시작")
        for lbl in [ctrl1, ctrl2, ctrl3, ctrl4, ctrl5]:
            lbl.setStyleSheet("color: #aaaaaa; font-size: 12px;")
            lbl.setAlignment(Qt.AlignCenter)

        side = QVBoxLayout()
        side.addWidget(self.next_label)
        side.addWidget(self.next_widget)
        side.addSpacing(20)
        side.addWidget(self.score_label)
        side.addWidget(self.level_label)
        side.addWidget(self.lines_label)
        side.addSpacing(20)
        side.addWidget(ctrl1)
        side.addWidget(ctrl2)
        side.addWidget(ctrl3)
        side.addWidget(ctrl4)
        side.addWidget(ctrl5)
        side.addStretch()

        main_layout = QHBoxLayout()
        main_layout.addWidget(self.board)
        main_layout.addLayout(side)

        container = QWidget()
        container.setLayout(main_layout)
        self.setCentralWidget(container)

    def update_ui(self):
        b = self.board
        self.score_label.setText(f"Score: {b.score}")
        self.level_label.setText(f"Level: {b.level}")
        self.lines_label.setText(f"Lines: {b.lines}")
        self.next_widget.set_piece(b.next_piece)

    def keyPressEvent(self, e):
        self.board.keyPressEvent(e)


class NextWidget(QWidget):
    def __init__(self):
        super().__init__()
        self.setFixedSize(120, 120)
        self.setStyleSheet("background-color: #111111;")
        self.piece = None

    def set_piece(self, piece):
        self.piece = piece
        self.update()

    def paintEvent(self, e):
        if not self.piece:
            return
        p = QPainter(self)
        shape = self.piece['shape']
        color = self.piece['color']
        bsize = 25
        ox = (self.width() - len(shape[0])*bsize) // 2
        oy = (self.height() - len(shape)*bsize) // 2
        for r, row in enumerate(shape):
            for c, cell in enumerate(row):
                if cell:
                    p.fillRect(ox+c*bsize+1, oy+r*bsize+1,
                                bsize-2, bsize-2, color)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = TetrisWindow()
    win.show()
    win.board.setFocus()
    sys.exit(app.exec_())