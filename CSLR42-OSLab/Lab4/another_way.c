#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#define PAGE_SIZE 4096

int main() {
  // creates if it doesnt exist
  int shm_fd = shm_open("/array", O_CREAT | O_RDWR | O_EXCL, 0666);
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
  printf("\n\n\n\n");

  // cons1
  if (fork() == 0) {
    printf("THE SUM OF ALL THE ELEMENTS: ");
    int sum = 0;
    for (int i = 0; i < PAGE_SIZE / sizeof(int); i++) {
      sum += arr[i];
    }
    printf("%d\n", sum);
    exit(0);
  }
  wait(NULL);
  printf("\n\n\n\n");
  // cons2
  if (fork() == 0) {
    int sum = 0;
    double mean, standard_dev_numerator = 0, standard_dev;
    for (int i = 0; i < PAGE_SIZE / sizeof(int); i++) {
      sum += arr[i];
    }
    mean = ((double)sum) / (double)(PAGE_SIZE / sizeof(int));
    printf("THE MEAN IS %f\n", mean);
    for (int i = 0; i < PAGE_SIZE / sizeof(int); i++) {
      standard_dev_numerator += pow((double)arr[i] - mean, 2);
    }
    printf("THE numerator IS %f\n", standard_dev_numerator);
    standard_dev =
        sqrt((standard_dev_numerator / (double)(PAGE_SIZE / sizeof(int))));
    printf("THE STANDARD DEVIATION IS : %f\n", standard_dev);
    exit(0);
  }
  close(shm_fd);
  munmap(arr, PAGE_SIZE);
  shm_unlink("/array");
}
