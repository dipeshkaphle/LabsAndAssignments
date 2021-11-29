import socket
import optparse
import struct


'''
This is the part where I am doing
command line argument parsing, so that
the server is more configurable

- The default port is 3000
- The default interface is lo(localhost)
- All these can be overriden through command line args
- To override port number, pass --port <port_no>
- To override interface, pass --interface <interface_name>
'''
parser = optparse.OptionParser()
parser.add_option('-p', '--port', dest='port', default=3000,
                  type="int", help='Port to run the server on')
parser.add_option('-I', '--interface', dest='interface',
                  default='lo', help='Network interface to run the server on')
parser.add_option('-a', '--use-ip-addr', dest='ip_addr', default='',
                  help='Connect through IP instead of using the interface')


(options, args) = parser.parse_args()
INTERFACE = options.interface
PORT = options.port
IP_ADDR = options.ip_addr
print("Interface: {}, Port: {}".format(INTERFACE, PORT))


def send_int(x: int, conn):
    conn.send(struct.pack("i", socket.htons(x)))


def recv_int(conn) -> int:
    return int.from_bytes(conn.recv(4), byteorder='big')


def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        if(IP_ADDR == ''):
            sock.setsockopt(socket.SOL_SOCKET, 25, INTERFACE.encode())
            sock.connect(('0.0.0.0',  PORT))
        else:
            sock.connect((IP_ADDR, PORT))

        print(sock.getpeername())
        while True:
            msg = input()
            if(msg == ""):
                sock.close()
                break
            msg = msg.strip()
            send_int(len(msg), sock)
            sock.send(msg.encode('utf-8'))
            print("Sent: ", msg)
            msg_sz = recv_int(sock)
            recvd_msg = sock.recv(msg_sz).decode('utf-8')
            print("Received: ", recvd_msg)


main()
