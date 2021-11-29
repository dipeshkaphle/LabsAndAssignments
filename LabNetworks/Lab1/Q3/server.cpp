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

void print_conn_name(const sockaddr_storage *addr) {
  char buf[1000];
  inet_ntop(addr->ss_family, get_in_addr(addr), buf, sizeof(sockaddr_storage));
  int port = get_port(addr);
  printf("Connected to %s at port %d\n", buf, port);
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

bool check_integrity(int *arr, int n) {
  return all_of(arr, arr + n, [](int x) { return x % 2 == 0; });
}

int sum_all_elems(int *arr, int n) { return accumulate(arr, arr + n, 0); }

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
  struct addrinfo hints, *res;
  struct sockaddr_storage client_addr, client_addr2;
  socklen_t len = sizeof(client_addr);
  int status;
  int yes = 1;
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
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
      die_with_error("setsockopt() failed");

    status = bind(fd, result->ai_addr, result->ai_addrlen);
    if (status == -1)
      continue;
    break;
  }
  freeaddrinfo(res);
  if (result == NULL)
    die_with_error("binding failed");

  while (true) {
    // arr1
    num_bytes = recvfrom(fd, (void *)buf, BUF_SIZE, 0,
                         (struct sockaddr *)&client_addr, &len);
    HANDLE_SEND_RECV_ERRORS(num_bytes);
    int recvd_buf_size1 = num_bytes / sizeof(int);
    // handle endianness
    ntoh_arr((int *)buf, recvd_buf_size1);

    // arr2
    num_bytes = recvfrom(fd, (void *)buf2, BUF_SIZE, 0,
                         (struct sockaddr *)&client_addr, &len);
    HANDLE_SEND_RECV_ERRORS(num_bytes);
    int recvd_buf_size2 = num_bytes / sizeof(int);
    // handle endianness
    ntoh_arr((int *)buf2, recvd_buf_size2);
    print_conn_name(&client_addr);
    print_nums((int *)buf, (int *)buf2);

    if (check_integrity((int *)buf, recvd_buf_size1) &&
        check_integrity((int *)buf2, recvd_buf_size2)) {
      int sm1 = sum_all_elems((int *)buf, recvd_buf_size1);
      int sm2 = sum_all_elems((int *)buf2, recvd_buf_size2);
      int sm = sm1 + sm2;
      printf("%d\n", sm);
      sm = htonl(sm);
      status = sendto(fd, &sm, sizeof(sm), 0,
                      (const struct sockaddr *)&client_addr, len);
      HANDLE_SEND_RECV_ERRORS(status);
      sm = ntohl(sm);
      printf("Sent %d\n", sm);
    }
  }
}
