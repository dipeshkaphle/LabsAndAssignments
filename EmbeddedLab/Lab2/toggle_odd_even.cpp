#include "mbed.h"
BusOut myleds(LED1, LED2, LED3, LED4);
InterruptIn btn(p5);
Ticker tk;
Timeout to;
int odd = 1;
const char *cntr_type = "Odd";
int val = 1;
void counter() {
  myleds = val;
  printf("%s: %d \n", cntr_type, val);
  val += 2;
  val %= 16;
}
void change_type() {
  printf("changed type using button \n");
  if (odd) {
    odd = 0;
    val = 0;
    cntr_type = "Even";
  } else {
    odd = 1;
    val = 1;
    cntr_type = "Odd";
  }
}
void reset() {
  printf("reseting the values after timeout \n");
  odd = 0;
  val = 0;
  cntr_type = "Even";
}
int main() {
  tk.attach(&counter, 1.0);
  btn.rise(&change_type);
  btn.fall(&change_type);
  to.attach(&reset, 10.0);
}
