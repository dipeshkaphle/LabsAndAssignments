#include <arpa/inet.h>
#include <condition_variable>
#include <deque>
#include <functional>
#include <iostream>
#include <mutex>
#include <netdb.h>
#include <netinet/in.h>
#include <optional>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
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

void send_int(int fd, int val) {
  val = htonl(val);
  send(fd, &val, sizeof(int), 0);
}
int recv_int(int fd) {
  int x;
  recv(fd, &x, sizeof(int), 0);
  return ntohl(x);
}

struct Client {
  int client_fd;
  struct addrinfo *result;
  mutex mt;
  condition_variable cv;
  mutex dq_mt;
  int opt;
  deque<string> dq;

  Client(const char *address, const char *port_no) {
    this->result = Client::addr_setup(address, port_no);
    this->client_fd = Client::setup_client_socket(this->result);
    opt = -1;
  }

  ~Client() {
    freeaddrinfo(result);
    close(client_fd);
  }

  void receiver_thread() {
    struct pollfd fds[1];
    fds[0].fd = this->client_fd;
    fds[0].events = POLLIN;
    while (true) {
      std::unique_lock<mutex> lock(mt);
      cv.wait(lock, [&]() { return this->opt != 1; });
      if (opt == 0) {
        break;
      }
      int out = poll(fds, 1, 500);
      if (out == 0) {
        continue;
      }
      if (fds[0].revents & POLLHUP) {
        // means connection was closed
        break;
      }
      if (fds[0].revents & POLLIN) {
        int msg_size = recv_int(this->client_fd);
        auto messsage = this->receive<string>(this->client_fd, msg_size,
                                              [](const char *s) { return s; });
        std::unique_lock<mutex> q_lock(dq_mt);
        dq.push_back(std::move(messsage));
      }
    }
  }
  void handle_connection() {
    // Handle the connection

    thread t([&]() { this->receiver_thread(); });
    t.detach();

    string s;
    while (true) {
      cout << "Enter (exit/get_online/send): ";
      cin >> s;
      if (s == "exit") {
        opt = 1;
        cv.notify_one();
        std::unique_lock<mutex> lock(mt);
        opt = 0;
        send_int(this->client_fd, 0);
        cv.notify_one();
        break;
      } else if (s == "get_online") {
        opt = 1;
        cv.notify_one();
        std::unique_lock<mutex> lock(mt);
        send_int(this->client_fd, 1);
        int sz = recv_int(this->client_fd);
        auto messsage = this->receive<string>(this->client_fd, sz,
                                              [](const char *s) { return s; });
        cout << "All Online are: " << endl;
        cout << messsage << endl;
        opt = -1;
      } else if (s == "send") {
        send_int(this->client_fd, 2);
        string x, dest;
        cout << "Enter Message to send: ";
        cin.ignore();
        getline(cin, x);
        // cin.sync();
        cout << "Enter Destination address: ";
        getline(cin, dest);
        // cin >> dest;
        send_int(this->client_fd, x.size());
        this->send<string>(this->client_fd, x, [](string t) {
          vector<uint8_t> vec;
          copy(t.begin(), t.end(), back_inserter(vec));
          return vec;
        });
        send_int(this->client_fd, dest.size());
        this->send<string>(this->client_fd, dest, [](string t) {
          vector<uint8_t> vec;
          copy(t.begin(), t.end(), back_inserter(vec));
          return vec;
        });
        cin.sync();
      }

      cv.notify_one();
      std::unique_lock<mutex> dq_lock(dq_mt);
      while (!dq.empty()) {
        cout << dq.front() << endl;
        dq.pop_front();
      }
    }
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

  static struct addrinfo *addr_setup(const char *address, const char *port_no) {
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

  static int setup_client_socket(struct addrinfo *result) {
    int yes = 1;
    int sock_fd =
        socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (sock_fd < 0)
      die_with_error("socket()");
    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT | SO_LINGER,
                   &yes, sizeof(yes)) < 0)
      die_with_error("setsockopt");
    if (connect(sock_fd, result->ai_addr, result->ai_addrlen) < 0)
      die_with_error("bind()");
    return sock_fd;
  }
};

int main() {
  cout.rdbuf()->pubsetbuf(0, 0);
  string port;
  cout << "enter port: ";
  cin >> port;
  cout << endl;
  Client cl(NULL, port.c_str());
  cl.handle_connection();

  // this_thread::yield();
  //
}
