#include <assert.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct {
  atomic_bool flags[2];
  atomic_int turn;
} petersons_lock_t;

typedef struct {
  int *counter;
  petersons_lock_t *lock;
  int p; // process number basically (can be 0 or 1 only)
} thread_func_arg;

void petersons_lock_init(petersons_lock_t *lock) {
  lock->flags[0] = FALSE;
  lock->flags[1] = FALSE;
  lock->turn = 0;
}

// This is similar to given in wikipedia
// The p value controls whether this is process 0 or process 1
void peterson_exec(petersons_lock_t *lock, int p, void (*func)(void *),
                   void *arg) {
  assert(p == 0 || p == 1);
  lock->flags[p] = TRUE;
  lock->turn = !p;
  while (lock->flags[!p] == TRUE && lock->turn == (!p)) {
  }
  // Critical section
  // Will executer without disturbance
  func(arg);
  // End of critical section
  lock->flags[p] = FALSE;
}

void increment(void *num) { (*(int *)num)++; }

void *count(void *param) {
  thread_func_arg *arg = param;
  for (int i = 0; i < 1000000; i++) {
    // this will ensure perfect syncronization between two threads that will be
    // incrementing the same arg->counter variable
    peterson_exec(arg->lock, arg->p, increment, arg->counter);
  }
  return NULL;
}
void *count_without_lock(void *arg) {
  for (int i = 0; i < 1000000; i++) {
    (*(int *)arg)++;
  }
  return NULL;
}

int main() {

  pthread_t p1, p2, p3, p4;
  petersons_lock_t lock;
  petersons_lock_init(&lock);
  int counter = 0, counter2 = 0;
  thread_func_arg arg1 = {.counter = &counter, .lock = &lock, .p = 0};
  thread_func_arg arg2 = {.counter = &counter, .lock = &lock, .p = 1};
  pthread_create(&p1, NULL, count, &arg1);
  pthread_create(&p2, NULL, count, &arg2);
  pthread_create(&p3, NULL, count_without_lock, &counter2);
  pthread_create(&p4, NULL, count_without_lock, &counter2);
  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  pthread_join(p3, NULL);
  pthread_join(p4, NULL);
  printf("With peterson :%d\n", counter);
  printf("Without peterson :%d\n", counter2);
}
