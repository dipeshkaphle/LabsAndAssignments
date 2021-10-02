from typing import  List
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
        self.fid=int(line[7])
        self.src_addr = line[8]
        self.dest_addr=line[9]
        self.seq_num = int(line[10])
        self.pkt_id = int(line[11])

def line_info(line: List[str])-> LineInfo:
    li = LineInfo(line)
    return li


class NS:
    def readlines(self,filename: str)-> List[str]:
        return open(filename).readlines()

    def __init__(self,filename:str,interval: float=  1.0) -> None:
        self.filename = filename
        self.lines = list(map( line_info, [line.split() for  line in self.readlines(filename)] ))
        self.interval = interval

    def get_lines(self):
        for line in self.lines:
            yield line

    def plr(self,src_nodes: List[int] , dest_nodes:List[int] , file_out: str = "plr_out.txt"):
        fp= open(file_out,"w")
        packet_recvd =0
        packet_sent = 0
        current_time=0
        last_time =0
        for line in self.get_lines():
            current_time = line.time
            if(line.event=="r" and line.to_node in dest_nodes ):
                packet_recvd+=1
            if(line.event=="+" and line.from_node in src_nodes):
                packet_sent+=1
            if(current_time-last_time >= self.interval):
                last_time = current_time
                if(packet_sent>0):
                    fp.write("{} {}\n".format(current_time, ( packet_sent-packet_recvd )/packet_sent))
        fp.close()

    def pdr(self, src_nodes: List[int], dest_nodes: List[int], file_out: str="pdr_out.txt"):
        fp= open(file_out,"w")
        packet_recvd =0
        packet_sent = 0
        current_time=0
        last_time =0
        for line in self.get_lines():
            current_time = line.time
            if(line.event=="r" and line.to_node in dest_nodes ):
                packet_recvd+=1
            if(line.event=="+" and line.from_node in src_nodes):
                packet_sent+=1
            if(current_time-last_time >= self.interval):
                last_time = current_time
                sys.last_value=current_time
                if(packet_sent>0):
                    fp.write("{} {}\n".format(current_time, ( packet_recvd )/packet_sent))
        fp.close()


    def end_to_end_delay(self,src_nodes: List[int], dest_nodes:List[int], file_out: str="e2e_delay.txt"):
        fp= open(file_out,"w")
        current_time=0
        tdelay = 0
        start_time = collections.defaultdict(lambda: 0.0)
        last_time =0
        for line in self.get_lines():
            current_time=line.time
            if(line.event=="r" and line.to_node in dest_nodes):
                tdelay+=current_time-start_time[line.pkt_id]

            if(line.event=="+" and line.from_node in src_nodes):
                start_time[line.pkt_id]= current_time
            if(current_time-last_time >= self.interval):
                last_time=current_time
                fp.write("{} {}\n".format(current_time, tdelay))
        print("Average Delay: {}".format(tdelay/(len(start_time.values()))) )

    def count_sent_packets(self,packet_type: str,src: str, dest: str):
        sent = collections.defaultdict(lambda: set())
        for line in self.get_lines():
            if(line.event=="+"):
                if(line.pkt_type == packet_type and 
                        line.src_addr == src and
                        line.dest_addr==dest and
                        line.from_node==int(float(src))):
                    sent[line.pkt_type].add(line.pkt_id)
        info = dict([(x,len(y)) for x, y in sent.items()  ])
        #  print("Packets sent: {}".format(info))
        print("{} Packets sent for {}->{} : {}".format(packet_type,src,dest,info))
        return info


    def count_recvd_packets(self,packet_type: str,src:str,dest:str):
        recvd = collections.defaultdict(lambda: set())
        for line in self.get_lines():
            if(line.event=="r"):
                if(line.pkt_type == packet_type and 
                        line.src_addr == (src) and
                        line.dest_addr==(dest) and
                        line.to_node==int(float(dest))):
                    recvd[line.pkt_type].add(line.pkt_id)
        info = dict([(x,len(y)) for x, y in recvd.items()  ])
        print("{} Packets received for {}->{} : {}".format(packet_type,src,dest,info))
        return info

def main():
    [ s1,d1,s2,d2] = sys.argv[1:]
    interval = 1.0
    if(len( sys.argv )>=6):
        interval = float(sys.argv[5])
    ns = NS("all.tr",interval)
    a=ns.count_sent_packets('tcp',s1,d1)
    b=ns.count_recvd_packets('tcp',s1,d1)
    c=ns.count_sent_packets('cbr',s2,d2)
    d=ns.count_recvd_packets('cbr',s2,d2)
    print("tcp dropped: {}".format( a['tcp']-b['tcp'] ))
    print("cbr dropped: {}".format( c['cbr']-d['cbr'] ))


main()
