#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define max(a, b) a > b ? a : b
#define arr_size 100
struct arg {
  int *arr;
  int l;
  int r;
};
struct arr_and_size {
  int *arr;
  int size;
};
void *get2ndMax(void *p) {
  struct arr_and_size *Arg = p;
  int max1 = INT_MIN + 1;
  int max2 = INT_MIN;
  for (int i = 0; i < Arg->size; i++) {
    if (Arg->arr[i] > max1) {
      max2 = max1;
      max1 = Arg->arr[i];
    } else {
      if (Arg->arr[i] > max2 && Arg->arr[i] != max1) {
        max2 = Arg->arr[i];
      }
    }
  }
  int *res = malloc(sizeof(int));
  *res = max2;
  return res;
}

void *sum(void *p) {
  int *val1;
  int *val2;
  struct arg *Arg = p;
  if (Arg->r - Arg->l == 1) {
    val1 = malloc(sizeof(int));
    *val1 = Arg->arr[Arg->l];
    return val1;
  }
  int m = Arg->l + (Arg->r - Arg->l) / 2;
  pthread_t p1, p2;
  struct arg arg1 = {.arr = Arg->arr, .l = Arg->l, .r = m};
  struct arg arg2 = {.arr = Arg->arr, .l = m, .r = Arg->r};
  pthread_create(&p1, NULL, sum, &arg1);
  pthread_create(&p2, NULL, sum, &arg2);
  pthread_join(p1, (void **)&val1);
  pthread_join(p2, (void **)&val2);
  (*val1) += (*val2);
  free(val2);
  return val1;
}

int main() {
  int arr[arr_size];
  /* int arr[5] = {1, 2, 3, 4, 5}; */
  srand(time(0));
  for (int i = 0; i < arr_size; i++) {
    arr[i] = rand() % 100;
    printf("%d ", arr[i]);
  }
  printf("\n");
  struct arg Arg = (struct arg){arr, 0, arr_size};
  struct arr_and_size Arg2 = (struct arr_and_size){arr, arr_size};
  pthread_t p, q;
  pthread_create(&q, NULL, get2ndMax, &Arg2);
  pthread_create(&p, NULL, sum, &Arg);
  int *ans, *max2;
  pthread_join(p, (void **)&ans);
  pthread_join(q, (void **)&max2);
  printf("Sum : %d, 2nd max: %d\n", *(int *)(ans), *(int *)(max2));
  free(ans);
  free(max2);
}
