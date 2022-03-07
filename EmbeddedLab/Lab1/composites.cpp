#include "mbed.h"

BusOut myleds(LED1, LED2, LED3, LED4);

bool isComposite(int n) {
  if (n == 1)
    return false;
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0)
      return true;
  }
  return false;
}

int main() {
  while (1) {
    for (int i = 1; i < 16; i++) {
      if (isComposite(i)) {
        myleds = i;
        wait(1);
      }
    }
  }
}
