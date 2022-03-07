#include "mbed.h"
BusOut myleds(LED1, LED2, LED3, LED4);
Ticker tk;
Timeout to;
int curr = 0;
void oct_counter() {
  myleds = curr;
  printf("%d \n", curr);
  curr += 1;
  curr %= 8;
}
void reset() {
  curr = 0;
  printf("Resetted to 0\n");
}
int main() {
  tk.attach(&oct_counter, 1.0);
  to.attach(&reset, 10.0);
}
