#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#define PAGE_SIZE 4096
int main() {
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
  close(fd);
  munmap(arr, PAGE_SIZE);
}
