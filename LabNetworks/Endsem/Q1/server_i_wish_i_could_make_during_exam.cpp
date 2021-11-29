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
#include <thread>
#include <unistd.h>
#include <unordered_map>
#include <vector>

using namespace std;
void send_int(int fd, int val) {
  val = htonl(val);
  send(fd, &val, sizeof(int), 0);
}
int recv_int(int fd) {
  int x;
  recv(fd, &x, sizeof(int), 0);
  return ntohl(x);
}

#define HANDLE_SEND_RECV_ERRORS_BUT_DONT_EXIT(st)                              \
  if (st == -1) {                                                              \
    perror("Error in send()/recv()");                                          \
  } else if ((st) == 0) {                                                      \
    perror("Connection is closed because send/recv returned 0");               \
  }

#define HANDLE_SEND_RECV_ERRORS(st)                                            \
  if (st == -1) {                                                              \
    perror("Error in send()/recv()");                                          \
    return 254;                                                                \
  } else if ((st) == 0) {                                                      \
    perror("Connection is closed because send/recv returned 0");               \
    return 255;                                                                \
  }

void die_with_error(const char *message, int err_code = 1) {
  perror(message);
  exit(err_code);
}

struct Server {
  int sock_fd;
  struct addrinfo *result;
  static unordered_map<string, int> ip_to_fd;

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
    string my_ip = Server::get_ip_port(&addr).first + "/" +
                   to_string(Server::get_ip_port(&addr).second);
    while (true) {
      int op = recv_int(client_fd);
      if (op == 0) {
        ip_to_fd.erase(my_ip);
        close(client_fd);
        break;
      } else if (op == 1) {
        string s;
        for (auto &[k, v] : ip_to_fd) {
          if (v == client_fd) {
            continue;
          }
          s += k;
          s += '\n';
        }
        if (s.empty()) {
          s = "NOONE IS ONLINE\n";
        }
        send_int(client_fd, s.size());
        Server::send<string>(client_fd, s, [](string t) {
          vector<uint8_t> vec;
          copy(t.begin(), t.end(), back_inserter(vec));
          return vec;
        });
      } else if (op == 2) {
        int msg_size = recv_int(client_fd);
        string msg = Server::receive<string>(
            client_fd, msg_size, [](const char *buf) { return buf; });

        int ip_sz = recv_int(client_fd);

        string dest_ip = Server::receive<string>(
            client_fd, ip_sz, [](const char *buf) { return buf; });
        msg += ("\n -BY IP: " + my_ip);
        // cout << "Sending : \n"
        // << msg << "\n"
        // << "to: " << dest_ip << ":" << ip_to_fd[dest_ip] << '\n';
        if (!ip_to_fd.count(dest_ip)) {
          continue;
        }
        send_int(ip_to_fd[dest_ip], msg.size());
        Server::send<string>(ip_to_fd[dest_ip], msg, [](string t) {
          vector<uint8_t> vec;
          copy(t.begin(), t.end(), back_inserter(vec));
          return vec;
        });
      }
    }
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
  static int send(int client_fd, T message,
                  std::function<vector<uint8_t>(T)> f) {
    //
    auto data = f(move(message));
    auto st = ::send(client_fd, &data[0], data.size(), 0);
    HANDLE_SEND_RECV_ERRORS(st);
    return st;
  }
  template <typename T>
  static T receive(int client_fd, size_t sz, std::function<T(const char *)> f) {
    //
    char buf[sz + 10];
    auto st = recv(client_fd, buf, sz, 0);
    HANDLE_SEND_RECV_ERRORS_BUT_DONT_EXIT(st);
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
unordered_map<string, int> Server::ip_to_fd = unordered_map<string, int>();

int main() {
  string port;
  cout << "enter port: ";
  cin >> port;
  cout << endl;
  Server s(NULL, port.c_str());
  s.listen(10);

  vector<std::pair<int, struct sockaddr_storage>> conns;
  while (true) {
    auto [conn, addr] = s.accept_connection();
    cout << "Connected to : " << Server::get_ip_port(&addr).first << '/'
         << Server::get_ip_port(&addr).second << endl;
    conns.push_back({conn, addr});
    Server::ip_to_fd[Server::get_ip_port(&addr).first + "/" +
                     to_string(Server::get_ip_port(&addr).second)] = conn;
    thread t(Server::handle_client, conns.back().first,
             std::ref(conns.back().second));
    t.detach();
  }
}
