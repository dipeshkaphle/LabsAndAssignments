from matplotlib.markers import MarkerStyle
import matplotlib.pyplot as plt
import math


def f(n, m):
    return n*m


bellman = open('./Bellman.txt').readlines()

n_values = [int(line.split(':')[0]) for line in bellman]
m_values = [int(line.split(':')[1]) for line in bellman]
time_values_bellman = [float(line.split(':')[2]) for line in bellman]

constants_dijkstra = list(map(lambda x: x[0]/f(x[1], x[2]),
                              zip(time_values_bellman, n_values, m_values)))
#
constant_dijkstra_max = max(constants_dijkstra)
constant_dijkstra_min = min(constants_dijkstra)
#  constant_prims = max(constants_prims)
plt.plot(n_values, time_values_bellman, marker='*')
plt.plot(n_values, list(
    map(lambda x: constant_dijkstra_max*f(x[0], x[1]), list(zip(n_values, m_values)))), marker='+')
plt.plot(n_values, list(
    map(lambda x: constant_dijkstra_min*f(x[0], x[1]),  list(zip(n_values, m_values)))), marker='+')


plt.legend(["ActualTime",
            f"Upper bound c={constant_dijkstra_max}*V*E ", f"Lower Bound c={constant_dijkstra_min}*V*E"])
plt.show()
