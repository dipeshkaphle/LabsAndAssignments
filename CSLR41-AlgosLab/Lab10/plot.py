from matplotlib.markers import MarkerStyle
import matplotlib.pyplot as plt
import math


def f(x):
    return x*x*math.log2(x)


bellman = open('./Bellman.txt').readlines()
dijkstra = open('./Dijkstra.txt').readlines()

n_values = [int(line.split(':')[0]) for line in bellman]
time_values_bellman = [float(line.split(':')[2]) for line in bellman]
time_values_dijkstra = [float(line.split(':')[2]) for line in dijkstra]

#  for i, j in zip(n_values, time_values):
#      print(i, j)

#  constants_krus = map(lambda x: x[0]/f(x[1]),
#                       zip(time_values_bellman, n_values))
#  constants_prims = map(lambda x: x[0]/f(x[1]),
#                        zip(time_values_dijkstra, n_values))
#
#  constant_krus = max(constants_krus)
#  constant_prims = max(constants_prims)


plt.plot(n_values, time_values_bellman, marker='+')
plt.plot(n_values, time_values_dijkstra, marker='*')
#  plt.plot(n_values, list(map(lambda x: constant_krus*f(x), n_values)), marker='+')
#  plt.plot(n_values, list(map(lambda x: constant_prims*f(x), n_values)), marker='*')
plt.xlabel("V values")
plt.ylabel("Times")
plt.legend(["Bellman", "Dijkstra"])

#  plt.legend(["Kruskal", "Prims"])
#  plt.legend(["Kruskal", "Prims",
#              f"c={constant_krus}*Elog(V) kruskal", f"c={constant_prims}*Elog(V) prims"])
plt.show()
