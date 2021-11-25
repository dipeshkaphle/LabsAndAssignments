"""
for each node inp=(list), 
    use only truth table that has the parent values set to to correct value,
    check if the current variable generates different outputs at all
    if no 
        change the current variable to next in list, start again with the previous value set/unset
    add two children and update their truth tables by setting values for current variable
"""

from typing import List
def generate_tt(variables: List[str]):
    sz =  len(variables)
    table=[]
    for i in range(0, 1<<(sz)):
        new_row=dict()
        for j in range(sz):
            val = False
            if ((i & (1<<j)) !=0):
                val = True
            new_row[variables[j]]=val
        table.append(new_row)
    return table
def useful(tt):
    first = True;
    buff = False;
    for row in tt:
        if first:
            first = False
            buff = eval(row)
        else:
            if eval(row) != buff:
                return True
    return False
def eval(list):
    return (list['A'] and list['B']) or (list['C'] and list["D"])
class node:
    def __init__(self,name):
        self.name = name
        self.true = None
        self.false = None
def maketree(varlist, tt,tabs = 0):
    if len(varlist)==0:
        if eval(tt[0]) == True:
            print(tabs*"    ","yes")
        else:
            print(tabs*"    ","no")
        return node("Leaf")
    if not useful(tt):
        return maketree(varlist[1:],list(filter(lambda ele: ele[varlist[0]]==True,tt)),tabs);
    else:
        newnode = node(varlist[0]) 
        print(tabs*"    ",newnode.name," true")
        newnode.true = maketree(varlist[1:],list(filter(lambda ele: ele[varlist[0]]==True,tt)),tabs+1)
        print(tabs*"    ",newnode.name," false")
        newnode.false = maketree(varlist[1:],list(filter(lambda ele: ele[varlist[0]]==False,tt)),tabs+1)
        return newnode
inputStr = ["A","B","C","D","E","F","G","H","I","J"]
root = maketree(inputStr,generate_tt(inputStr))


"""
2.
a.
b.
c.
"""