#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define R 3
#define P 3

int done[P];

void init_done() {
  for (int i = 0; i < P; i++)
    done[i] = -1;
}

int is_request_satisfied(int req[R], int avail[R]) {
  for (int i = 0; i < R; i++) {
    if (avail[i] < req[i]) {
      return 0;
    }
  }
  return 1;
}

int get_first_available(int need[P][R], int avail[R]) {
  for (int i = 0; i < P; i++) {
    if (done[i] == -1 && is_request_satisfied(need[i], avail)) {
      return i;
    }
  }
  printf("\n\n-->The available resource is not enough for any processes need.");
  printf("-->So our system is in unsafe state\n");
  exit(1);
}

void fill_need_matrix(int alloc[P][R], int max[P][R], int need[P][R]) {
  for (int i = 0; i < P; i++) {
    for (int j = 0; j < R; j++) {
      need[i][j] = max[i][j] - alloc[i][j];
    }
  }
}

void print_current_state(int alloc[P][R], int max[P][R], int need[P][R],
                         int avail[R]) {
  printf("Currently Available: ");
  for (int i = 0; i < R; i++) {
    printf("%-4d", avail[i]);
  }
  printf("\n\n");
  char fmt_str[100];
  // Decoration at top
  sprintf(fmt_str, "%%-8s|%%-%ds|%%-%ds|%%-%ds|%%s\n", R * 4, R * 4, R * 4);
  printf(fmt_str, "Name", "Allocation", "Max", "Need", "Order");

  // 2nd line
  printf("%-8s|", "");
  char c = 'A';
  for (int i = 0; i < R; i++)
    printf("%-4c", c++);
  printf("|");
  c = 'A';
  for (int i = 0; i < R; i++)
    printf("%-4c", c++);
  printf("|");
  c = 'A';
  for (int i = 0; i < R; i++)
    printf("%-4c", c++);
  printf("|\n");
  for (int i = 0; i <= (3 * R * 4 + 8 + 10); i++)
    printf("-");
  printf("\n");

  // main content
  for (int i = 0; i < P; i++) {
    char str[10];
    sprintf(str, "P%d", i + 1);
    printf("%-8s|", str);
    for (int j = 0; j < R; j++)
      printf("%-4d", alloc[i][j]);
    printf("|");
    for (int j = 0; j < R; j++)
      printf("%-4d", max[i][j]);
    printf("|");
    for (int j = 0; j < R; j++)
      printf("%-4d", need[i][j]);
    printf("|");
    printf(" %-4d\n", done[i]);
  }
  printf("\n");
}

void show_avail_update(int alloc[P][R], int avail[R], int i) {
  printf("---> New Available = ");
  printf("(");
  for (int j = 0; j < R; j++) {
    printf("%d%c ", avail[j], j == (R - 1) ? ' ' : ',');
  }
  printf(") + (");
  for (int j = 0; j < R; j++) {
    printf("%d%c ", alloc[i][j], j == (R - 1) ? ' ' : ',');
    avail[j] += (alloc[i][j]);
  }
  printf(")\n");
  printf("---> New Available = ");
  printf("(");
  for (int j = 0; j < R; j++) {
    printf("%d%c ", avail[j], j == (R - 1) ? ' ' : ',');
  }
  printf(")\n");
}

void print_safe() {
  printf("SAFE SEQUENCE : ");
  for (int i = 1; i <= P; i++) {
    for (int j = 0; j < P; j++) {
      if (done[j] == i) {
        printf("P%d   ", j + 1);
      }
    }
  }
  printf("\n\n");
}

void banker(int alloc[P][R], int max[P][R], int need[P][R], int avail[R]) {
  print_current_state(alloc, max, need, avail);
  printf("\n\n\n");
  for (int i = 1; i <= P; i++) {
    printf("---------------Iteration %d--------------------\n", i);
    int available = get_first_available(need, avail);
    done[available] = i;
    // updating available
    print_current_state(alloc, max, need, avail);
    printf("---> Allocated to P%d\n", available + 1);
    show_avail_update(alloc, avail, available);
    printf("\n\n");
  }
  print_safe();
}

int main() {
  init_done();
  int avail[R] = {2, 3, 0};

  int alloc[P][R] = {{2, 2, 3}, {2, 0, 3}, {1, 2, 4}};

  int max[P][R] = {{3, 6, 8}, {4, 3, 3}, {3, 4, 4}};
  int need[P][R];
  fill_need_matrix(alloc, max, need);
  banker(alloc, max, need, avail);
}
