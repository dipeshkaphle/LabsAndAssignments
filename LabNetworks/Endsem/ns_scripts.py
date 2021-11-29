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
            map(line_info, filter(lambda x: True, [line.split() for line in self.readlines(filename)])))
        #  self.lines = list(
        #  map(line_info, filter(lambda x: x[2] not in ['link-up', 'link-down'], [line.split() for line in self.readlines(filename)])))
        self.interval = interval

    def get_lines(self):
        for line in self.lines:
            yield line

    def plr(self, src_nodes: List[int], dest_nodes: List[int], file_out: str = "packet_drop_ratio_out.txt"):
        fp = open(file_out, "w")
        packet_dropped = 0
        packet_sent = 0
        current_time = 0
        last_time = 0
        for line in self.get_lines():
            current_time = line.time
            if(line.event == "d"):
                packet_dropped += 1
            if(line.event == "+" and line.from_node in src_nodes):
                packet_sent += 1
            if(current_time-last_time >= self.interval):
                last_time += self.interval
                if(packet_sent > 0):
                    fp.write("{} {}\n".format(last_time,
                             (packet_dropped)/packet_sent))
        fp.close()

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
                last_time += self.interval
                if(packet_sent > 0):
                    fp.write("{} {}\n".format(
                        last_time, (packet_recvd)/packet_sent))
        fp.close()

    def end_to_end_delay(self, src_nodes: List[int], dest_nodes: List[int], file_out: str = "e2e_delay.txt"):
        fp = open(file_out, "w")
        current_time = 0
        tdelay = 0
        delay = 0
        start_time = collections.defaultdict(lambda: 0.0)
        last_time = 0
        for line in self.get_lines():
            current_time = line.time
            if(line.event == "r" and line.to_node in dest_nodes):
                tdelay += current_time-start_time[line.pkt_id]
                delay += current_time-start_time[line.pkt_id]

            if(line.event == "+" and line.from_node in src_nodes):
                start_time[line.pkt_id] = current_time
            if(current_time-last_time >= self.interval):
                last_time += self.interval
                fp.write("{} {}\n".format(last_time, delay))
                #  delay=0
        fp.write("{} {}\n".format(current_time, delay))
        print("Average Delay: {}".format(tdelay/(len(start_time.values()))))

    def count_sent_packets(self, packet_type: str, src: str, dest: str):
        sent = collections.defaultdict(lambda: set())
        for line in self.get_lines():
            if(line.event == "+"):
                if(line.pkt_type == packet_type and
                        line.src_addr == src and
                        line.dest_addr == dest and
                        line.from_node == int(float(src))):
                    sent[line.pkt_type].add(line.pkt_id)
        info = dict([(x, len(y)) for x, y in sent.items()])
        #  print("Packets sent: {}".format(info))
        print("{} Packets sent for {}->{} : {}".format(packet_type, src, dest, info))
        return info

    def count_recvd_packets(self, packet_type: str, src: str, dest: str):
        recvd = collections.defaultdict(lambda: set())
        for line in self.get_lines():
            if(line.event == "r"):
                if(line.pkt_type == packet_type and
                        line.src_addr == (src) and
                        line.dest_addr == (dest) and
                        line.to_node == int(float(dest))):
                    recvd[line.pkt_type].add(line.pkt_id)
        info = dict([(x, len(y)) for x, y in recvd.items()])
        print("{} Packets received for {}->{} : {}".format(packet_type, src, dest, info))
        return info

    def throughput(self, dest: List[int], out_file: str = "throughput_out.txt"):
        fp = open(out_file, "w")
        recv_size = 0
        last_time = 0
        for line in self.get_lines():
            if(line.event == "r" and line.to_node in dest):
                recv_size += line.pkt_size
            if(line.time-last_time >= self.interval):
                last_time += self.interval
                fp.write("{} {}\n".format(
                    last_time, (8*recv_size)/(10**6 * last_time)))
        fp.close()

    def bandwith_util(self,  dest: List[int], bandwith: float,  out_file: str = "bandwithutil_out.txt"):
        '''
        bandwith will be in Mb per second
        '''
        fp = open(out_file, "w")
        recv_size = 0
        last_time = 0
        for line in self.lines:
            if(line.event == "r" and line.to_node in dest):
                recv_size += line.pkt_size
            if(line.time-last_time >= self.interval):
                last_time += self.interval
                fp.write("{} {}\n".format(
                    last_time, (8*recv_size)/(10**6 * last_time * bandwith)))
        fp.close()

    def control_overhead_normal(self, out_file: str = "control_overhead_normal.txt"):
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

    def control_overhead_dv_or_ls(self, out_file: str = "control_overhead_dv_or_ls"):
        fp = open(out_file, "w")
        total_packets = 0
        control_packets = 0
        last_time = 0
        for line in self.get_lines():
            if line.event == '+':
                total_packets += 1
                if line.pkt_type == "rtProtoDV" or line.pkt_type == "rtProtoLS":
                    control_packets += 1
                if line.time - last_time >= self.interval:
                    last_time += self.interval
                    fp.write("{} {}\n".format(
                        last_time, control_packets/total_packets))
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
    interval = 1.0
    ns = NS("all.tr", interval)
    ns.pdr([0], [7, 9])
    ns.end_to_end_delay([0], [7, 9])
    ns.throughput([7, 9])


main()
