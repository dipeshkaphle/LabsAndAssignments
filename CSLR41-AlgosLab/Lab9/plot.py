from matplotlib.markers import MarkerStyle
import matplotlib.pyplot as plt
import math


def f(x):
    return x*x*math.log2(x)


krus = open('./kruskal.txt').readlines()
prims = open('./prim.txt').readlines()

n_values = [int(line.split(':')[0]) for line in krus]
time_values_krus = [float(line.split(':')[1]) for line in krus]
time_values_prims = [float(line.split(':')[1]) for line in prims]

#  for i, j in zip(n_values, time_values):
#      print(i, j)

constants_krus = map(lambda x: x[0]/f(x[1]), zip(time_values_krus, n_values))
constants_prims = map(lambda x: x[0]/f(x[1]), zip(time_values_prims, n_values))
#
constant_krus = max(constants_krus)
constant_prims = max(constants_prims)


plt.plot(n_values, time_values_krus, marker='+')
plt.plot(n_values, time_values_prims, marker='*')
plt.plot(n_values, list(map(lambda x: constant_krus*f(x), n_values)), marker='+')
plt.plot(n_values, list(map(lambda x: constant_prims*f(x), n_values)), marker='*')
plt.xlabel("V values")
plt.ylabel("Times")

#  plt.legend(["Kruskal", "Prims"])
plt.legend(["Kruskal", "Prims",
            f"c={constant_krus}*Elog(V) kruskal", f"c={constant_prims}*Elog(V) prims"])
plt.show()
