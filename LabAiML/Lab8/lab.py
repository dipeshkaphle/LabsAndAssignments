from typing import List


class And:
    def __init__(self, lst: List[str]):
        self.symbols = lst

    def check(self, facts: List[str]):
        return all((x in facts) for x in self.symbols)

    def __str__(self):
        return '^'.join(self.symbols)


class Or:
    def __init__(self, lst: List[str]):
        self.symbols = lst

    def check(self, facts: List[str]):
        return any((x in facts) for x in self.symbols)

    def __str__(self):
        return '\\/'.join(self.symbols)


class Predicate:
    def __init__(self, s: str):
        lhs, rhs = [x.strip() for x in s.strip().split("=>")]
        self.lhs = And([lhs.split('^')[0].strip(), lhs.split('^')[1].strip()])
        self.rhs = rhs

    def __str__(self):
        return self.lhs.__str__() + "=>" + self.rhs.__str__()


global facts
global is_changed

is_changed = True

facts = ['A', 'B']
clauses = [Predicate(x) for x in ['H ^ S => Q', 'M ^ S => H',
           'H ^ A => M', 'M ^ B => S', 'A ^ B => M']]

needs_to_be_proved = 'Q'


def assert_fact(fact):
    global facts
    global is_changed
    if not (fact in facts):
        facts.append(fact)
        is_changed = True
    return is_changed


history = [facts.copy()]
print("Initial facts: {}".format(facts))
while is_changed:
    is_changed = False
    for clause in clauses:
        if clause.lhs.check(facts):
            if assert_fact(clause.rhs):
                print("{} are all true and it implies {} is true and is added to facts".format(
                    clause.lhs.symbols, clause.rhs))
                history.append(facts.copy())
                break

print("Final facts: {}".format(facts))
if needs_to_be_proved in facts:
    print("Q is in facts and hence proved")
else:
    print("Q is not in facts and hence cant be proved")

print("===========================================")
print("Count table")
print("===========================================")
for fct in history:
    print(fct)
