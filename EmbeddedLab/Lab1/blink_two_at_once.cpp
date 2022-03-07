#include "mbed.h"

BusOut myleds(LED1, LED2, LED3, LED4);

int main() {
  while (1) {
    // 1010
    // 0101
    int arr[] = {10, 5};
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
      myleds = arr[i];
      wait(1);
    }
  }
}
