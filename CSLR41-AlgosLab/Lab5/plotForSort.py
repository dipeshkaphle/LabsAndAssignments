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


plt.plot(sizes, worst_times)
plt.plot(sizes, random_times)
plt.plot(sizes, best_times)

plt.legend(["Worst", "Random", "Best"])

plt.xlabel(f"Size of input {file_name} Sort")
plt.ylabel(f"Time for {file_name} sort")
plt.show()
