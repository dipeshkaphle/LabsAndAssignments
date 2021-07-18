from os import times
from matplotlib.markers import MarkerStyle
import matplotlib.pyplot as plt

file_content = open('./output.txt').readlines()

n_values = [int(line.split(':')[0]) for line in file_content]
time_values = [float(line.split(':')[2]) for line in file_content]

#  for i, j in zip(n_values, time_values):
#      print(i, j)

constants = map(lambda x: x[0]/x[1], zip(time_values, n_values))

constant = max(constants)


plt.plot(n_values, time_values, marker='+')
plt.plot(n_values, list(map(lambda x: constant*x, n_values)), marker='*')
plt.xlabel("N values")
plt.ylabel("Times")

plt.legend(["Actual time curve", f"c={constant}*N"])
plt.show()
