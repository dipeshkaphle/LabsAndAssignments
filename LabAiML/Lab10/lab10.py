from typing import List, Dict, Optional
import pprint


def generate_tt(variables: List[str], func):
    sz = len(variables)
    table = []
    for i in range(0, 1 << (sz)):
        new_row = dict()
        for j in range(sz):
            val = False
            if ((i & (1 << j)) != 0):
                val = True
            new_row[variables[j]] = val
        table.append((new_row, func(new_row)))

    return table


def make_node(name):
    return {'name': name, 'yes': None, 'no': None, 'yes_vals': [], 'no_vals': [], 'is_leaf': False}


def make_leaf(name):
    return {'name': name,  'is_leaf': True}


def make_node_2nd_pass(name):
    return {'name': name, 'yes': None, 'no': None, 'is_leaf': False}


def generate_decision_tree(variables: List[str], accumulated_values: Dict[str, bool],  func):
    if len(variables) == 0:
        ans = func(accumulated_values)
        return (make_leaf(str(ans)), [ans])
    else:
        nd = make_node(variables[0])
        accumulated_values[variables[0]] = True
        nd['yes'], nd['yes_vals'] = generate_decision_tree(
            variables[1:], accumulated_values, func)
        accumulated_values[variables[0]] = False
        nd['no'], nd['no_vals'] = generate_decision_tree(
            variables[1:], accumulated_values, func)
        accumulated_values.pop(variables[0])
        return (nd, nd['yes_vals'] + nd['no_vals'])


def second_pass_to_remove_redundancy(node: Dict) -> Dict:
    if node['is_leaf']:
        return node
    else:
        mp = make_node_2nd_pass(node['name'])
        if node['yes_vals'] == node['no_vals']:
            return second_pass_to_remove_redundancy(node['no'])

        if all(x == node['yes_vals'][0] for x in node['yes_vals']):
            mp['yes'] = make_leaf(str(node['yes_vals'][0]))
        else:
            mp['yes'] = second_pass_to_remove_redundancy(node['yes'])
        if all(x == node['no_vals'][0] for x in node['no_vals']):
            mp['no'] = make_leaf(str(node['no_vals'][0]))
        else:
            mp['no'] = second_pass_to_remove_redundancy(node['no'])
        return mp


def print_tree(root, tabs=0):
    if root['is_leaf']:
        print(tabs*"    ", "Leaf: "+root['name'])
        return
    else:
        print(tabs*"    ", root['name'], 'yes')
        print_tree(root['yes'], tabs+1)
        print(tabs*"    ", root['name'], 'no')
        print_tree(root['no'], tabs+1)


def show_decision_tree_and_truth_table(expr, variables, func):
    print("="*80)
    print(expr)
    print("\nTRUTH TABLE FOR THE GIVEN EXPRESSION : {}".format(expr))
    print(' '.join(map(lambda x: "{:<10}".format(x), variables + ["Result"])))
    for x in generate_tt(variables, func):
        print(' '.join(map(lambda y: "{:<10}".format(
            str(y)),  list(x[0].values()) + [x[1]])))

    x = generate_decision_tree(variables, dict(), func)
    x = second_pass_to_remove_redundancy(x[0])
    print_tree(x)
    print("="*80)
    print()


inputs = [
    ("A and (not B)", ['A', 'B'], lambda h: h['A'] and not h['B']),
    ("A or (B and C)", ['A', 'B', 'C'],
     lambda h: h['A'] or (h['B'] and h['C'])),
    ("A xor B", ['A', 'B'], lambda h: h['A'] ^ h['B']),
    ("(A and B) or (C and D)", ['A', 'B', 'C', 'D'],
     lambda h: (
        h['A'] and h['B']) or (h['C'] and h['D'])),
    ("( A or B ) and (C xor D)", ['A', 'B', 'C', 'D'],
        lambda h: (h['A'] or h['B']) and (h['C'] ^ h['D']))
]

for expr, variables, func in inputs:
    show_decision_tree_and_truth_table(expr, variables, func)
