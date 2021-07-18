#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int fd;

void handler(int sig) {
  int res = write(fd, "exit", strlen("exit"));
  exit(0);
}

int main() {
  signal(SIGINT, handler);
  printf("Opening named pipe /tmp/my_fifo...");
  fflush(stdout);
  // F_OK means file exists
  if (access("/tmp/my_fifo", F_OK) == 0) {
    fd = open("/tmp/my_fifo", O_WRONLY);
    if (fd == -1) {
      printf("Failed to open named pipe");
      exit(4);
    } else {
      printf("...done\n");
    }
  } else {
    printf("Pipe doesnt exist yet\n");
    exit(3);
  }

  char buf[1024];
  while (1) {
    printf("Enter input: ");
    fflush(stdout);
    buf[read(0, buf, 1023) - 1] = 0;

    /* scanf(" %1023s", buf); */
    printf("Writing buffer to pipe...");
    fflush(stdout);
    int res = write(fd, buf, strlen(buf));
    if (res == -1) {
      printf("Couldnt write to the pipe\n");
      exit(1);
    } else {
      printf("done\n");
    }
    if (strcmp(buf, "exit") == 0) {
      close(fd);
      exit(0);
    }
  }
}
