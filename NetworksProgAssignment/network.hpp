#pragma once

#include <functional>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "network_layer.hpp"

using namespace std;

struct PacketAndSrc;

struct network_node {
  network::IP ip;
  /*
   * This is a network queue
   *
   * The packets that the particular network_node(be that router or host) has to
   * process are in this
   *
   * If the queue has something in it it will immediately be processed during
   * the simulation. There's no concept of dropping packets and bandwith in the
   * miniature simulation that I'm doing
   *
   */
  queue<PacketAndSrc> network_queue;

  /*
   * Copy constructor for network_node class
   */
  network_node(network::IP ip) : ip(ip) {}

  /*
   * Equal to comparison operator for network_node, it basically compares the
   * IPs of two network_node objects
   */
  bool operator==(const network_node &other) const { return ip == other.ip; }

  /*
   * This will use subnet mask and IP to determine whether two network_node are
   * in the same network
   *
   * Since Router and Host classes both derive from network_node, we can use
   * polymorphism here to know whether those belong to same network
   */
  static bool is_same_network(const network_node &node1,
                              const network_node &node2) {
    auto x = node1.ip.ip & ((1 << 31) >> (node1.ip.n - 1));
    auto y = node2.ip.ip & ((1 << 31) >> (node2.ip.n - 1));
    return x == y;
  }
};

/*
 * making network node hashable, becaue I'm storing network_node in
 * unordered_map which requires its key be hashable
 */
template <> struct std::hash<network_node> {
  size_t operator()(const network_node &node) const noexcept {
    return (std::hash<int32_t>()(node.ip.ip) ^ std::hash<int32_t>()(node.ip.n));
  }
};

/*
 * A struct to store Packet and the intermediate source it came from.
 * This is what Im using in the network queue of any network_node(Host or
 * Router)
 */
struct PacketAndSrc {
  network::Packet packet;
  network_node source;
  PacketAndSrc(network::Packet pkt, const network_node &src)
      : packet(pkt), source(src) {}
};

/*
 * Forward declaration of Router, because Im using the class in Host but its not
 * been defined yet, so I need to do this.
 */
struct Router;

// HOST Class
struct Host : network_node {

  /*
   * Stores all the pointers to router the host is connected to
   */
  unordered_set<Router *> hosts_routers; // stores router ids

  /*
   * This is something I'm using to keep track of all the host that have ever
   * been instantiated. This will ensure that I have no two Hosts with same IP
   * as well
   */
  static unordered_map<network_node, Host *> hosts;

  Host(network::IP ip) : network_node(ip) {
    /*
     * I will check if there's already a host with same IP
     * If yes, I will throw error crashing the program
     */
    if (hosts.find(static_cast<network_node>(*this)) != hosts.end()) {
      throw std::runtime_error("A Host with same IP already exists.\n"
                               "There cant be two hosts with same IP\n"
                               "It will cause issues\n");
    }
    /*
     *Else, I will add the entry of this Host along with its address
     */
    hosts[static_cast<network_node>(*this)] = this;
  }

  /*
   * Move constructor of Host
   *
   * This is especially useful  when we are using Host with vector i.e
   * vector<Host>
   *
   * vector will resize from time to time if we're pushing to it, and while
   * resizing it needs to move the Host to different memory location. To do that
   * it will invoke its move constructor which should be able to address the
   * memory change and update the hosts unordered_map with new memory address
   */
  Host(Host &&h) : network_node(h.ip) {
    this->network_queue = move(h.network_queue);
    this->hosts_routers = move(h.hosts_routers);
    hosts[static_cast<network_node>(*this)] = this;
  }

  /*
   * Gets the address of the Host
   */
  Host *get() { return this; }

  /*
   * Takes in raw message,destination and ttl
   *
   * - Converts the message to application layer data
   * - Splits the application layer data to segments of size mss
   * - Converts all the segments to network layer packets
   *
   *  ttl here specifies the maximum hop count a packet can take
   */
  void put_data_to_network_queue(string message, Host &destination, int ttl) {
    using application::data;
    using network::Packet;
    using transport::Segment;

    data msg(message);

    // Divide message into segments of size Segment::mss(maximum segment size)
    vector<Segment> segments = Segment::make_segments(msg);
    vector<Packet> packets;
    // Converts every single segment to packet
    transform(segments.begin(), segments.end(), back_inserter(packets),
              [&](const Segment &segment) {
                return Packet(this->ip, destination.ip, ttl, segment);
              });

    cout << "Preparing to send  the following packets\n";

    for (auto &packet : packets) {
      cout << "\tPacket(" << packet.segment.seq_no << ","
           << packet.segment.get_data_as_string() << "," << packet.ttl << ")\n";
    }

    for (auto &packet : packets) {
      // If the packet's destination is somewhere in the same network,
      // We just log it
      if (packet.destination == this->ip ||
          is_same_network(*this, network_node(packet.destination))) {
        // Logging that the packet is received instantly
        cout << "Host(" << packet.destination.to_cidr() << ") received "
             << packet.segment.get_data_size() << " from "
             << "Host(" << this->ip.to_cidr() << ")\n"
             << "\tinstantly because they're in same network"
                "\n";

      } else { // if it needs to go through router, we put it in network queue
               // the IP 0.0.0.0 was chosen to make it distinct and to ensure no
               // other node in the network had it
        this->network_queue.push(
            PacketAndSrc(packet, network_node(network::IP("0.0.0.0", 32))));
      }
    }
  }
};

struct Router : network_node {
  /*
   * This is something I'm using to keep track of all the Routers that have ever
   * been instantiated. This will ensure that I have no two Routers with same IP
   * as well
   */
  static unordered_map<network_node, Router *> routers;

  // All the hosts that the router is connected to
  std::unordered_set<Host *> hosts;
  // All the routers that this router has direct connection to
  std::unordered_set<Router *> connected_routers;

  Router(network::IP ip) : network_node(ip) {
    // This is similar to what I am doing in Host's constructor
    // To ensure no duplicacy
    if (routers.find(static_cast<network_node>(*this)) != routers.end()) {
      throw std::runtime_error("A Router with same IP already exists.\n"
                               "There cant be two routers with same IP\n"
                               "It will cause issues\n");
    }
    routers[static_cast<network_node>(*this)] = this;
  }
  // Move constructor for router
  Router(Router &&router) : network_node(router.ip) {
    this->network_queue = move(router.network_queue);
    this->connected_routers = move(router.connected_routers);
    this->hosts = move(router.hosts);
    routers[static_cast<network_node>(*this)] = this;
  }

  Router *get() { return this; }

  void connect(Router &r) {
    this->connected_routers.insert(r.get());
    r.connected_routers.insert(this);
  }
  void connect(Host &h) {
    this->hosts.insert(h.get());
    h.hosts_routers.insert(this);
  }
};
//
//

using network::Packet;

// Loggers for simulation
inline void RECEIVE(Router &src, Host &dest, Packet &p) {
  cout << "!!!! REACHED DESTINATION:  H(" << dest.ip.to_cidr()
       << ") received destined Pkt( seq_no: " << p.segment.seq_no
       << ", data: " << p.segment.get_data_as_string() << ")"
       << " from R(" << src.ip.to_cidr() << ")\n";
}
inline void LOG(Router &src, Router &dest, Packet &p) {
  cout << "R(" << dest.ip.to_cidr()
       << ") received Pkt( seq_no: " << p.segment.seq_no << ", ttl: " << p.ttl
       << ")"
       << " from R(" << src.ip.to_cidr() << ")\n";
}
inline void LOG(Host &src, Router &dest, Packet &p) {
  cout << "R(" << dest.ip.to_cidr()
       << ") received Pkt( seq_no: " << p.segment.seq_no << ", ttl: " << p.ttl
       << ")"
       << " from H(" << src.ip.to_cidr() << ")\n";
}

// DISCARD Packet, used in sncf to log discarding a packet when we've already
// seen the packet before
inline void DISCARD(Router &r1, Router &r2, Packet &p) {

  cout << "R(" << r1.ip.to_cidr()
       << ") discards Pkt( seq_no: " << p.segment.seq_no << ") coming from R("
       << r2.ip.to_cidr() << ")\n";
  //
}
