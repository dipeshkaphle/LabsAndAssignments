#include <ctype.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define WRITE_END 1
#define READ_END 0

int main() {
  sem_t *sem1 = (sem_t *)mmap(0, sizeof(sem_t), PROT_READ | PROT_WRITE,
                              MAP_ANONYMOUS | MAP_SHARED, 0, 0);

  sem_t *sem2 = (sem_t *)mmap(0, sizeof(sem_t), PROT_READ | PROT_WRITE,
                              MAP_ANONYMOUS | MAP_SHARED, 0, 0);
  sem_init(sem1, 1, 0);
  sem_init(sem2, 2, 0);
  int fd[2];
  if (pipe(fd) == -1) {
    printf("Error in initiating the pipe\n");
    exit(1);
  }

  pid_t pid = fork();
  if (pid < 0) {
    printf("Couldnt fork\n");
    exit(2);
  }
  if (pid == 0) {
    sem_wait(sem1);
    char str2[1024];
    read(fd[READ_END], str2, 1024);
    close(fd[READ_END]);
    printf("Received data in child process\n");
    fflush(stdout);
    int len = strlen(str2);
    int count = 0;
    for (int i = 0; i < len; i++) {
      char c = str2[i];
      if (isalpha(c)) {
        c = tolower(c);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
          count++;
        }
      }
    }
    char str3[1024];
    sprintf(str3, "The number of vowels is %d\n", count);
    write(fd[WRITE_END], str3, strlen(str3));
    printf("Sent no of vowels to parent process\n");
    fflush(stdout);
    close(fd[WRITE_END]);
    sem_post(sem2);
    exit(0);

  } else {

    char str[1024] = "A quick brown fox jumps over the lazy dog";
    write(fd[WRITE_END], str, strlen(str));
    close(fd[WRITE_END]);
    printf("Sent a string from parent process: %s\n\n", str);
    fflush(stdout);
    if (sem_post(sem1) == -1) {
      printf("Failed to post\n");
      exit(0);
    }
    fflush(stdout);
    sem_wait(sem2);
    char str4[1024];
    str4[read(fd[READ_END], str4, 1023)] = 0;
    printf("%s", str4);
    fflush(stdout);
    close(fd[READ_END]);
  }
  wait(NULL);
  exit(0);
}
