#include <arpa/inet.h>
#include <iostream>
#include <math.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

#define HANDLE_SEND_RECV_ERRORS(st)                                            \
  if ((st) == -1) {                                                            \
    perror("Error in send()/recv()");                                          \
    exit(254);                                                                 \
  } else if ((st) == 0) {                                                      \
    perror("Connection is closed because send/recv returned 0");               \
    exit(255);                                                                 \
  }

struct __attribute__((packed)) _data {
  char c;
  uint32_t x;
  double y;
  _data(char _c, uint32_t _x, double _y) : c(_c), x(_x), y(_y) {}
  string str() {
    return string("data( ") + c + " , " + to_string(x) + " , " + to_string(y) +
           " )";
  }
};

_data hton(_data other) { return _data(other.c, htonl(other.x), other.y); }
_data ntoh(_data other) { return _data(other.c, ntohl(other.x), other.y); }

int main(int argc, char **argv) {
  _data buf('c', 12345, 123.45);
  int yes = 1;
  struct addrinfo hints, *res;
  int status;
  const char *port_no = "3000";
  int fd;
  struct sockaddr_storage *addr;
  socklen_t len = sizeof(
      std::remove_reference_t<decltype(*std::declval<decltype(addr)>())>);

  printf("HI\n");
  // 2nd argument is port number
  if (argc >= 2)
    port_no = argv[1];

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  if ((status = getaddrinfo(NULL, port_no, &hints, &res)) != 0) {
    printf("error in getaddrinfo: %s\n", gai_strerror(status));
    return 1;
  }

  struct addrinfo *result = res;

  for (; result != nullptr; result = result->ai_next) {
    fd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (fd == -1) {
      perror("socket()");
      continue;
    }
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
      perror("setsockopt() failed: ");
      exit(10);
    }
    status = connect(fd, res->ai_addr, res->ai_addrlen);
    if (status == -1) {
      perror("connect()");
      continue;
    }
    break;
  }

  freeaddrinfo(res);
  if (result == nullptr) {
    perror("connect() failed");
    exit(20);
  }

  // send
  buf = hton(buf);
  status = send(fd, &buf, sizeof(buf), 0);
  HANDLE_SEND_RECV_ERRORS(status);
  buf = ntoh(buf);
  printf("Sent %s successfully\n", buf.str().c_str());
  fflush(stdout);
  close(fd);
  return 0;
}
