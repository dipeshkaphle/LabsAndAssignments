#include "application_layer.hpp"
#include "network.hpp"
#include "network_layer.hpp"
#include "simulation_with_ttl_count.hpp"
#include "sncf_simulation.hpp"
#include "transport_layer.hpp"

#include <fstream>
#include <iostream>
#include <set>

using namespace std;
using network::Packet;

size_t transport::Segment::mss = 2;

unordered_map<network_node, Router *> Router::routers =
    unordered_map<network_node, Router *>();

unordered_map<network_node, Host *> Host::hosts =
    unordered_map<network_node, Host *>();

extern std::unordered_map<Router *,
                          unordered_set<pair<network_node, seq_number>>>
    seen_sequences;

using arg_type = unordered_map<network_node, vector<PacketAndSrc>>;

void simulate(void (*handle_hosts)(arg_type &),
              void (*handle_routers)(arg_type &)) {

  arg_type router_queue_for_next_time_unit;

  handle_hosts(router_queue_for_next_time_unit);
  handle_routers(router_queue_for_next_time_unit);

  for (auto &p : Router::routers) {
    auto router = p.second;
    const network_node &router_as_node = *router;
    router->network_queue = queue<PacketAndSrc>();
    for (auto &x : router_queue_for_next_time_unit[router_as_node]) {
      router->network_queue.push(x);
    }
  }
  //
}

bool all_queues_empty() {
  return (all_of(Host::hosts.begin(), Host::hosts.end(),
                 [](auto &h) { return h.second->network_queue.empty(); })) &&
         (all_of(Router::routers.begin(), Router::routers.end(),
                 [](auto &r) { return r.second->network_queue.empty(); }));
}

int main() {
  using network::IP;

  ifstream inp("input.txt");

  int host_count, router_count, connection_count;
  string simulation_type, source, destination, message_to_send;
  int ttl;

  cout << "Enter the Simulation type(TTLBased,SNCF): ";
  cin >> simulation_type;

  inp >> ttl;

  inp >> host_count >> router_count >> connection_count;

  inp >> source;
  inp >> destination;
  inp >> message_to_send;

  vector<Host> hosts;
  vector<Router> routers;
  unordered_map<string, Host *> host_names;
  unordered_map<string, Router *> router_names;

  for (int i = 0; i < host_count; i++) {
    string ip;
    int mask;
    inp >> ip >> mask;
    hosts.emplace_back(IP(ip, mask));
  }
  for (int i = 0; i < host_count; i++)
    host_names["H" + to_string(i)] = hosts[i].get();

  for (int i = 0; i < router_count; i++) {
    string ip;
    int mask;
    inp >> ip >> mask;
    routers.emplace_back(IP(ip, mask));
  }
  for (int i = 0; i < router_count; i++)
    router_names["R" + to_string(i)] = routers[i].get();

  for (int i = 0; i < connection_count; i++) {
    string x, y;
    inp >> x >> y;
    if (x[0] == 'R' && y[0] == 'R') { // Router -> Router
      router_names[x]->connect(*router_names[y]);
    } else if (x[0] == 'R' && y[0] == 'H') { // Router -> Host
      router_names[x]->connect(*host_names[y]);
    }
  }

  host_names[source]->put_data_to_network_queue(message_to_send,
                                                *host_names[destination], ttl);

  while (true) {
    char c;
    cout << "\n\n";
    cout << "Enter y to continue simulation: ";
    cin >> c;
    if (c == 'y') {
      if (all_queues_empty()) {
        cout << "All queues are empty, so no point of simulating further\n";
        break;
      }

      if (simulation_type == "TTLBased") {
        simulate(ttl_based::handle_hosts, ttl_based::handle_routers);
      } else if (simulation_type == "SNCF") {
        simulate(sncf::handle_hosts, sncf::handle_routers);
      } else {
        continue;
      }
    } else
      break;
  }
}
