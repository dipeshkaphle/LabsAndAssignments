#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  printf("Creating named pipe '/tmp/my_fifo'..");
  int res = mkfifo("/tmp/my_fifo", 0666);
  if (res == -1) {
    printf("Named pipe creation failed\n");
    exit(2);
  } else {
    printf("done\n");
  }
  int fd = open("/tmp/my_fifo", O_RDONLY);
  if (fd == -1) {
    printf("Failed to open named pipe");
    exit(1);
  }
  char str[1024];
  while (1) {
    printf("Waiting for input..");
    fflush(stdout);
    fflush(stdout);
    int n_bytes = read(fd, str, 1024);
    str[n_bytes] = 0;
    printf("%s\n", str);
    if (strcmp(str, "exit") == 0) {
      close(fd);
      unlink("/tmp/my_fifo");
      exit(0);
    }
  }
}
