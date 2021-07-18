import matplotlib.pyplot as plt
from math import log2

arr = []
for i in range(100, 1000000000, 100):
    arr.append(i)

nlogn = [n*log2(n) for n in arr]

plt.plot(arr, nlogn)
plt.show()
