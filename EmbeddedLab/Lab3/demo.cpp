#include "mbed.h"
AnalogIn p(p15);
DigitalOut led(p5);
int main() {
  float var;
  while (1) {
    var = p.read();
    led = !led;
    printf("Blink! LED is now %d\n", led.read());
    wait(var);
  }
}
