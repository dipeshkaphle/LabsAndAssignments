#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();
  int status;

  if (pid == 0) {
    // will be executed by child process
    printf("=============================================================\n");
    printf("With execlp\n");
    execlp("ls", "ls", "-l", "-a", NULL);

  } else {
    // code executed by parent process;
    wait(&status);
    printf("Child exited with status %d\n", status);
  }
  if (fork() == 0) {
    printf("=============================================================\n");
    printf("With execl\n");
    execl("/bin/ls", "ls", "-l", "-a", NULL);
  } else {
    wait(&status);
    printf("Child exited with status %d\n", status);
  }
  if (fork() == 0) {
    printf("=============================================================\n");
    printf("With execvp\n");
    char *args[] = {"ls", "-la", NULL};
    execvp("ls", args);
  } else {
    wait(&status);
    printf("Child exited with status %d\n", status);
  }
  if (fork() == 0) {
    printf("=============================================================\n");
    printf("With execv\n");
    char *args[] = {"ls", "-la", NULL};
    execv("/bin/ls", args);
    printf("=============================================================\n");
  } else {
    wait(&status);
    printf("Child exited with status %d\n", status);
  }
}
