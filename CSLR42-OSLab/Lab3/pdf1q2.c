#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void print() {
  printf("\nProcess pid: %d, Parent's pid: %d , Process group id : %d\n",
         getpid(), getppid(), getpgrp());
  exit(0);
}
int main() {
  fork();
  fork();
  fork();
  print();
}
