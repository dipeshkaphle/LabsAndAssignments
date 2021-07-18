import matplotlib.pyplot as plt
import sys

opt = int(sys.argv[1])
max_wt_type = ""
if (opt == 0):
    max_wt_type = "n"
elif(opt == 1):
    max_wt_type = "n^2"
elif(opt == 2):
    max_wt_type = "log(n)"
else:
    max_wt_type = "n* (rand()%n)"


filelines = open(f"./ZeroOne.txt").readlines()
filelines1 = open(f"./Fractional.txt").readlines()

ns = [int(i.split(':')[0]) for i in filelines]
max_wts = [int(i.split(':')[1]) for i in filelines]
times = [float(i.split(':')[2]) for i in filelines]
ns1 = [int(i.split(':')[0]) for i in filelines1]
max_wts1 = [int(i.split(':')[1]) for i in filelines1]
times1 = [float(i.split(':')[2]) for i in filelines1]
#  n_into_ws = [i[0]*i[1] for i in zip(ns, max_wts)]

plt.plot(ns, times, marker='+')
plt.plot(ns, times1, marker='+')

plt.legend([f"Zero One with MAX_WT={max_wt_type}", "Fractional"])
plt.xlabel("Size")
plt.ylabel("times")
plt.show()
