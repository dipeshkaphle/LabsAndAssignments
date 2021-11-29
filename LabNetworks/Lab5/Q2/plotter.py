import sys
import matplotlib.pyplot as plt
import collections

title = sys.argv[1]
file1 = sys.argv[2]
image_name = sys.argv[3]

d = collections.defaultdict(lambda: list())
file1_lines = open(file1).readlines()
x1 = [float(line.strip().split()[0]) for line in file1_lines]
y1 = [float(line.strip().split()[1]) for line in file1_lines]
plt.plot(x1, y1)
plt.title(title)
plt.savefig(image_name)
