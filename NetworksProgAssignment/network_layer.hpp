#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>

#include "transport_layer.hpp"

namespace network {

using namespace std;

struct IP {
  int32_t ip;
  int n;

  IP(string ip_addr, int n) : n(n) { ip = IP::to_int(move(ip_addr)); }

  static int32_t to_int(string ip_addr) {
    vector<uint32_t> octets;
    auto l = ip_addr.begin();
    auto r = ip_addr.end();
    do {
      auto it = find(l, r, '.');
      auto s = string(l, it);
      octets.push_back(stoi(string(l, it)));
      l = min(++it, r);
    } while (l != r);
    assert(octets.size() == 4);
    return (octets[0] << 24) | (octets[1] << 16) | (octets[2] << 8) |
           (octets[3] << 0);
  }

  string addr_to_string() {
    vector<string> octets;
    octets.push_back(to_string(ip & (0xff)));
    octets.push_back(to_string((ip & (0xff00)) >> 8));
    octets.push_back(to_string((ip & (0xff0000)) >> 16));
    octets.push_back(to_string((ip & (0xff000000)) >> 24));
    reverse(octets.begin(), octets.end());
    return octets[0] + "." + octets[1] + "." + octets[2] + "." + octets[3];
  }

  string to_cidr() { return addr_to_string() + "/" + to_string(n); }

  bool operator==(const IP &other) const {
    return this->ip == other.ip && this->n == other.n;
  }
  bool operator!=(const IP &other) const { return !(*this == other); }
};

struct Packet {
  IP source;
  IP destination;
  int ttl;
  transport::Segment segment;

  Packet(IP src, IP dest, int ttl, transport::Segment segment)
      : source(src), destination(dest), ttl(ttl), segment(move(segment)) {}
};
//
}; // namespace network
