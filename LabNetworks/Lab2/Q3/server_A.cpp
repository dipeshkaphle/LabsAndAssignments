#include "file_splitter.h"
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
    die_with_error("getaddrinfo");
  return result;
}

int setup_socket(struct addrinfo *result) {
  int yes = 1;
  int sock_fd =
      socket(result->ai_family, result->ai_socktype, result->ai_protocol);
  if (sock_fd < 0)
    die_with_error("socket()");
  if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT | SO_LINGER,
                 &yes, sizeof(yes)) < 0)
    die_with_error("setsockopt");
  if (bind(sock_fd, result->ai_addr, result->ai_addrlen) < 0)
    die_with_error("bind()");
  return sock_fd;
}

pair<int, struct sockaddr_storage> accept_connection(int sock_fd) {
  struct sockaddr_storage addr;
  socklen_t len = sizeof(addr);
  int client_fd = accept(sock_fd, (struct sockaddr *)&addr, &len);
  if (client_fd == -1)
    die_with_error("accept()");
  return {client_fd, addr};
}

vector<int> get_five_random_nums(int mod) {
  srand(time(NULL));
  vector<int> nums(mod);
  iota(nums.begin(), nums.end(), 0);
  random_shuffle(nums.begin(), nums.end());
  return vector<int>(nums.begin(), nums.begin() + 5);
}

void send_file_chunk(int conn, const file_chunk &chunk) {
  cout << endl << chunk.chunk_no << ":" << chunk.sz << endl;
  int size = chunk.sz;
  int chunk_id = chunk.chunk_no;
  int big_endian_sz = htonl(size);
  int big_endian_id = htonl(chunk_id);
  int status;

  status = send(conn, (void *)&big_endian_sz, sizeof(int), 0);
  cout << "sent size for " << chunk.chunk_no << ":" << status << endl;
  HANDLE_SEND_RECV_ERRORS(status);
  status = send(conn, (void *)&big_endian_id, sizeof(int), 0);
  cout << "sent id for " << chunk.chunk_no << ":" << status << endl;
  HANDLE_SEND_RECV_ERRORS(status);

  int total_sent = 0;
  const char *buf = chunk.buf.c_str();
  while (total_sent != size) {
    int bytes_sent =
        send(conn, (void *)(buf + total_sent), size - total_sent, 0);
    HANDLE_SEND_RECV_ERRORS(bytes_sent);
    cout << bytes_sent << ':' << total_sent << ' ';
    total_sent += bytes_sent;
  }
  cout << endl;
}

void handle_connection(int conn) {
  array<file_chunk, 10> file_chunks = splitter("./large_file.txt");
  auto five_random_chunk_no = get_five_random_nums(10);
  for (int id : five_random_chunk_no)
    cout << id << ' ' << file_chunks[id].buf.size() << '\n';
  for (int id : five_random_chunk_no) {
    // cout << id << '\n';
    send_file_chunk(conn, file_chunks[id]);
  }
}

int main() {
  int sock_fd;
  struct addrinfo *result = addr_setup(NULL, "3000");
  sock_fd = setup_socket(result);
  freeaddrinfo(result);
  listen(sock_fd, 10);

  auto [conn, addr] = accept_connection(sock_fd);
  handle_connection(conn);

  close(sock_fd);
}
