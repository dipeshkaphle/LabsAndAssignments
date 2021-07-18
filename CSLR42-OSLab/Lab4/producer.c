#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#define PAGE_SIZE 4096
int main() {
  // creates if it doesnt exist
  int shm_fd = shm_open("/array", O_CREAT | O_RDWR | O_EXCL, 0664);
  if (shm_fd == -1) {
    printf("Failed to create or the object already exist\n");
    exit(1);
  }
  ftruncate(shm_fd, PAGE_SIZE);
  // shared memory is mapped to some heap memory with mmap, it has READ and
  // WRITE priviliges It is shared as well indicated by MAP_SHARED
  int *arr =
      mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (arr == MAP_FAILED) {
    printf("mmap failed\n");
    exit(2);
  }
  printf("BEFORE:\n");
  for (int i = 0; i < (PAGE_SIZE / sizeof(int)); i++)
    printf("%x ", arr[i]);
  for (int i = 0; i < PAGE_SIZE / sizeof(int); i++)
    arr[i] = i;
  printf("\nAFTER:\n");
  for (int i = 0; i < (PAGE_SIZE / sizeof(int)); i++)
    printf("%x ", arr[i]);
  printf("\n");
  close(shm_fd);
  munmap(arr, PAGE_SIZE);
}
