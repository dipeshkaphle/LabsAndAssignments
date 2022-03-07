#include "mbed.h"
PwmOut led(p5);
PwmOut speaker(p21);
int main() {
  int inc = 1;
  while (1) {
    led = led + inc * 0.10;
    speaker = speaker + inc * 0.10;
    printf("LEDs are now %.2f, and speaker is %.2f\n", led.read(),
           speaker.read());
    wait(0.5);
    if (led == 1.0) {
      inc = -1;
    }
    if (led == 0) {
      inc = 1;
    }
  }
}
