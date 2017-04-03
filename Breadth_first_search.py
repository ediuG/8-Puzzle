from random import randint
from collections import deque
import copy

class Puzzle(object):
    """
        8 Puzzle Game with
        - random Board
        - move space
        - show current Board position
    """

    def __init__(self, board=[1, 2, 3, 4, 5, 6, 7, 8, ' ']):
        self.board = board
        self.move_history = None
        self.parent = None

    def random_board(self, times):
        """
            Create random board from the final form
                - [1][2][3]
                  [4][5][6]
                  [7][8][ ]

        """
        # add number into Board
        for i in range(1, 9):
            self.board.append(i)
        self.board.append(' ')
        print('show current board')
        self.show()

        # random number position by sliding zero
        count = 0
        move_before = 0
        while True:
            rand_dir = randint(1, 4)
            pos_0 = self.board.index(' ')

            if count == times:
                break
            elif rand_dir == 1 and pos_0 > 2 and move_before is not 2:
                self.move(1)  # Up
                count += 1
                move_before = 1
                self.show()
            elif rand_dir == 2 and pos_0 < 6 and move_before is not 1:
                self.move(2)  # Down
                count += 1
                move_before = 2
                self.show()
            elif rand_dir == 3 and pos_0 != 0 and pos_0 != 3 and pos_0 != 6 and move_before is not 4:
                self.move(3)  # Left
                count += 1
                move_before = 3
                self.show()
            elif rand_dir == 4 and pos_0 != 2 and pos_0 != 5 and pos_0 != 8 and move_before is not 3:
                self.move(4)  # Right
                count += 1
                move_before = 4
                self.show()

    def move(self, direction):
        """
            move space

            direction represent in number
            - up = 1
            - down = 2
            - left = 3
            - right = 4
        """

        if direction == 1:
            pos_0 = self.board.index(' ')
            self.board[pos_0] = self.board[pos_0 - 3]
            self.board[pos_0 - 3] = ' '
            self.move_history = "Up"
            # self.show()

        elif direction == 2:
            pos_0 = self.board.index(' ')
            self.board[pos_0] = self.board[pos_0 + 3]
            self.board[pos_0 + 3] = ' '
            self.move_history = "Down"
            # self.show()

        elif direction == 3:
            pos_0 = self.board.index(' ')
            self.board[pos_0] = self.board[pos_0 - 1]
            self.board[pos_0 - 1] = ' '
            self.move_history = "Left"
            # self.show()

        elif direction == 4:
            pos_0 = self.board.index(' ')
            self.board[pos_0] = self.board[pos_0 + 1]
            self.board[pos_0 + 1] = ' '
            self.move_history = "Right"
            # self.show()

    def show(self):
        """
            show board in console in 3x3 table
        """
        if self.move_history is not None:
            print(self.move_history)
        for i in range(0, 9, 3):
            print('[{}][{}][{}]' .format(self.board[i],
                                         self.board[i + 1], self.board[i + 2]))

def is_in_set(sett, puzzle):
    for i in range(0, len(sett)):
        if puzzle.board == sett[i].board:
            return False
    return True


def bfs(puzzle):
    s = []
    ans = []
    queue = deque()

    s.append(puzzle)
    queue.append(puzzle)

    # while len(queue) > 0:
    for y in range(0, 4):
        puzzle_temp = copy.deepcopy(queue.popleft())
        print("////////////////////")
        puzzle_temp.show()
        print("////////////////////")
        # puzzle_temp = Puzzle(queue.popleft().board)
        if puzzle_temp.board == [1, 2, 3, 4, 5, 6, 7, 8, ' ']:
            print("found")
            while puzzle_temp.parent is not None:
                ans.append(puzzle_temp)
                puzzle_temp = puzzle_temp.parent
            puzzle.show()
            for i in reversed(range(len(ans), -1, -1)):
                ans[i].show()
            break
        else:
            pos_0 = puzzle_temp.board.index(' ')
            for i in range(1, 5):
                if (i == 1 and pos_0 > 2) or (i == 2 and pos_0 < 6) or (i == 3 and pos_0 != 0 and pos_0 != 3 and pos_0 != 6) or (i == 4 and pos_0 != 2 and pos_0 != 5 and pos_0 != 8):
                    # print('puzzle_temp.board :> {} ' .format(puzzle_temp.board))
                    # print(puzzle_temp)
                    # tmp = Puzzle(puzzle_temp.board)
                    tmp = copy.deepcopy(puzzle_temp)
                    tmp.move(i)
                    if is_in_set(s, tmp):
                        # print("tmp object moved")
                        # print('tmp.board :> {} ' .format(tmp.board))
                        s.append(tmp)
                        tmp.parent = puzzle_temp
                        queue.append(tmp)

        # print(len(queue))
        for i in range(0, len(s)):
            s[i].show()
        # print(puzzle.board)
        print("================================================")


def main():
    puzz = Puzzle()
    puzz.random_board(2)
    print("_______________________start BFS___________________________")
    bfs(puzz)


if __name__ == '__main__':
    main()
