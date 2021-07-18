import matplotlib.pyplot as plt
import sys


qsort_filelines = open(f"./QuickSort.txt").readlines()
qsort_random_filelines = open(f"./QuickSortRandom.txt").readlines()
sort_filelines = open(f"./StlSort.txt").readlines()

qsort_worst_times = [qsort_filelines[i]
                     for i in range(0, len(qsort_filelines), 3)]
qsort_rand_worst_times = [qsort_random_filelines[i]
                          for i in range(0, len(qsort_random_filelines), 3)]
sort_worst_times = [sort_filelines[i]
                    for i in range(0, len(sort_filelines), 3)]

sizes = [int(i.split(':')[1]) for i in qsort_worst_times]
qsort_worst_times = [float(i.split(':')[-1]) for i in qsort_worst_times]
qsort_rand_worst_times = [float(i.split(':')[-1])
                          for i in qsort_rand_worst_times]
sort_worst_times = [float(i.split(':')[-1]) for i in sort_worst_times]


plt.plot(sizes, qsort_worst_times)
plt.plot(sizes, qsort_rand_worst_times)
plt.plot(sizes, sort_worst_times)

plt.legend(["QSort Worst", "Qsort Random Worst", "Inbuilt Sort Worst"])

plt.xlabel(f"Size of input for Sorts")
plt.ylabel(f"Time for sorts")
plt.show()
