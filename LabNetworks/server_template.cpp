#include <arpa/inet.h>
#include <functional>
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
#include <vector>

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

struct Server {
  int sock_fd;
  struct addrinfo *result;

  Server(const char *address, const char *port_no) {
    this->result = Server::addr_setup(address, port_no);
    this->sock_fd = Server::setup_socket(this->result);
  }

  ~Server() {
    freeaddrinfo(this->result);
    close(sock_fd);
  }

  int listen(int n) { return ::listen(sock_fd, n); }

  std::pair<int, struct sockaddr_storage> accept_connection() {
    struct sockaddr_storage addr;
    socklen_t len = sizeof(addr);
    int client_fd = accept(this->sock_fd, (struct sockaddr *)&addr, &len);
    if (client_fd == -1)
      die_with_error("accept()");
    return {client_fd, addr};
  }

  static void handle_client(int client_fd,
                            const struct sockaddr_storage &addr) {
    // Handle the client connection
  }

  static std::pair<std::string, int> get_ip_port(const sockaddr_storage *addr) {
    int port;
    char buf[1000];
    if (addr->ss_family == AF_INET) {
      port = ((struct sockaddr_in *)addr)->sin_port;
      inet_ntop(addr->ss_family, &((struct sockaddr_in *)addr)->sin_addr, buf,
                sizeof(sockaddr_storage));
    } else {
      port = ((struct sockaddr_in6 *)addr)->sin6_port;
      inet_ntop(addr->ss_family, &((struct sockaddr_in6 *)addr)->sin6_addr, buf,
                sizeof(sockaddr_storage));
    }
    return {std::string(buf), port};
  }

  template <typename T>
  void send(int client_fd, T message, std::function<vector<uint8_t>(T)> f) {
    //
    auto data = f(move(message));
    auto st = ::send(client_fd, &data[0], data.size(), 0);
    HANDLE_SEND_RECV_ERRORS(st);
  }
  template <typename T>
  T receive(int client_fd, size_t sz, std::function<T(const char *)> f) {
    //
    char buf[sz + 10];
    auto st = recv(client_fd, buf, sz, 0);
    HANDLE_SEND_RECV_ERRORS(st);
    buf[st] = 0;
    return f(buf);
  }

  static int setup_socket(struct addrinfo *result) {
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
  static struct addrinfo *addr_setup(const char *address, const char *port_no) {
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_addr = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int status = getaddrinfo(address, port_no, &hints, &res);
    if (status != 0)
      die_with_error("getaddrinfo");
    return res;
  }
};

int main() {
  Server s(NULL, "8000");
  s.listen(10);
  cout << "Here\n";
  auto [conn, addr] = s.accept_connection();

  cout << s.receive<string>(conn, 4, [](const char *buf) -> string {
    return buf;
  }) << '\n';

  s.send<std::vector<char>>(conn, std::vector<char>{'a', 'b', 'c'},
                            [](vector<char> s) {
                              vector<uint8_t> vec;
                              copy(s.begin(), s.end(), back_inserter(vec));
                              return vec;
                            });
}
