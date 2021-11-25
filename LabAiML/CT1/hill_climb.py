from time import time


class Node(object):
    """
    Represent state of board in 8 puzzle problem.
    """
    n = 0

    def __init__(self, board, prev_state=None):
        assert len(board) == 9

        self.board = board[:]
        self.prev = prev_state
        self.step = 0
        Node.n += 1

        if self.prev:
            self.step = self.prev.step + 1

    def __eq__(self, other):
        """Check wether two state is equal."""
        return self.board == other.board

    def __hash__(self):
        """Return hash code of object.

        Used for comparing elements in set
        """
        h = [0, 0, 0]
        h[0] = self.board[0] << 6 | self.board[1] << 3 | self.board[2]
        h[1] = self.board[3] << 6 | self.board[4] << 3 | self.board[5]
        h[2] = self.board[6] << 6 | self.board[7] << 3 | self.board[8]

        h_val = 0
        for h_i in h:
            h_val = h_val * 31 + h_i

        return h_val

    def __str__(self):
        string_list = [str(i) for i in self.board]
        sub_list = (string_list[:3], string_list[3:6], string_list[6:])
        return "\n".join([" ".join(l) for l in sub_list])

    def manhattan_distance(self):
        """Return Manhattan distance of state."""
        distance = 0
        goal = [1, 2, 3, 4, 5, 6, 7, 8, 0]
        for i in range(1, 9):
            xs, ys = self.__i2pos(self.board.index(i))
            xg, yg = self.__i2pos(goal.index(i))
            distance += abs(xs-xg) + abs(ys-yg)
        return distance

    def hamming_distance(self):
        """Return Hamming distance of state."""
        distance = 0
        goal = [1, 2, 3, 4, 5, 6, 7, 8, 0]
        for i in range(9):
            if goal[i] != self.board[i]:
                distance += 1
        return distance

    def next(self):
        """Return next states from this state."""
        next_moves = []
        i = self.board.index(0)

        next_moves = (self.move_up(i), self.move_down(
            i), self.move_left(i), self.move_right(i))

        return [s for s in next_moves if s]

    def move_right(self, i):
        x, y = self.__i2pos(i)
        if y < 2:
            right_state = Node(self.board, self)
            right = self.__pos2i(x, y+1)
            right_state.__swap(i, right)
            return right_state

    def move_left(self, i):
        x, y = self.__i2pos(i)
        if y > 0:
            left_state = Node(self.board, self)
            left = self.__pos2i(x, y - 1)
            left_state.__swap(i, left)
            return left_state

    def move_up(self, i):
        x, y = self.__i2pos(i)
        if x > 0:
            up_state = Node(self.board, self)
            up = self.__pos2i(x - 1, y)
            up_state.__swap(i, up)
            return up_state

    def move_down(self, i):
        x, y = self.__i2pos(i)
        if x < 2:
            down_state = Node(self.board, self)
            down = self.__pos2i(x + 1, y)
            down_state.__swap(i, down)
            return down_state

    def __swap(self, i, j):
        self.board[j], self.board[i] = self.board[i], self.board[j]

    def __i2pos(self, index):
        return (int(index / 3), index % 3)

    def __pos2i(self, x, y):
        return x * 3 + y


class Searcher(object):
    """Searcher that manuplate searching process."""

    def __init__(self, start, goal):
        self.start = start
        self.goal = goal

    def print_path(self, state):
        path = []
        while state:
            path.append(state)
            state = state.prev
        path.reverse()
        print("\n-->\n".join([str(state) for state in path]))

    def hill_climbing(self):
        """Run hill climbing search."""
        stack = [self.start]

        while stack:
            state = stack.pop()
            if state == self.goal:
                self.print_path(state)
                print("Found solution")
                break

            h_val = state.manhattan_distance() + state.hamming_distance()
            next_state = False
            for s in state.next():
                h_val_next = s.manhattan_distance() + s.hamming_distance()
                if h_val_next < h_val:
                    next_state = s
                    h_val = h_val_next
                    stack.append(next_state)
                    break

            if not next_state:
                self.print_path(state)
                print("Cannot find solution")


if __name__ == "__main__":

    print("Search for solution\n")
    start = []
    # The input file must be called input.txt
    '''
    The default input.txt has
    6 4 2
    1 0 3
    7 5 8

    '''

    for line in open("input.txt").readlines():
        for n in line.split():
            start.append(int(n))
    start = Node(start)
    goal = Node([1, 2, 3, 4, 5, 6, 7, 8, 0])

    search = Searcher(start, goal)

    start_time = time()
    search.hill_climbing()
    end_time = time()
    elapsed = end_time - start_time
    print("Search time: %s" % elapsed)
