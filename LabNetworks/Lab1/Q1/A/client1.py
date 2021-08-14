import socket
import sys
port = 3000
if(len( sys.argv )>=2):
    port = int(sys.argv[1])

with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as sock:
    sock.connect(('localhost',port))
    print(sock.getpeername())
    sock.send("c".encode())
    sock.close()

