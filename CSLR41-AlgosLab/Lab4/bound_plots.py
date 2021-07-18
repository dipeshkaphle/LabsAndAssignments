import matplotlib.pyplot as plt
import sys

file_name = sys.argv[1]

filelines = open(f"./{file_name}.txt").readlines()

worst_times = [filelines[i] for i in range(0, len(filelines), 3)]
random_times = [filelines[i] for i in range(1, len(filelines), 3)]
best_times = [filelines[i] for i in range(2, len(filelines), 3)]

sizes = [int(i.split(':')[1]) for i in worst_times]
worst_times = [float(i.split(':')[-1]) for i in worst_times]
random_times = [float(i.split(':')[-1]) for i in random_times]
best_times = [float(i.split(':')[-1]) for i in best_times]

nSquaredValues = list(map(lambda x: x**2, sizes))
nSquaredConstants = list(
    map(lambda x: x[0]/x[1], list(zip(worst_times, nSquaredValues))))
UpperBoundConstant = max(nSquaredConstants)
nConstants = list(map(lambda x: x[0]/x[1], list(zip(best_times, sizes))))
compl = ""
if(file_name == "Selection"):
    LowerBoundConstant = min(nSquaredConstants)
    LowerBoundTimes = [LowerBoundConstant * i for i in nSquaredConstants]
    compl = "n^2"
else:
    LowerBoundConstant = min(nConstants)
    LowerBoundTimes = [LowerBoundConstant * i for i in sizes]
    compl = "n"
UpperBoundTimes = [UpperBoundConstant * i for i in nSquaredValues]

print(f"Upper bound constant for {file_name} : {UpperBoundConstant}*n^2 ")
print(f"Lower bound constant for {file_name} : {LowerBoundConstant}*{compl} ")

plt.plot(sizes, worst_times)
plt.plot(sizes, random_times)
plt.plot(sizes, best_times)
plt.plot(sizes, UpperBoundTimes)
plt.plot(sizes, LowerBoundTimes)

plt.legend(["Worst", "Random", "Best",
            f"Upper Bound Graph,c={UpperBoundConstant}, c*n^2", f"Lower Bound Graph , c={LowerBoundConstant}, c*{compl}"])

plt.xlabel(f"Size of input {file_name} Sort")
plt.ylabel(f"Time for {file_name} sort")
plt.show()
