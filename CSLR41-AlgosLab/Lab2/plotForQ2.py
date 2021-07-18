import matplotlib.pyplot as plt

ssearch = [line.split(':')
           for line in open('SSearch.txt', 'r').readlines()]
bsearch = [line.split(':')
           for line in open('BSearch.txt', 'r').readlines()]

indices = [int(i[0]) for i in ssearch]

ssearch_times = [float(i[1])*100000 for i in ssearch]
bsearch_times = [float(i[1])*100000 for i in bsearch]


plt.plot(indices, ssearch_times)
plt.plot(indices, bsearch_times)

plt.legend(["SSearch ", "BSearch "])
plt.xlabel("Search index")
plt.ylabel("Time*100000")
plt.show()
