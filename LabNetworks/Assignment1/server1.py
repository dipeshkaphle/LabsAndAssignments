import socket
import optparse
import struct
import threading

MAX_QUEUE = 10

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
parser.add_option('-M', '--multi-threaded', action='store_true',
                  dest='multi_threaded', default=False, help='Tells weather multi threading should be done to handle multiple requests')


(options, args) = parser.parse_args()
INTERFACE = options.interface
PORT = options.port
MULTI_THREADED = options.multi_threaded
print("Interface: {}, Port: {}, Multi-threaded?: {}".format(INTERFACE, PORT, MULTI_THREADED))


def pad_to_8chars(c: str) -> str:
    '''
    Given a string of length less than
    or equal to 8, this will pad it to
    8 characters putting 0s in front of it
    '''
    assert(len(c) <= 8)
    return '0'*(8-len(c))+c


def send_int(x: int, conn):
    conn.send(struct.pack("i", socket.htons(x)))


def recv_int(conn) -> int:
    return int.from_bytes(conn.recv(4), byteorder='big')


def data_to_send(msg: str):
    return ''.join((map(lambda x: pad_to_8chars(
        bin(ord(x))[2:])+' ', msg)))


def handle_client(conn, addr):
    print("Connected to ",  addr)
    while True:
        data_size = recv_int(conn)
        if(data_size == 0):
            break
        msg = conn.recv(data_size).decode('utf-8')
        print("Received: {}".format(msg))
        to_be_sent = data_to_send(msg)
        send_int(len(to_be_sent), conn)
        conn.send(to_be_sent.encode('utf-8'))
        print("Sent: {}".format(to_be_sent))


def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.setsockopt(socket.SOL_SOCKET, 25, INTERFACE.encode())
        sock.bind(('0.0.0.0',  PORT))
        sock.listen(MAX_QUEUE)
        while True:
            if not MULTI_THREADED:
                conn, addr = sock.accept()
                handle_client(conn, addr)
                break
            else:
                conn, addr = sock.accept()
                thrd = threading.Thread(
                    target=handle_client, args=[conn, addr])
                thrd.start()
                continue


main()
