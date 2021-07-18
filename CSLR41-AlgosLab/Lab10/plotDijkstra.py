from matplotlib.markers import MarkerStyle
import matplotlib.pyplot as plt
import math


def f(n):
    return n*n


bellman = open('./Bellman.txt').readlines()
dijkstra = open('./Dijkstra.txt').readlines()

n_values = [int(line.split(':')[0]) for line in bellman][2:]
time_values_bellman = [float(line.split(':')[2]) for line in bellman]
time_values_dijkstra = [float(line.split(':')[2]) for line in dijkstra][2:]

constants_dijkstra = list(map(lambda x: x[0]/f(x[1]),
                              zip(time_values_dijkstra, n_values)))
#
constant_dijkstra_max = max(constants_dijkstra)
constant_dijkstra_min = min(constants_dijkstra)
#  constant_prims = max(constants_prims)
plt.plot(n_values, time_values_dijkstra, marker='*')
plt.plot(n_values, list(
    map(lambda x: constant_dijkstra_max*f(x), n_values)), marker='+')
plt.plot(n_values, list(
    map(lambda x: constant_dijkstra_min*f(x), n_values)), marker='+')


plt.legend(["ActualTime",
            f"Upper bound c={constant_dijkstra_max}*V^2 ", f"Lower Bound c={constant_dijkstra_min}*V^2"])
plt.show()
