#include "mbed.h"
PwmOut led1(p5);
PwmOut led2(p6);
InterruptIn btn(p7);
AnalogIn p(p15);
#define MAX(x, y) x > y ? x : y
#define MIN(x, y) x > y ? y : x
void inc_dec_by_potentio() {
  led1 = 0;
  led2 = 1;
  while (1) {
    float rate = p.read();
    led1 = MIN(led1 + rate, 1);
    led2 = MAX(led2 - rate, 0);
    printf("Potentiometer: LED1 is now %.2f\n", led1.read());
    printf("Potentiometer: LED2 is now %.2f\n", led2.read());
    wait(1);
    if (led1 == 1) {
      led1 = 0;
    }
    if (led2 == 0) {
      led2 = 1;
    }
  }
}
void inc_dec() {
  led1 = 0;
  led2 = 1;
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
int main() {
  btn.rise(inc_dec_by_potentio);
  btn.fall(inc_dec);
}
// Interface switch, 2 LEDs, potentiometer with the mbed board.
// If the switch is on, control the intensity of the LEDs using
// potentiometer (one LED should be increasing and other should
// be decreasing at the rate given via potentiometer).
// If the switch is off, blink LEDs one at increasing rate and other at
// decreasing rate (same rate) and loop back.
