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

    def pdr(self, src_nodes: List[int], dest_nodes: List[int], file_out: str = "pdr_out.txt"):
        fp = open(file_out, "w")
        packet_recvd = 0
        packet_sent = 0
        current_time = 0
        last_time = 0
        for line in self.get_lines():
            current_time = line.time
            if(line.event == "r" and line.to_node in dest_nodes):
                packet_recvd += 1
            if(line.event == "+" and line.from_node in src_nodes):
                packet_sent += 1
            if(current_time-last_time >= self.interval):
                last_time = current_time
                if(packet_sent > 0):
                    fp.write("{} {}\n".format(
                        current_time, (packet_recvd)/packet_sent))
        fp.close()

    def control_overhead(self, out_file: str = "control_overhead.txt"):
        fp = open(out_file, "w")
        control_packet = 0
        all_packets = 0
        last_time = 0
        for line in self.get_lines():
            if(line.event == "+"):
                all_packets += 1
                if(line.pkt_type == "ack"):
                    control_packet += 1
            if(line.time-last_time >= self.interval):
                last_time = line.time
                fp.write("{} {}\n".format(
                    line.time, control_packet/all_packets))
        fp.close()

    def congestion_control(self, out_file: str = "congestion_control.txt"):
        fp = open(out_file, "w")
        last_time = 0
        congestions = 0
        acks = collections.defaultdict(lambda: 0)
        for line in self.get_lines():
            if(line.event == "+" and line.pkt_type == "ack"):
                s = str(line.to_node)+str(line.from_node) + str(line.seq_num)
                acks[s] += 1
                if((acks[s] % 3) == 0):
                    congestions += 1
            if(line.time-last_time >= self.interval):
                last_time = line.time
                fp.write("{} {}\n".format(line.time, float(congestions)))
        fp.close()


def main():
    infile = sys.argv[1]
    srcs = []
    dests = []
    for line in open(infile).readlines():
        srcs.append(int(line.split()[0]))
        dests.append(int(line.split()[1]))
    interval = 1.0
    if(len(sys.argv) >= 3):
        interval = float(sys.argv[2])
    ns = NS("all.tr", interval)
    ns.pdr(srcs, dests)
    ns.control_overhead()
    ns.congestion_control()


main()
