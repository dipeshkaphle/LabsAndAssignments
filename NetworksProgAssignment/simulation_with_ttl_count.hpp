#pragma once
#include "network.hpp"
#include "network_layer.hpp"
using network::Packet;
namespace ttl_based {

inline void handle_hosts(unordered_map<network_node, vector<PacketAndSrc>>
                             &router_queue_for_next_time_unit) {

  /**
   * What does a host do in simple flooding(having a fixed ttl)?
   *
   * For a packet to be sent by the host, I'm already checking if its
   * destination lies in the same network. This I did in
   * put_data_to_network_queue method of the Host class itself.
   *
   * So we know for sure whatever data is in the network_queue, it is supposed
   * to go through a router.
   *
   * So its purpose is to go through all the routers and flood the packets,
   * after decrementing ttl by 1 .
   *
   *
   */

  // Go through every host in the world
  for (auto &elem : Host::hosts) {
    auto host = elem.second;
    const network_node &host_as_node = *host; // polymorphism at use

    while (!host->network_queue.empty()) {

      if (host->network_queue.front().packet.ttl == 0) {
        host->network_queue.pop();
        continue;
      }
      PacketAndSrc front_packet = host->network_queue.front();

      for (auto router : host->hosts_routers) {

        const network_node &router_as_node = *router; // polymorphism

        // new packet that is to be sent should has ttl one less than the
        // current packet
        Packet new_packet = front_packet.packet;
        new_packet.ttl--;

        // Put the new packet and the source node(i.e the current host ) to
        // temporary queue that will be used in the next simulation
        router_queue_for_next_time_unit[router_as_node].push_back(
            PacketAndSrc(new_packet, host_as_node));

        LOG(*host, *router, new_packet);
      }
      host->network_queue.pop();
    }
  }
}

inline void handle_routers(unordered_map<network_node, vector<PacketAndSrc>>
                               &router_queue_for_next_time_unit) {

  /**
   * What does a router do in simple flooding(having a fixed ttl)?
   *
   * - It will check if the packet that it has in its queue is supposed to be
   * given to a host which it is connected with.
   * - If thats the case it will send the packet to that Host
   * - Else, It will flood the packet to all the routers in its reach, after
   * decrementing ttl by 1 for the packet
   */

  for (auto &elem : Router::routers) {
    auto router = elem.second;

    const network_node &router_as_node = *router; // polymorphism at use

    while (!router->network_queue.empty()) {
      if (router->network_queue.front().packet.ttl == 0) {
        router->network_queue.pop();
        continue;
      }
      PacketAndSrc front_packet = router->network_queue.front();

      bool we_have_the_destination_host = false;

      // Goes through all the  hosts in reach and check if the packet is
      // intended for them. If yes, RECEIVE it and pop from queue
      for (auto host : router->hosts) {
        const network_node &host_as_node = *host; // polymorphism
        if (front_packet.packet.destination == host->ip) {
          we_have_the_destination_host = true;
          // RECEIVE;
          RECEIVE(*router, *host, front_packet.packet);
        }
      }
      if (we_have_the_destination_host) {
        router->network_queue.pop();
        continue;
      }

      // Flood the packet to all the routers that are reachable
      for (auto dest_rtr : router->connected_routers) {
        const network_node &rtr_as_node = *dest_rtr; // polymorphism
        Packet new_packet = front_packet.packet;
        new_packet.ttl--;
        if (front_packet.source.ip != dest_rtr->ip) {
          router_queue_for_next_time_unit[rtr_as_node].push_back(
              PacketAndSrc(new_packet, router_as_node));
          LOG(*router, *dest_rtr, new_packet);
        }
      }

      router->network_queue.pop();
    }
  }
}

} // namespace ttl_based
