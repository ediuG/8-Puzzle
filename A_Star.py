import copy
from collections import deque
from random import randint


class Puzzle(object):
    """
        8 Puzzle Game with
        - random Board
        - move space
        - show current Board position
    """

    def __init__(self, board=None):
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
        self.board = [1, 2, 3, 4, 5, 6, 7, 8, ' ']
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

        elif direction == 2:
            pos_0 = self.board.index(' ')
            self.board[pos_0] = self.board[pos_0 + 3]
            self.board[pos_0 + 3] = ' '
            self.move_history = "Down"

        elif direction == 3:
            pos_0 = self.board.index(' ')
            self.board[pos_0] = self.board[pos_0 - 1]
            self.board[pos_0 - 1] = ' '
            self.move_history = "Left"

        elif direction == 4:
            pos_0 = self.board.index(' ')
            self.board[pos_0] = self.board[pos_0 + 1]
            self.board[pos_0 + 1] = ' '
            self.move_history = "Right"

    def show(self):
        """
            show board in console in 3x3 table
        """

        if self.move_history is not None:
            print(self.move_history)
        for i in range(0, 9, 3):
            print('[{}][{}][{}]' .format(self.board[i],
                                         self.board[i + 1], self.board[i + 2]))

def astar(puzzle):
    """
        A star Search
    """
    pass
    s = []
    ans = []
    queue = deque()
    s.append(puzzle)
    queue.append(puzzle)

    while len(queue) > 0:
        puzzle_temp = copy.deepcopy(queue.popleft())
        if puzzle_temp.board == [1,2,3,4,5,6,7,8,' ']:
            print("found")
            while puzzle_temp.parent is not None:
                ans.append(puzzle_temp)
                puzzle_temp = puzzle_temp.parent

            puzzle.show()
            for i in range(len(ans)-1,-1,-1):
                ans[i].show()
            break
        else:
            #astar algorithm
            pass

def main():
    puzz = Puzzle()
    puzz.random_board(10)
    print("---------------------Start A star search-----------------------")
    astar(puzz)

if __name__ == '__main__':
    main()
