import socket,sys

def main():
    start =  1
    end = 1026

    addr = 'localhost'
    if len(sys.argv)>1 :
        addr = sys.argv[1]

    for port in range(start,end+1):
        try:
            sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
            sock.settimeout(1)
            res = sock.connect_ex((addr,port))
            if(res==0):
                print("{}:{} (tcp) is open".format(addr,port))
            sock.close()
        except:
            continue
main()
