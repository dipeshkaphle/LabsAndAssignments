import collections


class Soduku:
    def __init__(self, dimension: int):
        self.M = dimension

    def puzzle(self, grid):
        for i in range(self.M):
            for j in range(self.M):
                print(grid[i][j], end=" ")
            print()

    def row_check(self, grid, row, num):
        for x in range(9):
            if(grid[row][x] == num):
                return False
        return True

    def col_check(self, grid, col, num):
        for x in range(9):
            if(grid[x][col] == num):
                return False
        return True

    def sub_grid_check(self, grid, row, col,  num):
        startRow = row - row % 3
        startCol = col - col % 3
        for i in range(3):
            for j in range(3):
                if grid[i + startRow][j + startCol] == num:
                    return False
        return True

    def solve(self, grid, row, col, num):
        return self.row_check(grid, row, num) \
            and self.col_check(grid, col, num) \
            and self.sub_grid_check(grid, row, col, num)

    def soduku(self, grid, row, col):
        M = self.M
        if (row == M - 1 and col == M):
            return True
        if col == M:
            row += 1
            col = 0
        if grid[row][col] > 0:
            return self.soduku(grid, row, col + 1)
        for num in range(1, M + 1, 1):

            if self.solve(grid, row, col, num):
                grid[row][col] = num
                if self.soduku(grid, row, col + 1):
                    return True
            grid[row][col] = 0
        return False


'''0 means the cells where no value is assigned'''
grid = [[2, 5, 0, 0, 3, 0, 9, 0, 1],
        [0, 1, 0, 0, 0, 4, 0, 0, 0],
        [4, 0, 7, 0, 0, 0, 2, 0, 8],
        [0, 0, 5, 2, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 9, 8, 1, 0, 0],
        [0, 4, 0, 0, 0, 3, 0, 0, 0],
        [0, 0, 0, 3, 6, 0, 0, 7, 2],
        [0, 7, 0, 0, 0, 0, 0, 0, 3],
        [9, 0, 3, 0, 0, 0, 6, 0, 4]]


s = Soduku(9)

if (s.soduku(grid, 0, 0)):
    s.puzzle(grid)
else:
    print("Solution does not exist:(")
