import matplotlib.pyplot as plt
import math

ssearch = [line.split(':')
           for line in open('WorstCaseSSearch.txt', 'r').readlines()]
bsearch = [line.split(':')
           for line in open('WorstCaseBSearch.txt', 'r').readlines()]

sizes = [int(i[0]) for i in ssearch]

ssearch_times = [float(i[1]) for i in ssearch]
bsearch_times = [float(i[1]) for i in bsearch]

linearWith_c_equal_to_1 = [1*i for i in sizes]

logWith_c_equal_to_1 = [math.log2(i) for i in sizes]

# I'll find the ratio of our times with a linear slop for ssearch
# The max of that ratio will bound our curve
linearConstants = list(
    map(lambda x: x[0]/x[1], list(zip(ssearch_times, linearWith_c_equal_to_1))))
linearBoundConstant = max(linearConstants)
boundingLinearCurve = [linearBoundConstant *
                       i for i in linearWith_c_equal_to_1]

logConstants = list(
    map(lambda x: x[0]/x[1], list(zip(bsearch_times, logWith_c_equal_to_1))))
logBoundConstant = max(logConstants)
boundingLogCurve = [logBoundConstant * i for i in logWith_c_equal_to_1]

# logWith_c_equal_to_2 = [2*math.log2(i) for i in sizes]
# logWith_c_equal_to_3 = [3*math.log2(i) for i in sizes]
print(
    f'''The bound constant for linear search is {linearBoundConstant}. 
    That means, our linear search was taking at max {linearBoundConstant}*sizeOfRecord time''')
print(
    f'''The bound constant for binary search is {logBoundConstant}. 
    That means, our linear search was taking at max {logBoundConstant}*log(sizeOfRecord) time''')

plt.plot(sizes, ssearch_times)
plt.plot(sizes, bsearch_times)
plt.plot(sizes, boundingLinearCurve)
plt.plot(sizes, boundingLogCurve)

plt.legend(["SSearch ", "BSearch ",
            f"SSearch bounding curve with c={linearBoundConstant}",
            f"BSearch bounding curve with c={logBoundConstant}"])
plt.xlabel("Search index")
plt.ylabel("Time")
plt.show()
