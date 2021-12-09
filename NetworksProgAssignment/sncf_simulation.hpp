#pragma once

// SNCF
//
// SNCF (Sequence Number Controlled Flooding)
//

#include "network.hpp"
#include "network_layer.hpp"

#include <functional>
#include <set>
#include <unordered_map>

using seq_number = int;

template <> struct std::hash<pair<network_node, seq_number>> {
  size_t operator()(const pair<network_node, seq_number> &p) const noexcept {
    return std::hash<network_node>()(p.first);
  }
};

namespace sncf {

/// Global variable to keep track of all the seen sequences of all the routers
std::unordered_map<Router *, unordered_set<pair<network_node, seq_number>>>
    seen_sequences;

inline void handle_hosts(unordered_map<network_node, vector<PacketAndSrc>>
                             &router_queue_for_next_time_unit) {
  /**
   * What does a host do in SNCF ?
   *
   * So we know for sure whatever data is in the network_queue, it is supposed
   * to go through a router.
   *
   * So its purpose is to go through all the routers and flood the packets,
   * after decrementing ttl by 1 . If the router has already seen the seq_no and
   * source before, it'll ignore
   *
   */

  // Go through every host in the world
  for (auto &elem : Host::hosts) {
    auto host = elem.second;

    const network_node &host_as_node = *host; // polymorphism at use

    // Check the hosts network queue
    // Process every request in the queue
    while (!host->network_queue.empty()) {
      if (host->network_queue.front().packet.ttl == 0) {
        host->network_queue.pop();
        continue;
      }

      PacketAndSrc front_packet_and_src = host->network_queue.front();
      for (auto router : host->hosts_routers) {
        const network_node &router_as_node = *router; // polymorphism

        if (seen_sequences[router].find(
                {network_node(front_packet_and_src.packet.source),
                 front_packet_and_src.packet.segment.seq_no}) !=
            seen_sequences[router].end()) {
          continue;
        }

        Packet new_packet = front_packet_and_src.packet;
        new_packet.ttl--;

        router_queue_for_next_time_unit[router_as_node].push_back(
            PacketAndSrc(new_packet, host_as_node));

        seen_sequences[router].insert(
            {network_node(front_packet_and_src.packet.source),
             front_packet_and_src.packet.segment.seq_no});

        LOG(*host, *router, new_packet);
      }
      host->network_queue.pop();
    }
  }
}

inline void handle_routers(unordered_map<network_node, vector<PacketAndSrc>>
                               &router_queue_for_next_time_unit) {

  /**
   * What does a Router do in SNCF ?
   *
   * - It will check if the packet that it has in its queue is supposed to be
   * given to a host which it is connected with.
   * - If thats the case it will send the packet to that Host
   * - Else, It will flood the packet to all the routers in its reach, after
   * decrementing ttl by 1 for the packet. But the destination router will check
   * the seen_sequences first to make sure the seq_no and source  is not seen
   * already. If it has already seen it, it'll discard. Else it'll put to its
   * network queue
   *
   */

  for (auto &elem : Router::routers) {
    auto router = elem.second;

    const network_node &router_as_node = *router; // polymorphism at use

    while (!router->network_queue.empty()) {
      bool we_have_the_destination_host = false;

      for (auto host : router->hosts) {
        const network_node &host_as_node = *host; // polymorphism
        PacketAndSrc front_packet = router->network_queue.front();
        if (front_packet.packet.destination == host->ip) {
          we_have_the_destination_host = true;
          // RECEIVE;
          RECEIVE(*router, *host, front_packet.packet);
        }
      }

      if (router->network_queue.front().packet.ttl == 0) {
        router->network_queue.pop();
        continue;
      }

      PacketAndSrc front_packet_and_src = router->network_queue.front();
      if (!we_have_the_destination_host) {
        for (auto dest_rtr : router->connected_routers) {
          const network_node &rtr_as_node = *dest_rtr; // polymorphism

          Packet new_packet = front_packet_and_src.packet;
          new_packet.ttl--;
          if (front_packet_and_src.source.ip != dest_rtr->ip) {

            if (seen_sequences[dest_rtr].find(
                    {network_node(front_packet_and_src.packet.source),
                     front_packet_and_src.packet.segment.seq_no}) !=
                seen_sequences[dest_rtr].end()) {
              DISCARD(*dest_rtr, *router, front_packet_and_src.packet);
              continue;
            }

            router_queue_for_next_time_unit[rtr_as_node].push_back(
                PacketAndSrc(new_packet, router_as_node));
            seen_sequences[dest_rtr].insert(
                {network_node(front_packet_and_src.packet.source),
                 front_packet_and_src.packet.segment.seq_no});
            LOG(*router, *dest_rtr, new_packet);
          }
        }
      }

      router->network_queue.pop();
    }
  }
}

}; // namespace sncf
