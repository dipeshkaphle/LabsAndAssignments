import sys
import subprocess
import os

filename = sys.argv[1]
type_of_tcp = sys.argv[2]
traffic_percent = sys.argv[3]
interval = 1
if(len(sys.argv) >= 5):
    interval = float(sys.argv[4])


p1 = subprocess.Popen(['ns', filename, *sys.argv[2:]], stdout=subprocess.PIPE)
stdout = p1.communicate()[0]
#  while
p1.wait()
src_dest_filename = "src_dest.txt"
outfile = open(src_dest_filename, "w")

for line in stdout.strip().decode().splitlines():
    outfile.write("{}\n".format(line.strip()))

outfile.close()
print("p1 done")

p2 = subprocess.Popen(['python3', 'ns.py', src_dest_filename, str(interval)])
p2.wait()
os.remove(src_dest_filename)
print("p2 done")
