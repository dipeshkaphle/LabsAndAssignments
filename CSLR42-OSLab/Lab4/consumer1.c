#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

#define PAGE_SIZE 4096

int main() {
  printf("THE SUM OF ALL THE ELEMENTS: ");
  int fd = shm_open("/array", O_RDONLY, 0444);
  if (fd == -1) {
    printf("Couldnt open shared memory\n");
    exit(1);
  }
  int *arr = mmap(NULL, PAGE_SIZE, PROT_READ, MAP_SHARED, fd, 0);
  if (arr == MAP_FAILED) {
    printf("mmap Failed\n");
    exit(2);
  }
  int sum = 0;
  for (int i = 0; i < PAGE_SIZE / sizeof(int); i++) {
    sum += arr[i];
  }
  printf("%d\n", sum);
}
