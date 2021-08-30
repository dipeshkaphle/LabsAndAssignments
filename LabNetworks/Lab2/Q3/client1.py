import socket
import sys
if(len( sys.argv )>=2):
    port = int(sys.argv[1])

def recv_data(sock , sz:int):
    recvd = 0
    BUF_SIZE=4096
    buffer = ''
    while((sz-recvd)>BUF_SIZE):
        x = sock.recv(BUF_SIZE)
        buffer+= x.decode()
        recvd= len(buffer)
    x = sock.recv(sz-recvd)
    buffer+=x.decode()
    return buffer



with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as sock:
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR | socket.SO_REUSEPORT | socket.SO_LINGER , 1)
    sock.connect(('localhost',3000))
    print(sock.getpeername())
    recvd_already =  set()
    for i in range(5):
        sz = int.from_bytes(sock.recv(4),byteorder='big')
        id = int.from_bytes(sock.recv(4),byteorder='big')
        recvd_already.add(id)
        print(sz,id)
        open( "file{}.txt".format(id),"w" ).write(recv_data(sock,sz))
    sock.close()


    not_recvd =  set(range(0,10)) -  recvd_already
    sock2 =  socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    sock2.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR | socket.SO_REUSEPORT | socket.SO_LINGER , 1)
    sock2.connect(('localhost',4000))

    for id in not_recvd:
        sock2.send(id.to_bytes(4,byteorder='big'))
        sz = int.from_bytes(sock2.recv(4),byteorder='big')
        id = int.from_bytes(sock2.recv(4),byteorder='big')
        recvd_already.add(id)
        print(sz,id)
        open( "file{}.txt".format(id),"w" ).write(recv_data(sock2,sz))
    sock2.send("THANKS".encode())
    sock2.close()
