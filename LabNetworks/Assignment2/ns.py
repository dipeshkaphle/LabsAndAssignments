from typing import List
import collections
import sys


class LineInfo:
    def __init__(self, line: List[str]):
        self.event = line[0]
        self.time = float(line[1])
        self.from_node = int(line[2])
        self.to_node = int(line[3])
        self.pkt_type = line[4]
        self.pkt_size = int(line[5])
        self.flags = line[6]
        self.fid = int(line[7])
        self.src_addr = line[8]
        self.dest_addr = line[9]
        self.seq_num = int(line[10])
        self.pkt_id = int(line[11])


def line_info(line: List[str]) -> LineInfo:
    li = LineInfo(line)
    return li


class NS:
    def readlines(self, filename: str) -> List[str]:
        return open(filename).readlines()

    def __init__(self, filename: str, interval: float = 1.0) -> None:
        self.filename = filename
        self.lines = list(
            map(line_info, [line.split() for line in self.readlines(filename)]))
        self.interval = interval

    def get_lines(self):
        for line in self.lines:
            yield line

    def throughput(self, dest: int, out_file: str = "throughput_out.txt"):
        fp = open(out_file, "w")
        recv_size = 0
        last_time = 0
        avg = 0
        leng = 0
        for line in self.get_lines():
            if(line.event == "r" and line.to_node == dest):
                recv_size += line.pkt_size
            if(line.time-last_time >= self.interval):
                last_time += self.interval
                fp.write("{} {}\n".format(
                    last_time, (8*recv_size)/(10**6 * self.interval)))
                avg += (8*recv_size)/(10**6 * self.interval)
                leng += 1
                recv_size = 0
        last_time += self.interval
        fp.write("{} {}\n".format(
            last_time, (8*recv_size)/(10**6 * self.interval)))
        avg += (8*recv_size)/(10**6 * self.interval)
        leng += 1
        print(avg/leng)
        fp.close()


def main():
    interval = 1.0
    if(len(sys.argv) >= 3):
        interval = float(sys.argv[2])
    ns = NS("out.tr", interval)
    ns.throughput(1)


main()
