#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define HANDLE_SEND_RECV_ERRORS(st)                                            \
  if ((st) == -1) {                                                            \
    perror("Error in send()/recv()");                                          \
    exit(254);                                                                 \
  } else if ((st) == 0) {                                                      \
    perror("Connection is closed because send/recv returned 0");               \
    exit(255);                                                                 \
  }

int main(int argc, char **argv) {
  double buf = 1.5;
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

  // 3rd argument is the letter to send
  if (argc >= 3)
    buf = atof(argv[2]);

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
  status = send(fd, &buf, sizeof(buf), 0);
  HANDLE_SEND_RECV_ERRORS(status);
  printf("Sent %f successfully\n", buf);
  fflush(stdout);
  close(fd);
  return 0;
}
