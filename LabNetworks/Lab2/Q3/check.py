import socket
sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

sock.connect(('127.0.1.1',3000))

input()
