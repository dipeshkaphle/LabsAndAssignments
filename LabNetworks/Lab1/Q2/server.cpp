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

#define MAXPENDING 5 /* Maximum outstanding connection requests */
#define NAMESIZE 10
#define DESCSIZE 10
#define BUFSIZE 30
#define PARTSSIZE 5
#define CUSTSIZE 5
#define SUBPARTSSIZE 2

typedef struct part_t {
  int number;
  char name[NAMESIZE];
  int price;
  char desc[DESCSIZE];
  int qty;
  int subparts[SUBPARTSSIZE];
} part;

typedef struct order_t {
  int partno;
  int qty;
} order;

typedef struct customer_t {
  int acno;
  order ord;
} customer;

part parts[PARTSSIZE];
customer customers[CUSTSIZE];

void populate() {
  // 0 - wheel
  // 1 - tyre
  // 2 - door
  // 3 - engine
  // 4 - shaft
  strcpy(parts[0].name, "Wheel");
  strcpy(parts[0].desc, "Car Wheel");
  parts[0].number = 0;
  parts[0].price = 5000;
  parts[0].qty = 100;
  parts[0].subparts[0] = 1; // tyre
  parts[0].subparts[1] = -1;

  strcpy(parts[1].name, "Tyre");
  strcpy(parts[1].desc, "Rubber Tyre");
  parts[1].number = 1;
  parts[1].price = 2000;
  parts[1].qty = 200;
  parts[1].subparts[0] = -1;
  parts[1].subparts[1] = -1;

  strcpy(parts[2].name, "Door");
  strcpy(parts[2].desc, "Metal Door");
  parts[2].number = 2;
  parts[2].price = 10000;
  parts[2].qty = 150;
  parts[2].subparts[0] = -1;
  parts[2].subparts[1] = -1;

  strcpy(parts[3].name, "Engine");
  strcpy(parts[3].desc, "Petrol Engine");
  parts[3].number = 3;
  parts[3].price = 50000;
  parts[3].qty = 20;
  parts[3].subparts[0] = 4; // shaft
  parts[3].subparts[1] = -1;

  strcpy(parts[4].name, "Shaft");
  strcpy(parts[4].desc, "Crankshaft");
  parts[4].number = 4;
  parts[4].price = 7500;
  parts[4].qty = 50;
  parts[4].subparts[0] = -1;
  parts[4].subparts[1] = -1;

  customers[0].acno = 0;
  customers[1].acno = 1;
  customers[2].acno = 2;
  customers[3].acno = 3;
  customers[4].acno = 4;
}

void die_with_error(const char *errorMessage) {
  perror(errorMessage);
  exit(1);
}

int recv_int(int sock) {
  int res = -1;
  int recv_msg_size;

  if ((recv_msg_size = recv(sock, &res, sizeof(res), 0)) < 0)
    die_with_error("recv() failed");
  return res;
}

void send_str(int sock, char *msg_buf) {
  int status = send(sock, msg_buf, strlen(msg_buf), 0);
  HANDLE_SEND_RECV_ERRORS(status);
  if (status != strlen(msg_buf))
    die_with_error("Couldn't send() fully");
}

void send_int(int sock, int payload) {
  int status = send(sock, &payload, sizeof(payload), 0);
  HANDLE_SEND_RECV_ERRORS(status);
  if (status != sizeof(payload))
    die_with_error("Couldn't send() fully");
}

void recv_str(int sock, char buf[BUFSIZE]) {
  int recv_msg_size;

  recv_msg_size = recv(sock, buf, BUFSIZE, 0);
  HANDLE_SEND_RECV_ERRORS(recv_msg_size);
}

void handle_client(int client_socket, int queryno) {
  if (queryno < 0 || queryno > 5)
    return;
  // 1: obtain part name from part number
  // 2: give quantity of parts avaliable
  // 3: order a part
  // 4: obtain list of subpart numbers
  // 5: search for part

  printf("Got query %d\n", queryno);

  if (queryno == 1) {
    char name[NAMESIZE];
    strcpy(name, "Invalid");
    int partno = recv_int(client_socket);

    if (partno < PARTSSIZE)
      strcpy(name, parts[partno].name);

    send_str(client_socket, name);
  } else if (queryno == 2) {
    int partno = recv_int(client_socket);
    int result = 0;

    if (partno < PARTSSIZE)
      result = parts[partno].qty;

    send_int(client_socket, result);
  } else if (queryno == 3) {
    int custid = recv_int(client_socket);
    int partno = recv_int(client_socket);
    int qty = recv_int(client_socket);

    char response[BUFSIZE];
    strcpy(response, "Failed");

    if (partno < PARTSSIZE && parts[partno].qty >= qty) {
      if (custid < CUSTSIZE) {
        customers[custid].ord.partno = partno;
        customers[custid].ord.qty = qty;

        parts[partno].qty -= qty;

        strcpy(response, "Success");
      }
    }

    send_str(client_socket, response);
  } else if (queryno == 4) {
    int partno = recv_int(client_socket);
    char response[BUFSIZE];
    strcpy(response, "Empty");

    if (partno < PARTSSIZE) {
      int num = 0;
      for (int i = 0; i < PARTSSIZE && parts[partno].subparts[i] != -1; ++i)
        ++num;

      send_int(client_socket, num);

      for (int i = 0; i < num; ++i) {
        strcpy(response, parts[parts[partno].subparts[i]].name);
        send_str(client_socket, response);
      }
    }
  } else if (queryno == 5) {
    char partname[BUFSIZE];
    recv_str(client_socket, partname);

    int partno = -1;
    for (int i = 0; i < PARTSSIZE; ++i)
      if (strcmp(partname, parts[i].name) == 0)
        partno = i;

    send_int(client_socket, partno);
  }
}

int main(int argc, char *argv[]) {
  int server_socket;
  int client_socket;
  struct sockaddr_storage client_addr;
  unsigned short port;
  unsigned int client_len;

  if (argc != 2) {
    fprintf(stderr, "Usage:  %s <Port>\n", argv[0]);
    exit(1);
  }

  port = atoi(argv[1]);

  populate();

  struct addrinfo hints, *res;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  if (getaddrinfo(NULL, to_string(port).c_str(), &hints, &res) == -1) {
    die_with_error("getaddrinfo()");
  }

  if ((server_socket =
           socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0)
    die_with_error("socket() failed");

  /* Bind to the local address */
  if (bind(server_socket, res->ai_addr, res->ai_addrlen) < 0)
    die_with_error("bind() failed");

  // frees heap memory
  freeaddrinfo(res);

  /* Mark the socket so it will listen for incoming connections */
  if (listen(server_socket, MAXPENDING) < 0)
    die_with_error("listen() failed");

  int queryno = 0;
  while (queryno != -1) {
    client_len = sizeof(client_addr);

    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr,
                                &client_len)) < 0)
      die_with_error("accept() failed");

    while (queryno != -1) {
      queryno = recv_int(client_socket);
      handle_client(client_socket, queryno);
    }
  }

  close(client_socket);

  return 0;
}
