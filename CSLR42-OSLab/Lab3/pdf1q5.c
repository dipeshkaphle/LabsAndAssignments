#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (fork() == 0) {
    if (argc == 2) {
      printf("Executing from child process:\n");
      execl("/bin/ls", "ls", argv[1], NULL);
    } else if (argc == 1) {
      printf("Didnt receive directory name as argument\n");
      exit(1);
    } else {
      printf("To many arguments received. Expected only 1\n");
      exit(1);
    }
  } else {
    wait(NULL);
    printf("\nDone..\n");
  }
}
