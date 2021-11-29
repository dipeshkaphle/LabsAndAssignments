#include <algorithm>
#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <numeric>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

#define BUF_SIZE 32

#define HANDLE_SEND_RECV_ERRORS(st)                                            \
  if ((st) == -1) {                                                            \
    perror("Error in send()/recv()");                                          \
    exit(254);                                                                 \
  } else if ((st) == 0) {                                                      \
    perror("Connection is closed because send/recv returned 0");               \
    exit(255);                                                                 \
  }

void die_with_error(const char *message, int err_code = 1) {
  perror(message);
  exit(err_code);
}

void ntoh_arr(int *arr, int n) {
  transform(arr, arr + n, arr, [](int x) { return (int)ntohl(x); });
}
void hton_arr(int *arr, int n) {
  transform(arr, arr + n, arr, [](int x) { return (int)htonl(x); });
}

void populate(int *buf, int *buf2, bool make_wrong = false) {
  int num = 2;
  for (int i = 1; i * sizeof(int) <= BUF_SIZE; i++) {
    buf[i - 1] = num;
    num += 2;
  }
  for (int i = 1; i * sizeof(int) <= BUF_SIZE; i++) {
    buf2[i - 1] = num;
    num += 2;
  }
  if (make_wrong)
    buf2[0] = 1;
}

void print_nums(int *buf, int *buf2) {
  printf("Buf1: ");
  for (int i = 1; (i * sizeof(int)) <= BUF_SIZE; i++) {
    printf("%d ", buf[i - 1]);
  }
  printf("\n");
  printf("Buf2: ");
  for (int i = 1; i * sizeof(int) <= BUF_SIZE; i++) {
    printf("%d ", buf2[i - 1]);
  }
  printf("\n");
}

int main(int argc, char **argv) {
  char buf[BUF_SIZE];
  char buf2[BUF_SIZE];
  bool make_wrong = false;
  if (argc >= 3) {
    if (string(argv[2]) == string("wrong"))
      make_wrong = true;
  }
  populate((int *)buf, (int *)buf2, make_wrong);
  print_nums((int *)buf, (int *)buf2);
  int sz = BUF_SIZE / sizeof(int);
  hton_arr((int *)buf, sz);
  hton_arr((int *)buf2, sz);

  struct addrinfo hints, *res;
  struct sockaddr_storage server_addr;
  socklen_t len = sizeof(server_addr);
  int status;
  const char *port = "3000";
  int fd, num_bytes;

  if (argc >= 2)
    port = argv[1];

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE;

  status = getaddrinfo(NULL, port, &hints, &res);
  if (status == -1)
    die_with_error("getaddrinfo() failed");

  struct addrinfo *result = res;
  for (; result != nullptr; result = result->ai_next) {
    fd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (fd == -1)
      continue;

    // https://stackoverflow.com/questions/13547721/udp-socket-set-timeout
    struct timeval t;
    t.tv_sec = 5;
    t.tv_usec = 0;
    if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &t, sizeof(t)) == -1)
      die_with_error("setsockopt() failed");
    break;
  }
  if (result == NULL)
    die_with_error("binding failed");

  // first buffer sent
  int sent_bytes =
      sendto(fd, buf, BUF_SIZE, 0, result->ai_addr, result->ai_addrlen);
  HANDLE_SEND_RECV_ERRORS(sent_bytes);

  // second buffer sent
  sent_bytes =
      sendto(fd, buf2, BUF_SIZE, 0, result->ai_addr, result->ai_addrlen);
  HANDLE_SEND_RECV_ERRORS(sent_bytes);

  int bytes_recvd;
  int ans = 0;
  while ((bytes_recvd = recvfrom(fd, &ans, sizeof(ans), 0, result->ai_addr,
                                 &result->ai_addrlen)) < 0) {
    if (bytes_recvd == 0) {
      perror("Connection closed");
      exit(20);
    }
    printf("Timeout reached, sending again...\n");
    sent_bytes =
        sendto(fd, buf, BUF_SIZE, 0, result->ai_addr, result->ai_addrlen);
    HANDLE_SEND_RECV_ERRORS(sent_bytes);

    // second buffer sent
    sent_bytes =
        sendto(fd, buf2, BUF_SIZE, 0, result->ai_addr, result->ai_addrlen);
    HANDLE_SEND_RECV_ERRORS(sent_bytes);
  }
  ans = ntohl(ans);
  printf("Received response: %d\n", ans);
  close(fd);
  freeaddrinfo(res);
}
