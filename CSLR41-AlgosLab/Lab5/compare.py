import matplotlib.pyplot as plt
import sys


merge_filelines = open(f"./MergeSort.txt").readlines()
heap_filelines = open(f"./HeapSort.txt").readlines()
sort_filelines = open(f"./StlSort.txt").readlines()

merge_worst_times = [merge_filelines[i]
                     for i in range(0, len(merge_filelines), 3)]
heap_worst_times = [heap_filelines[i]
                    for i in range(1, len(heap_filelines), 3)]
sort_worst_times = [sort_filelines[i]
                    for i in range(2, len(sort_filelines), 3)]

sizes = [int(i.split(':')[1]) for i in merge_worst_times]
merge_worst_times = [float(i.split(':')[-1]) for i in merge_worst_times]
heap_worst_times = [float(i.split(':')[-1]) for i in heap_worst_times]
sort_worst_times = [float(i.split(':')[-1]) for i in sort_worst_times]


plt.plot(sizes, merge_worst_times)
plt.plot(sizes, heap_worst_times)
plt.plot(sizes, sort_worst_times)

plt.legend(["Merge Worst", "Heap Worst", "Inbuilt Sort Worst"])

plt.xlabel(f"Size of input for Sorts")
plt.ylabel(f"Time for sorts")
plt.show()
