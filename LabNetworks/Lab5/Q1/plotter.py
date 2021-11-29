import sys
import matplotlib.pyplot as plt
import collections

prot = sys.argv[1]
file1 = sys.argv[2]
file2 = sys.argv[3]
image_name = sys.argv[4]

d = collections.defaultdict(lambda: list())
file1_lines = open(file1).readlines()
file2_lines = open(file2).readlines()
x1 = [float(line.strip().split()[0]) for line in file1_lines]
x2 = [float(line.strip().split()[0]) for line in file2_lines]
y1 = [float(line.strip().split()[1]) for line in file1_lines]
y2 = [float(line.strip().split()[1]) for line in file2_lines]
plt.plot(x1, y1, label=file1)
plt.plot(x2, y2, label=file2)
plt.title(prot)
plt.legend()
plt.savefig(image_name)
