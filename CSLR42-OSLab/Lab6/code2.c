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
  printf("IO started at %d for process %d\n", p.start_time, p.process->id);
  fflush(stdout);
  usleep(p.process->io_burst * 100);
  printf("IO finished at %d for process %d\n",
         p.start_time + p.process->io_burst, p.process->id);
  fflush(stdout);
  p.process->io_burst = 0;
  p.process->time_quanta -= 5;
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
  /* u_int32_t time_quanta = 50; */
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
    queue[l]->time_quanta = min(queue[l]->time_quanta + 10, 100);
    queue[l]->cpu_burst -= runtime;
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
      l++;
    }
    fflush(stdout);
  }
}
