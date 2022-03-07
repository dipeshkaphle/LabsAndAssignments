#include "mbed.h"
PwmOut led1(p5);
PwmOut led2(p6);
int main() {
  led2 = 1;
  led1 = 0;
  while (1) {
    led1 = led1 + 0.10;
    led2 = led2 - 0.10;
    printf("LED1 is now %.2f\n", led1.read());
    printf("LED2 is now %.2f\n", led2.read());
    wait(1);
    if (led1 == 1.0) {
      led1 = 0;
    }
    if (led2 == 0) {
      led2 = 1;
    }
  }
}
