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

using namespace std;

const int BUF_SIZE = 512;

#define HANDLE_SEND_RECV_ERRORS(st)                                            \
  if ((st) == -1) {                                                            \
    perror("Error in send()/recv()");                                          \
    return 254;                                                                \
  } else if ((st) == 0) {                                                      \
    perror("Connection is closed because send/recv returned 0");               \
    return 255;                                                                \
  }

int get_port(const sockaddr_storage *addr) {
  if (addr->ss_family == AF_INET) {
    return ((struct sockaddr_in *)addr)->sin_port;
  } else {
    return ((struct sockaddr_in6 *)addr)->sin6_port;
  }
}

void *get_in_addr(const sockaddr_storage *addr) {
  if (addr->ss_family == AF_INET) {
    return &((struct sockaddr_in *)addr)->sin_addr;
  } else {
    return &((struct sockaddr_in6 *)addr)->sin6_addr;
  }
}

void print_conn_name(int fd, const sockaddr_storage *addr) {
  char buf[1000];
  inet_ntop(addr->ss_family, get_in_addr(addr), buf, sizeof(sockaddr_storage));
  int port = get_port(addr);
  printf("Connected to %s at port %d\n", buf, port);
}

int main(int argc, char **argv) {
  struct addrinfo hints, *result;
  const char *port_no = "3000";
  char buf[BUF_SIZE];
  memset(buf, 0, sizeof(buf));
  // stores status of various syscalls
  int status;

  if (argc >= 2)
    port_no = argv[1];

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  if ((status = getaddrinfo(NULL, port_no, &hints, &result)) != 0) {
    printf("error in getaddrinfo: %s\n", gai_strerror(status));
    return 1;
  }

  /*
   * i'm assuming the first node in ll that we get from getaddrinfo is
   * the right one
   */
  int sock_fd =
      socket(result->ai_family, result->ai_socktype, result->ai_protocol);
  if (sock_fd == -1) {
    printf("unable to open socket\n");
    return 2;
  }
  status = bind(sock_fd, result->ai_addr, result->ai_addrlen);
  if (status == -1) {
    printf("unable to bind to the fd\n");
    return 3;
  }

  status = listen(sock_fd, 2);
  if (status == -1) {
    printf("error in listening\n");
    return 4;
  }

  // first client
  struct sockaddr_storage addr1;
  socklen_t len = sizeof(addr1);
  int conn1 = accept(sock_fd, (struct sockaddr *)&addr1, &len);
  if (conn1 == -1) {
    printf("error in accepting connection 1\n");
    return 5;
  }
  print_conn_name(conn1, &addr1);
  // I only want one character so the buffer size is 1 here
  status = recv(conn1, buf, 1, 0);
  HANDLE_SEND_RECV_ERRORS(status);
  buf[1] = '\0';
  printf("Received : %s\n", buf);
  close(conn1);

  // second client
  struct sockaddr_storage addr2;
  int conn2 = accept(sock_fd, (struct sockaddr *)&addr2, &len);
  if (conn2 == -1) {
    printf("error in accepting connection 2\n");
    return 6;
  }
  // changing the buffer , decrementing the letter received
  print_conn_name(conn2, &addr2);
  buf[0]--;
  status = send(conn2, buf, strlen(buf), 0);
  HANDLE_SEND_RECV_ERRORS(status);
  printf("Sent: %s\n", buf);
  close(conn2);

  freeaddrinfo(result);
}
