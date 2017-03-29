from random import randint


class Puzzle(object):
    """
        8 Puzzle Game with
        - random Board
        - move space
        - show current Board position
    """

    def __init__(self, move_time):
        self.board = []
        self.move_h = None
        self.h1 = 0
        self.h2 = 0
        self.random_board(move_time)

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
            self.h1 = self.h1 + 1
            self.move_h = "Up"
            return self.board

        elif direction == 2:
            pos_0 = self.board.index(' ')
            self.board[pos_0] = self.board[pos_0 + 3]
            self.board[pos_0 + 3] = ' '
            self.h1 = self.h1 + 1
            self.move_h = "Down"
            return self.board

        elif direction == 3:
            pos_0 = self.board.index(' ')
            self.board[pos_0] = self.board[pos_0 - 1]
            self.board[pos_0 - 1] = ' '
            self.h1 = self.h1 + 1
            self.move_h = "Left"
            return self.board

        elif direction == 4:
            pos_0 = self.board.index(' ')
            self.board[pos_0] = self.board[pos_0 + 1]
            self.board[pos_0 + 1] = ' '
            self.h1 = self.h1 + 1
            self.move_h = "Right"
            return self.board

    def show(self):
        """
            show board in console in 3x3 table
        """
        if self.move_h is not None:
            print(self.move_h)
        for i in range(0, 9, 3):
            print('[{}][{}][{}]' .format(self.board[i],
                                         self.board[i + 1], self.board[i + 2]))


def main():
    puzz = Puzzle(40)


if __name__ == '__main__':
    main()
