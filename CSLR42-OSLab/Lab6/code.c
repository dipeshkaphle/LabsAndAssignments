#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

struct process_detail {
  u_int32_t id;
  u_int32_t arrival;
  u_int32_t cpu_burst;
  u_int32_t io_burst;
  u_int32_t priority;
  u_int32_t time_quanta;
  u_int32_t finish_time;
};

int main() {
  struct process_detail p1 = {1, 0, 120, 10, 5, 50, 0};
  struct process_detail p2 = {2, 0, 55, 45, 5, 50, 0};
  struct process_detail p3 = {3, 0, 150, 10, 5, 50, 0};
  struct process_detail p4 = {4, 0, 65, 35, 5, 50, 0};
  struct process_detail p5 = {5, 320, 25, 30, 5, 50, 0};

  struct process_detail *queue[1000] = {NULL};
  queue[0] = &p1;
  queue[1] = &p2;
  queue[2] = &p3;
  queue[3] = &p4;
  int l = 0;
  int r = 4;
  /* u_int32_t time_quanta = 50; */
  u_int32_t seconds = 0;
  u_int32_t last_stop = 0;

  int io = 0;
  while (r != l) {

    if (queue[l]->cpu_burst) {
      // we'll finish the cpu burst first
      queue[l]->cpu_burst--;
    } else {
      // then we move on to io_burst
      if (queue[l]->io_burst) {
        queue[l]->io_burst--;
        io = 1;
      } else {
        // if there's no io_burst as well, we don't put the process in queue
        // anymore as it is finished
        queue[l]->finish_time = seconds;
        last_stop = seconds;
        printf("Process %d finished at %d time unit with%s\n", queue[l]->id,
               queue[l]->finish_time, (io == 0) ? "out IO" : " IO");
        io = 0;
        l++;
        continue;
      }
    }

    seconds++;

    if (seconds == 320) {
      queue[r++] = &p5;
      printf("Process %d pushed to the end of queue at %d\n", queue[r - 1]->id,
             queue[r - 1]->arrival);
    }
    // if the time quanta is finished
    if (seconds - last_stop == queue[l]->time_quanta) {
      printf("Process %d executed for one time quanta of %d time unit(with%s), "
             "pushed "
             "back to the end of queue at %d\n",
             queue[l]->id, queue[l]->time_quanta, (io == 0) ? "out IO" : " IO",
             seconds);
      if (io) {
        queue[l]->time_quanta -= 5;
      } else {
        queue[l]->time_quanta += (queue[l]->time_quanta == 100 ? 0 : 10);
      }
      queue[r++] = queue[l++];
      last_stop = seconds;
    }
  }
  printf("\n\n\n");
  struct process_detail *all_processes[5] = {&p1, &p2, &p3, &p4, &p5};

  double turnaroundtime = 0;
  for (int i = 0; i < 5; i++) {
    printf("Process %d arrived at %d and finished at %d\n",
           all_processes[i]->id, all_processes[i]->arrival,
           all_processes[i]->finish_time);
    turnaroundtime +=
        (all_processes[i]->finish_time - all_processes[i]->arrival);
  }
  printf("\nThe average turnaroundtime is %f\n", turnaroundtime / 5);
}
