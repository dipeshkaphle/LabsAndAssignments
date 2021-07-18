#include <iostream>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <vector>

using namespace std;

struct process {
  int process_num;
  int q_num;
  int arrival;
  int started_time;
  int burst;
  process() { process_num = -1; }
  process(int p_num, int q_num, int arr, int burst)
      : process_num(p_num), q_num(q_num), arrival(arr), burst(burst) {}
  // comparision in queue will be based on arrival time
  bool operator<(const process &other) const {
    return this->arrival < other.arrival;
  }
  bool operator>(const process &other) const {
    return this->arrival > other.arrival;
  }
  bool operator==(const process &other) const {
    return this->process_num == other.process_num;
  }
};

int main(int argc, char **argv) {
  array<int, 2> queue_quantum = {4, 2};

  unordered_map<int, process> arrival_time_map;

  unordered_map<int, int> finishing_times;
  unordered_map<int, int> arrivals;
  unordered_map<int, int> waitings;

  vector<process> table;

  int num_of_process;
  cout << "Enter num of processes: ";
  cin >> num_of_process;

  // input part
  for (int i = 0; i < num_of_process; i++) {
    int q_num, process_num, arrival, burst;
    cout << "Enter process number, queue number, arrival time and burst time "
            "for the process\n";
    cin >> process_num >> q_num >> arrival >> burst;
    table.push_back(process(process_num, q_num, arrival, burst));
    // maps the arrival time to process
    arrival_time_map[arrival] = table.back();
    arrivals[table.back().process_num] = arrival;
  }

  // Q1's priority is higher than Q2
  priority_queue<process, vector<process>, std::greater<process>>
      Q1; // has quantum 4
  priority_queue<process, vector<process>, std::greater<process>>
      Q2; // has quantum 2

  int sec = 0;
  int running_queue = 1;
  // will keep track of the currently running process if any
  process running_process;

  while (true) {
    process &p = running_process; // alias for running_process

    if (running_process.process_num != -1) {
      // if it has completed
      if (p.arrival + p.burst <= sec) {
        cout << running_process.process_num << " has completed at " << sec
             << '\n';
        finishing_times[running_process.process_num] = sec;
        arrival_time_map.erase(p.arrival);
        running_process = process();
      } else if (sec - running_process.started_time ==
                 queue_quantum[running_process.q_num -
                               1]) { // if quanta has completed
        cout << running_process.process_num << " has completed one quantum at "
             << sec << " from queue " << running_process.q_num << '\n';
        arrival_time_map[sec] = process(p.process_num, p.q_num, sec,
                                        p.burst - queue_quantum[p.q_num - 1]);
        if (running_process.q_num == 1) {
          Q1.push(
              process(p.process_num, p.q_num, sec, p.burst - queue_quantum[0]));
        } else {
          Q2.push(
              process(p.process_num, p.q_num, sec, p.burst - queue_quantum[1]));
        }
        running_process = process();
      }
    }
    // this means there's a process arriving a time sec
    if (arrival_time_map.find(sec) != arrival_time_map.end()) {
      if (running_process.process_num != -1) { // some process is running
        if (p.q_num == 2) { // this is the case when q2 is running but a process
          // arrives for q1
          if (arrival_time_map[sec].q_num == 1) {
            cout << p.process_num << " has preempted at " << sec
                 << " and pushed to Q2 again\n";
            Q2.push(process(p.process_num, p.q_num, sec,
                            (p.burst + p.started_time) - sec));
            running_process = process();
          }
        }
      }

      if (arrival_time_map[sec].q_num == 1)
        Q1.push(arrival_time_map[sec]);
      else
        Q2.push(arrival_time_map[sec]);
      arrival_time_map.erase(sec);
    }

    // means no running process
    if (running_process.process_num == -1) {
      if (!Q1.empty()) {
        running_process = Q1.top();
        Q1.pop();
        cout << running_process.process_num << " has started at " << sec
             << "\n";
        running_process.started_time = sec;
      } else if (!Q2.empty()) {
        running_process = Q2.top();
        Q2.pop();
        cout << running_process.process_num << " has started at " << sec
             << "\n";
        running_process.started_time = sec;
        waitings[running_process.process_num] = sec - running_process.arrival;
      }
    }
    if (running_process.process_num == -1 && arrival_time_map.empty())
      break;

    sec++;
  }

  int total_turn = 0;
  cout << "Turnaround times:\n";
  for (auto &x : arrivals) {
    cout << x.first << ' ' << finishing_times[x.first] - x.second << '\n';
    total_turn += (finishing_times[x.first] - x.second);
  }
  cout << "Total turnaround time = " << total_turn << '\n';

  int total_wait = 0;
  cout << "Waiting times:\n";
  for (auto &x : arrivals) {
    cout << x.first << ' ' << waitings[x.first] << '\n';
    total_wait += (waitings[x.first]);
  }
  cout << "Total waiting time = " << total_wait << '\n';
}
