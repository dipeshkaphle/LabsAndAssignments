import matplotlib.pyplot as plt
import sys
from math import log2

file_name = sys.argv[1]

filelines = open(f"./{file_name}.txt").readlines()

worst_times = [filelines[i] for i in range(0, len(filelines), 3)]
random_times = [filelines[i] for i in range(1, len(filelines), 3)]
best_times = [filelines[i] for i in range(2, len(filelines), 3)]

sizes = [int(i.split(':')[1]) for i in worst_times]
worst_times = [float(i.split(':')[-1]) for i in worst_times]
random_times = [float(i.split(':')[-1]) for i in random_times]
best_times = [float(i.split(':')[-1]) for i in best_times]

nlognValues = list(map(lambda x: x * log2(x), sizes))
nlognConstants = list(
    map(lambda x: x[0]/x[1], list(zip(worst_times, nlognValues))))
UpperBoundConstant = max(nlognConstants)
LowerBoundConstants = list(
    map(lambda x: x[0]/x[1], list(zip(best_times, nlognValues))))
compl = "nlogn"
LowerBoundConstant = min(LowerBoundConstants)
LowerBoundTimes = [LowerBoundConstant * i for i in nlognValues]

UpperBoundTimes = [UpperBoundConstant * i for i in nlognValues]

print(f"Upper bound constant for {file_name} : {UpperBoundConstant}*{compl} ")
print(f"Lower bound constant for {file_name} : {LowerBoundConstant}*{compl} ")

plt.plot(sizes, worst_times, marker='+')
plt.plot(sizes, random_times, marker='+')
plt.plot(sizes, best_times, marker='+')
plt.plot(sizes, UpperBoundTimes, marker='+')
plt.plot(sizes, LowerBoundTimes, marker='+')

plt.legend(["Worst", "Random", "Best",
            f"Upper Bound Graph,c={UpperBoundConstant}, c*{compl}", f"Lower Bound Graph , c={LowerBoundConstant}, c*{compl}"])

plt.xlabel(f"Size of input {file_name} Sort")
plt.ylabel(f"Time for {file_name} sort")
plt.show()
