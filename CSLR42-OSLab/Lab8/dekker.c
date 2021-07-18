#include <assert.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct {
  atomic_bool wants_to_enter[2];
  atomic_int turn;
} dekker_lock_t;

typedef struct {
  int *counter;
  dekker_lock_t *lock;
  int p; // process number basically (can be 0 or 1 only)
} thread_func_arg;

void lock_init(dekker_lock_t *lock) {
  lock->wants_to_enter[0] = FALSE;
  lock->wants_to_enter[1] = FALSE;
  lock->turn = 0;
}

// Dekker algorithm, for p=0, it acts as process 0 and for p=1,as process 1
//
void dekker_exec(dekker_lock_t *lock, int p, void (*func)(void *), void *arg) {
  assert(p == 1 || p == 0); // ensures the process count is binary
  lock->wants_to_enter[p] = TRUE;
  while (lock->wants_to_enter[!p]) {
    if (lock->turn != p) {
      lock->wants_to_enter[p] = FALSE;
      while (lock->turn != p) {
      }
      lock->wants_to_enter[p] = TRUE;
    }
  }
  // Will be executed exclusively
  // Critical Section
  func(arg);
  // Critical section ens
  lock->turn = !p;
  lock->wants_to_enter[p] = FALSE;
}
void increment(void *num) { (*(int *)num)++; }
void *count(void *param) {
  thread_func_arg *arg = (thread_func_arg *)param;
  for (int i = 0; i < 1000000; i++) {
    dekker_exec(arg->lock, arg->p, increment, arg->counter);
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
  dekker_lock_t lock;
  lock_init(&lock);
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
  printf("With dekker: %d\n", counter);
  printf("Without dekker: %d\n", counter2);
}
