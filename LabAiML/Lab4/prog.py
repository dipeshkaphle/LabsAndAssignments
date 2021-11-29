from math import exp
import random
from copy import deepcopy
import time

N_QUEENS = 8
temp = 2000


def calculate_threat(n):
    '''Combination formula. It is choosing two queens in n queens'''
    if n < 2:
        return 0
    if n == 2:
        return 1
    return (n - 1) * n / 2


def make_board(n):
    '''Create a chess boad with a queen on a row'''
    chess_board = {}
    temp = list(range(n))
    # shuffle to make sure it is random
    random.shuffle(temp)  
    column = 0

    while len(temp) > 0:
        row = random.choice(temp)
        chess_board[column] = row
        temp.remove(row)
        column += 1
    del temp
    return chess_board


def cost(chess_board):
    '''Calculate how many pairs of threaten queen'''
    threat = 0
    m_chessboard = {}
    a_chessboard = {}

    for column in chess_board:
        temp_m = column - chess_board[column]
        temp_a = column + chess_board[column]
        if temp_m not in m_chessboard:
            m_chessboard[temp_m] = 1
        else:
            m_chessboard[temp_m] += 1
        if temp_a not in a_chessboard:
            a_chessboard[temp_a] = 1
        else:
            a_chessboard[temp_a] += 1

    for i in m_chessboard:
        threat += calculate_threat(m_chessboard[i])
    del m_chessboard

    for i in a_chessboard:
        threat += calculate_threat(a_chessboard[i])
    del a_chessboard

    return threat


def simulated_annealing():
    '''Simulated Annealing'''
    solution_found = False
    answer = make_board(N_QUEENS)

    # To avoid recounting when can not find a better state
    cost_answer = cost(answer)

    t = temp
    sch = 0.99

    while t > 0:
        t *= sch
        successor = deepcopy(answer)
        while True:
            index_1 = random.randrange(0, N_QUEENS - 1)
            index_2 = random.randrange(0, N_QUEENS - 1)
            if index_1 != index_2:
                break
        successor[index_1], successor[index_2] = successor[index_2], \
            successor[index_1]  # swap two chosen queens
        delta = cost(successor) - cost_answer
        if delta < 0 or random.uniform(0, 1) < exp(-delta / t):
            answer = deepcopy(successor)
            cost_answer = cost(answer)
        if cost_answer == 0:
            solution_found = True
            print_chess_board(answer)
            break
    if solution_found is False:
        print("Failed")


def print_chess_board(board):
    '''Print the chess board'''
    brd = [['_' for j in range(0,N_QUEENS)] for i in range(0,N_QUEENS)]
    for column, row in board.items():
        brd[row][column] = 'Q'
        print("{} => {}".format(column, row))
    for row in brd:
        print(row)


def main():
    start = time.time()
    simulated_annealing()
    print("Runtime in second:", time.time() - start)


if __name__ == "__main__":
    main()
