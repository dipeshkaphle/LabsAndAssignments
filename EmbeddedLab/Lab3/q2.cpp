#include "mbed.h"
PwmOut led(p5);
AnalogIn p(p15);
int main() {
  while (1) {
    led = p.read();
    printf("LED is now %.2f\n", led.read());
    wait(0.5);
  }
}
