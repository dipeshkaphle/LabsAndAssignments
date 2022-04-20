#include "mbed.h"
BusOut myleds(LED1, LED2, LED3, LED4);
InterruptIn button(p5);
void hex_counter() {
  printf("button Raised");
  while (1) {
    for (int i = 0; i < 16; i++) {
      myleds = i;
      printf("Hex counter: %d\n", i);
      wait(0.5);
    }
  }
}
void dec_counter() {
  printf("button Fallen");
  while (1) {
    for (int i = 0; i < 10; i++) {
      myleds = i;
      printf("Decade counter: %d\n", i);
      wait(0.5);
    }
  }
}
int main() {
  button.rise(&hex_counter);
  button.fall(&dec_counter);
}
