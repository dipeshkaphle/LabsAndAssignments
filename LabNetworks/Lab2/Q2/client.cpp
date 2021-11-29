#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <optional>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;
void HANDLE_SEND_RECV_ERRORS(int st) {
  if (st == -1) {
    perror("Error in send()/recv()");
    exit(254);
  } else if ((st) == 0) {
    perror("Connection is closed because send/recv returned 0");
    exit(255);
  }
}

void die_with_error(const char *message, int err_code = 1) {
  perror(message);
  exit(err_code);
}

struct addrinfo *addr_setup(const char *address, const char *port_no) {
  struct addrinfo hints, *result;

  memset(&hints, 0, sizeof(hints));
  hints.ai_addr = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  int status = getaddrinfo(address, port_no, &hints, &result);
  if (status != 0)
    die_with_error("getaddrinfo()");
  cout << "OK\n";
  return result;
}

int setup_client_socket(struct addrinfo *result) {
  int yes = 1;
  int sock_fd =
      socket(result->ai_family, result->ai_socktype, result->ai_protocol);
  if (sock_fd < 0)
    die_with_error("socket()");
  if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT | SO_LINGER,
                 &yes, sizeof(yes)) < 0)

    die_with_error("setsockopt");

  if (connect(sock_fd, result->ai_addr, result->ai_addrlen) < 0)
    die_with_error("bind()");
  return sock_fd;
}

void send_message(int conn, const string &message) {
  int sz = message.size();
  int htonl_sz = htonl(sz);

  int st = send(conn, &htonl_sz, sizeof(int), 0);
  HANDLE_SEND_RECV_ERRORS(st);

  st = send(conn, message.c_str(), sz, 0);
  HANDLE_SEND_RECV_ERRORS(st);
}

string receive_message(int conn) {
  int sz;
  int status = recv(conn, &sz, 4, 0);
  HANDLE_SEND_RECV_ERRORS(status);
  sz = ntohl(sz);

  char *buf = new char[sz + 1];
  status = recv(conn, buf, sz, 0);
  HANDLE_SEND_RECV_ERRORS(status);
  buf[status] = '\0';

  string buffer(buf);
  cout << "Received : " << buffer << endl;
  delete[] buf;
  return buffer;
}

void handle_connection(int conn) {
  while (true) {
    string message;
    cout << "Enter message to send: ";
    cin >> message;
    cout.flush();

    send_message(conn, message);
    cout << "Sent : " << message << endl;

    string buffer = receive_message(conn);

    if (message == "BYEBYE" && buffer == "BYEBYE") {
      break;
    }
  }
}

int main() {
  struct addrinfo *result = addr_setup(NULL, "5000");
  int sock_fd = setup_client_socket(result);
  freeaddrinfo(result);
  handle_connection(sock_fd);
  close(sock_fd);
  return 0;
}
