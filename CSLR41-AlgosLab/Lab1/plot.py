from matplotlib import colors
import matplotlib.pyplot as plt

fp = open('out', 'r')
lines = list(map(lambda x: [float(y)
                            for y in x.split(':')[1:]], fp.readlines()))
lines = list(map(lambda x: [x[0], x[1]*100], lines))
for line in lines:
    print(line)


# For found

ns = [lines[x][0] for x in range(0, len(lines), 2)]
times = [lines[x][1] for x in range(0, len(lines), 2)]

ns2 = [2*lines[x][0] for x in range(0, len(lines), 2)]
times2 = [2*lines[x][1] for x in range(0, len(lines), 2)]
print(ns)
print(times)
plt.plot(ns, times)
plt.plot(ns2, times2)
plt.xlabel("number of items")
plt.ylabel("Time*100")
plt.legend(["One", "Two"])

plt.show()


# For not found

ns = [lines[x][0] for x in range(1, len(lines), 2)]
times = [lines[x][1] for x in range(1, len(lines), 2)]


print(ns)
print(times)
plt.plot(ns, times)
plt.xlabel("number of items")
plt.ylabel("Time*100")

plt.show()
