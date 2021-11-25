def get_reverse(literal: str):
    if literal[0] == '~':
        return literal[1:]
    else:
        return '~' + literal


def is_satisfiable(n_vars, clauses):
    candidates = {frozenset()}
    for clause in clauses:
        temp = set()
        for s in candidates:
            for literal in clause:
                if get_reverse(literal) not in s:
                    temp.add(s | {literal})
        candidates = temp
        if len(candidates) == 0:
            return False
    return True


def load_case():
    n_vars, n_clauses = input().split()
    clauses = [input().strip().split(' v ')
               for _ in range(int(n_clauses))]
    return int(n_vars), clauses


def main():
    num_cases = int(input())
    outputs = []
    for _ in range(num_cases):
        n_vars, clauses = load_case()
        result = is_satisfiable(n_vars, clauses)
        if result:
            outputs.append("satisfiable")
        else:
            outputs.append("unsatisfiable")
    for out in outputs:
        print(out)


main()
