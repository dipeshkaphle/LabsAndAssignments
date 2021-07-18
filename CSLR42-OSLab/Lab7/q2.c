#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define M 3
#define N 4
#define P 2

int A[M][N];
int B[N][P];
int C[M][P];

struct Arg {
  int row_num;
};

void *get_row(void *p) {
  struct Arg *arg = p;
  for (int i = 0; i < P; i++) {
    C[arg->row_num][i] = 0;
    for (int j = 0; j < N; j++) {
      C[arg->row_num][i] += (A[arg->row_num][j] * B[j][i]);
    }
  }
}

int main() {
  struct Arg args_arr[M];
  pthread_t threads[M];
  srand(time(0));
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      A[i][j] = rand() % 10;
    }
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < P; j++) {
      B[i][j] = rand() % 10;
    }
  }

  printf("Matrix A\n");
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      printf("%2d ", A[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  printf("Matrix B\n");
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < P; j++) {
      printf("%2d ", B[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  for (int i = 0; i < M; i++) {
    args_arr[i] = (struct Arg){i};
    pthread_create(&threads[i], NULL, get_row, &args_arr[i]);
  }
  for (int i = 0; i < M; i++) {
    pthread_join(threads[i], NULL);
  }
  printf("The result of multiplication is , Matrix C:\n");
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < P; j++) {
      printf("%4d ", C[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}
