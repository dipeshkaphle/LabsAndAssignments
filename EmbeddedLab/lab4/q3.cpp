#include "mbed.h"
PwmOut speaker(p21);
PwmOut led1(p6);
PwmOut led2(p7);
float delta = -0.1f;
InterruptIn btn(p5);
void pos() { delta = 0.1f; }
void neg() { delta = -0.1f; }
int main() {
  btn.rise(&pos);
  btn.fall(&neg);
  speaker = 0;
  while (1) {
    if (delta > 0 && speaker >= 1)
      speaker = 0;
    if (delta < 0 && speaker <= 0)
      speaker = 1;
    speaker = speaker + delta;
    led1 = speaker;
    led2 = speaker;
    wait(0.5);
  }
}
