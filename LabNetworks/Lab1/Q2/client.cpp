#include <arpa/inet.h>
#include <iostream>
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

#define BUFSIZE 30

void die_with_error(const char *errorMessage) {
  perror(errorMessage);
  exit(1);
}

int recv_int(int sock) {
  int res = -1;
  int recv_msg_size;

  recv_msg_size = recv(sock, &res, sizeof(res), 0);
  HANDLE_SEND_RECV_ERRORS(recv_msg_size);
  return res;
}

void send_str(int sock, char msg_buf[BUFSIZE]) {
  int len = send(sock, msg_buf, strlen(msg_buf), 0);
  HANDLE_SEND_RECV_ERRORS(len);
  if (len != strlen(msg_buf))
    die_with_error("Couldn't send() fully");
}

void send_int(int sock, int payload) {
  int len = send(sock, &payload, sizeof(payload), 0);
  HANDLE_SEND_RECV_ERRORS(len);
  if (len != sizeof(payload))
    die_with_error("Couldn't send() fully");
}

void recv_str(int sock, char buf[BUFSIZE]) {
  int recv_msg_size;

  recv_msg_size = recv(sock, buf, BUFSIZE, 0);
  HANDLE_SEND_RECV_ERRORS(recv_msg_size);
  buf[recv_msg_size] = '\0';
}

void handle(int sock, int queryno) {
  if (queryno < 0 || queryno > 5)
    return;

  if (queryno == 1) {
    int partno;
    printf("Enter the part no: ");
    scanf("%d", &partno);

    send_int(sock, partno);
    char partname[BUFSIZE];
    recv_str(sock, partname);

    printf("%s\n\n", partname);
  } else if (queryno == 2) {
    int partno;
    printf("Enter the part no: ");
    scanf("%d", &partno);

    send_int(sock, partno);
    int qty = recv_int(sock);

    printf("Quantity: %d\n\n", qty);
  } else if (queryno == 3) {
    int custid, partno, qty;

    printf("Enter customer id: ");
    scanf("%d", &custid);

    printf("Enter the part no: ");
    scanf("%d", &partno);

    printf("Enter the quantity: ");
    scanf("%d", &qty);

    send_int(sock, custid);
    send_int(sock, partno);
    send_int(sock, qty);

    char status[BUFSIZE];
    recv_str(sock, status);

    printf("Status: %s\n\n", status);
  } else if (queryno == 4) {
    int partno;
    printf("Enter the part no: ");
    scanf("%d", &partno);

    send_int(sock, partno);
    int num = recv_int(sock);

    printf("%d subparts present\n", num);

    char response[BUFSIZE];
    for (int i = 0; i < num; ++i) {
      recv_str(sock, response);
      printf("%s, ", response);
    }
    printf("\n\n");
  } else if (queryno == 5) {
    char partname[BUFSIZE];

    printf("Enter the part name: ");
    scanf("%s", partname);

    send_str(sock, partname);
    int partno = recv_int(sock);

    if (partno == -1)
      printf("Does not exist\n\n");
    else
      printf("Part no: %d\n\n", partno);
  }
}

int main(int argc, char *argv[]) {
  int sock;
  unsigned short server_port;
  char *server_ip;

  if (argc != 3) {
    fprintf(stderr, "Usage: %s <Server IP> <Server Port>\n", argv[0]);
    exit(1);
  }

  server_ip = argv[1];
  server_port = atoi(argv[2]);

  struct addrinfo hints, *res;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  int status =
      getaddrinfo(server_ip, to_string(server_port).c_str(), &hints, &res);
  if (status == -1)
    die_with_error("getaddrinfo() failed");

  if ((sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0)
    die_with_error("socket() failed");

  if (connect(sock, res->ai_addr, res->ai_addrlen) < 0)
    die_with_error("connect() failed");

  freeaddrinfo(res);

  int queryno = 0;
  while (queryno != -1) {
    printf("%s\n%s\n%s\n%s\n%s\n%s\n", "1. obtain part name from number",
           "2. obtain quantity of parts avaliable", "3. order a part",
           "4. obtain list of subparts", "5. search for part",
           "Enter the query number: ");

    scanf("%d", &queryno);
    send_int(sock, queryno);
    handle(sock, queryno);
  }

  close(sock);
  exit(0);
}
