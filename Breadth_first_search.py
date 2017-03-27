from random import *

class Puzzle:
    def __init__(self):
        self.board = []
        self.move_h = None
        self.h1 = 0
        self.h2 = 0

    def random_board(self, times):
        for i in range(1, 9):
            self.board.append(i)
        self.board.append(0)

        for i in range(0,times):
            rand_dir = randint(1,4)
            pos_0 = self.board.index(0)
            if rand_dir == 1 and pos_0 > 2:
                self.move(1) #Up
            elif rand_dir == 2 and pos_0 < 6:
                self.move(2) #Down
            elif rand_dir == 3 and pos_0 != 0 and pos_0 != 3 and pos_0 != 6:
                self.move(3) #Left
            elif rand_dir == 4 and pos_0 != 2 and pos_0 != 5 and pos_0 != 8:
                self.move(4) #Right

    def move(self, direction):
        # up = 1
        # down = 2
        # left = 3
        # right = 4

        if (direction == 1):
            pos_0 = self.board.index(0)
            self.board[pos_0] = self.board[pos_0 - 3]
            self.board[pos_0 - 3] = 0
            self.h1 = self.h1 + 1
            self.move_h = "Up"

        elif (direction == 2):
            pos_0 = self.board.index(0)
            self.board[pos_0] = self.board[pos_0 + 3]
            self.board[pos_0 + 3] = 0
            self.h1 = self.h1 + 1
            self.move_h = "Down"

        elif (direction == 3):
            pos_0 = self.board.index(0)
            self.board[pos_0] = self.board[pos_0 - 1]
            self.board[pos_0 - 1] = 0
            self.h1 = self.h1 + 1
            self.move_h = "Left"

        elif (direction == 4):
            pos_0 = self.board.index(0)
            self.board[pos_0] = self.board[pos_0 + 1]
            self.board[pos_0 + 1] = 0
            self.h1 = self.h1 + 1
            self.move_h = "Right"

    def show(self):
        if self.move_h is not None:
            print self.move_h
        for i in range(0, 9, 3):
            print '[{}][{}][{}]' .format(puzz.board[i], puzz.board[i+1], puzz.board[i+2])

puzz = Puzzle()
puzz.random_board(40)
puzz.move(1)
puzz.show()
