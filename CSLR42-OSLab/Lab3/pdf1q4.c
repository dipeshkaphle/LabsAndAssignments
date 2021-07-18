#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
void print_all_primes(int n) {
  printf("From pid %d, Printing all the primes till %d\n", getpid(), n);
  if (n < 0) {
    printf("Invalid number %d\n", n);
    exit(1);
  }
  int isPrime = 1;
  for (int i = 2; i < n; i++) {
    isPrime = 1;
    for (int j = 2; j < i; j++) {
      if (i % j == 0) {
        isPrime = 0;
        break;
      }
    }
    if (isPrime)
      printf("%d\n", i);
  }
  exit(0);
}
int main(int argc, char *argv[]) {
  int status;
  if (fork() == 0) {
    if (argc <= 1) {
      printf("No argument provided to the program\n");
      exit(1);
    }
    print_all_primes(atoi(argv[1]));
  } else {
    wait(&status);
    printf("Child process exited with %d\n", status);
  }
}
