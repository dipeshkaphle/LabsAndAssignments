#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void *print_all_odds(void *param) {
  int n = *((int *)param);
  for (int i = 1; i <= n; i += 2) {
    printf("Odd: %d\n", i);
  }
  return NULL;
}
void *print_all_evens(void *param) {
  int n = *((int *)param);
  for (int i = 2; i <= n; i += 2) {
    printf("Even: %d\n", i);
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Wrong number of arguments received\n");
    exit(1);
  }
  int n = atoi(argv[1]);
  pthread_t thread1, thread2;
  pthread_create(&thread1, NULL, print_all_odds, &n);
  pthread_create(&thread2, NULL, print_all_evens, &n);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
}
