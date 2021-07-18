#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define min(x, y) x > y ? y : x

pthread_mutex_t lock;

struct process_detail {
  u_int32_t id;
  u_int32_t arrival;
  u_int32_t cpu_burst;
  u_int32_t io_burst;
  u_int32_t priority;
  u_int32_t time_quanta;
  u_int32_t finish_time;
};

struct process_detail *queue[1000];

struct process_detail_for_io_exec {
  struct process_detail *process;
  u_int32_t start_time;
};

struct process_add_timer {
  struct process_detail *process;
  u_int32_t *r;
};

void *put_in_queue(void *data) {
  struct process_add_timer *p = (struct process_add_timer *)data;
  usleep(p->process->arrival * 100);
  pthread_mutex_lock(&lock);
  queue[(*(p->r))++] = p->process;

  pthread_mutex_unlock(&lock);
  printf("Process %d pushed to the end of the queue at %d time \n",
         p->process->id, p->process->arrival);
  fflush(stdout);
}

void *sleep_func(void *param) {
  struct process_detail_for_io_exec p;
  memcpy(&p, param, sizeof(struct process_detail_for_io_exec));
  u_int32_t runtime = min(p.process->io_burst, p.process->time_quanta);
  printf("IO burst started at %d for process %d\n", p.start_time,
         p.process->id);
  fflush(stdout);
  usleep(p.process->io_burst * 100);
  printf("IO burst finished at %d for process %d\n", p.start_time + runtime,
         p.process->id);
  fflush(stdout);
  p.process->io_burst -= runtime;
  p.process->time_quanta -= 5;
  if (p.process->cpu_burst == 0 && p.process->io_burst == 0) {
    printf("Process %d has completed IO and CPU burst and is no more active\n",
           p.process->id);
    p.process->finish_time = p.start_time + runtime;
  }
  return NULL;
}

int main() {
  pthread_t threads[100];
  int thread_count = 0;

  struct process_detail p1 = {1, 0, 120, 10, 5, 50, 0};
  struct process_detail p2 = {2, 0, 55, 45, 5, 50, 0};
  struct process_detail p3 = {3, 0, 150, 10, 5, 50, 0};
  struct process_detail p4 = {4, 0, 65, 35, 5, 50, 0};
  struct process_detail p5 = {5, 320, 25, 30, 5, 50, 0};

  queue[0] = &p1;
  queue[1] = &p2;
  queue[2] = &p3;
  queue[3] = &p4;
  u_int32_t l = 0;
  u_int32_t r = 4;
  u_int32_t seconds = 0;
  u_int32_t last_stop = 0;

  struct process_add_timer p = {&p5, &r};
  // create a thread which will put process 5 to the queue
  pthread_create(threads + (thread_count++), NULL, put_in_queue, &p);

  int io = 0;
  while (r != l) {

    u_int32_t runtime = min(queue[l]->cpu_burst, queue[l]->time_quanta);

    seconds += runtime;
    usleep(runtime * 100);
    queue[l]->time_quanta =
        min(queue[l]->time_quanta + (runtime == queue[l]->time_quanta ? 10 : 0),
            100);
    queue[l]->cpu_burst -= runtime;
    queue[l]->priority++;
    printf("Process %d executed for %d time(starting: %d, end:%d)\n ",
           queue[l]->id, runtime, seconds - runtime, seconds);
    fflush(stdout);

    if (queue[l]->io_burst) {
      struct process_detail_for_io_exec data = {queue[l], seconds};
      pthread_create(threads + thread_count, NULL, sleep_func, &data);
      thread_count++;
    }

    if (queue[l]->cpu_burst) {
      printf("   Process %d pushed back to the queue\n", queue[l]->id);
      queue[r++] = queue[l++];
    } else {
      printf("   CPU Execution time for process %d is over\n", queue[l]->id);
      // if io_burst and cpu_burst both completed process is done
      if (queue[l]->io_burst == 0) {
        printf(
            "    Process %d has completed IO and CPU burst and is no more in "
            "queue\n",
            queue[l]->id);
        queue[l]->finish_time = seconds;
      }
      l++;
    }
    fflush(stdout);
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
