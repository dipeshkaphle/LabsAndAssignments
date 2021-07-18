from math import log2
import matplotlib.pyplot as plt

worstcase = [line.split(':')
             for line in open('WorstCase.txt', 'r').readlines()]
randomcase = [line.split(':')
              for line in open('RandomCase.txt', 'r').readlines()]
best_case = [line.split(':')
             for line in open('BestCase.txt', 'r').readlines()]

sizes = [int(i[0]) for i in worstcase][1:]

worstcaseTimes = [float(i[1]) for i in worstcase][1:]
randomcaseTimes = [float(i[1]) for i in randomcase][1:]
bestcaseTimes = [float(i[1]) for i in best_case][1:]


lognValues = list(map(lambda x: log2(x), sizes))
logConstants = list(
    map(lambda x: x[0]/x[1], list(zip(worstcaseTimes, lognValues))))
logUpperBoundConstant = max(logConstants)
logLowerBoundConstant = min(logConstants)
UpperboundingLogCurve = [logUpperBoundConstant * i for i in lognValues]
LowerboundingLogCurve = [logLowerBoundConstant * i for i in lognValues]

print(
    f'''The upper bound constant for binary search is {logUpperBoundConstant}.
    That means, our binary search was taking at max {logUpperBoundConstant}*log(sizeOfRecord) time''')

print(
    f'''The lower bound constant for binary search is {logLowerBoundConstant}.
    That means, our binary search was taking at min{logLowerBoundConstant}*log(sizeOfRecord) time''')

plt.plot(sizes, worstcaseTimes)
plt.plot(sizes, randomcaseTimes)
plt.plot(sizes, bestcaseTimes)
plt.plot(sizes, UpperboundingLogCurve)
plt.plot(sizes, LowerboundingLogCurve)

plt.legend(["Worst Case", "Random Case", "Best Case",
            f"BSearch upper bounding curve with c={logUpperBoundConstant}",
            f"BSearch lower bounding curve with c={logLowerBoundConstant}"])
plt.xlabel("Size of input")
plt.ylabel("Time")
plt.show()
