import sys
import subprocess

filename = sys.argv[1]

p1 = subprocess.Popen(['ns',filename, *sys.argv[2:]])
p1.wait()

print("p1 done")
p2 = subprocess.Popen(['python3','ns.py', *sys.argv[2:]])
p2.wait()
print("p2 done")
