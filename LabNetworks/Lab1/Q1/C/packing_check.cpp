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

struct __attribute__((packed)) data {
  char c;
  int x;
  double y;
};
struct unpacked_data {
  char c;
  int x;
  double y;
};

int main() {
  printf("%d\n", sizeof(data));
  printf("%d\n", sizeof(unpacked_data));
}
