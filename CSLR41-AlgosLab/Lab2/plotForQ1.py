import matplotlib.pyplot as plt

bestcase = [line.split(':')
            for line in open('BestCaseQ1.txt', 'r').readlines()]
worstcase = [line.split(':')
             for line in open('WorstCaseQ1.txt', 'r').readlines()]
randomcase = [line.split(':')
              for line in open('RandomCaseQ1.txt', 'r').readlines()]

sizes = [int(i[0]) for i in bestcase]

bestcaseTimes = [float(i[1])*100000 for i in bestcase]
worstcaseTimes = [float(i[1])*100000 for i in worstcase]
randomcaseTimes = [float(i[1])*100000 for i in randomcase]


plt.scatter(sizes, bestcaseTimes)
plt.scatter(sizes, worstcaseTimes)
plt.scatter(sizes, randomcaseTimes)

plt.legend(["Best case", "Worst Case", "Random Case"])
plt.xlabel("Size of input")
plt.ylabel("Time*100000")
plt.show()
