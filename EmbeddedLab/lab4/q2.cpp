#include "mbed.h"
PwmOut speaker(p21);
int main() {
  while (1) {
    // Can use ticker as well
    wait_ms(5000);
    printf("Speaker will beep twice now \n\n");
    speaker = 0.5;
    wait_ms(50);
    printf("Speaker: %.2f\n", speaker.read());
    speaker = 0;
    wait_ms(50);
    speaker = 0.5;
    wait_ms(50);
    printf("Speaker: %.2f\n", speaker.read());
    speaker = 0;
  }
}
