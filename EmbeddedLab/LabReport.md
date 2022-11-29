---
<!-- title: Embedded Lab Report -->
<!-- author: 106119029 Dipesh Kafle -->
bibliography: "bibliography.bib"
link-citations: true
geometry: margin=2cm
<!-- toc: true -->
toc-depth: 2
header-includes: |
  \usepackage{fancyhdr}
  \pagestyle{fancy}
  \usepackage{graphicx}
  \usepackage{amsfonts} 
  \usepackage{amssymb}
  \usepackage{amsmath}
  \usepackage[colorlinks = true,
              linkcolor = blue,
              urlcolor  = blue]{hyperref}
  \usepackage[australian]{babel}
urlcolor: blue
---

<!-- #\tableofcontents# Lab 1

1. Blink LEDs in alternate order – 1 and 3 together and 2 and 4 together.
1. Blink LEDs – count from 1 to 15; if the board is counting odd value, wait for 1 sec, else wait for 2 sec.
1. Blink LEDs – for all composite number below 15.
1. Blink LEDs – to count even numbers

### 1.1

### Question

### Aim

### Code

### Output -->

<!-- # Lab 1/left Date: 31-01-2022 -->
<!-- <div align="center"># Lab 1</div> -->
<!-- \tableofcontents -->

\newcommand{\titlestr}{Embedded Systems Lab Report}
\newcommand{\authorstr}{Dipesh Kafle}
\begin{titlepage}
\centering
\includegraphics[width=0.35\textwidth]{./pics/NITT_logo.png}

\vspace{1cm}
{\LARGE \bf{\titlestr} \par}

\vspace{.5cm}
{\LARGE {\it{Embedded Systems Lab} \\ (CSLR 61)} \par}

\vspace{1cm}
{\Large \authorstr \par}

{\bf Roll No: 106119029}
\\
{\bf Class: CSE A}

\vspace{1cm}
\today

\vfill
\end{titlepage}

\newpage

<!-- \pagebreak -->

\setcounter{tocdepth}{2}
\tableofcontents

\newpage

| S.N | \centering Topic                                                                                                                                                                                                                                                                                                                                           | Date &nbsp; &nbsp;&nbsp; &nbsp;   | Lab |
| :-- | :--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | :------------------------------------------------------------------------------------------- | :------------- |
| 1   | Blink LEDs in alternate order – 1 and 3 together and 2 and 4 together.                                                                                                                                                                                                                                                                                     | 31-01-2022                                                                                   | 1              |
| 2   | Blink LEDs – count from 1 to 15; if the board is counting odd value, wait for 1 sec, else wait for 2 sec.                                                                                                                                                                                                                                                  | 31-01-2022                                                                                   | 1              |
| 3   | Blink LEDs – for all composite number below 15.                                                                                                                                                                                                                                                                                                            | 31-01-2022                                                                                   | 1              |
| 4   | Blink LEDs – to count even numbers                                                                                                                                                                                                                                                                                                                         | 31-01-2022                                                                                   | 1              |
| 5   | Switch between hex counter and decade counter using switches. Display the current value of the counter with the help of 4 LEDs and the screen. Libraries Used: InterruptIn, BusOut                                                                                                                                                                         | 07-02-2022                                                                                   | 2              |
| 6   | Display the octal counter using the onboard LEDs using Ticker Object; After 10 second, reset all the values of the onboard LED using Timeout Object. Libraries Used: TimeOut, Ticker                                                                                                                                                                       | 07-02-2022                                                                                   | 2              |
| 7   | Display the odd counter using the onboard LEDs and screen; After 10 seconds, reset all the values of the onboard LED and display even counter using Timeout Object. Give switch option to manually toggle between two counters. Libraries Used: InterruptIn, Ticker, TimeOut, BusOut                                                                       | 07-02-2022                                                                                   | 2              |
| 8   | Increase the intensity of one LED while descreasing the other LED's intensity at the same unit. Display the intensity value of the LEDs. Libraries Used: pwmout                                                                                                                                                                                            | 14-02-2022                                                                                   | 3              |
| 9   | Interface potentiometer with mbed board and based on the value of potentiometer, adjust the intensity of an external LED. Libraries To Be Used: pwmout, analogin                                                                                                                                                                                           | 14-02-2022                                                                                   | 3              |
| 10  | Interface switch, 2 LEDs, potentiometer with the mbed board. If the switch is on, control the intensity of the LEDs using potentiometer (one LED should be increasing and other should be decreasing at the rate given via potentiometer). If the switch is off, blink LEDs one at increasing rate and other at decreasing rate (same rate) and loop back. | 14-02-2022                                                                                   | 3              |
| 11  | Write a program to increase the intensity of external LED. At the same rate, increase the sound intensity of speaker.Libraries Used: pwmout                                                                                                                                                                                                                | 28-02-2022                                                                                   | 4              |
| 12  | Design an alarm system, which makes double beep sound for every 5s using a speaker. Libraries To Be Used: pwmout, analogin                                                                                                                                                                                                                                 | 28-02-2022                                                                                   | 4              |
| 13  | Have a switch, 2 LEDs and a speaker interfaced with mbed board. Upon switching on, the intensity of the sound should be increasing and the upon switching off, should make the intensity of the sound decreasing. Proportionally increase or decrease the intensity of two LEDs.                                                                           | 28-02-2022                                                                                   | 4              |
| 14  | Design a program to make ambulance sound.                                                                                                                                                                                                                                                                                                                  | 28-02-2022                                                                                   | 4              |
| 15  | Blink LEDs in alternate order – 1 and 3 together and 2 and 4 together.                                                                                                                                                                                                                                                                                     | 07-03-2022                                                                                   | 5              |
| 16  | Blink LEDs – count from 1 to 15; if the board is counting odd value, wait for 1 sec, else wait for 2 sec.                                                                                                                                                                                                                                                  | 07-03-2022                                                                                   | 5              |
| 17  | Blink LEDs – for all composite number below 15.                                                                                                                                                                                                                                                                                                            | 07-03-2022                                                                                   | 5              |
| 18  | Blink LEDs – to count even numbers                                                                                                                                                                                                                                                                                                                         | 07-03-2022                                                                                   | 5              |
| 19  | Interface an ultrasonic sensor and display the distance measured in a screen and glow red, blue and green led if the distance is close, moderate and far respectively. Play different tones for different cases.                                                                                                                                           | 28-03-2022                                                                                   | 6              |
| 20  | Interface a PIR sensor with Arduino and blink a led if any movement is captured by the sensor and count the number of movements. Make a buzzer when movement detected                                                                                                                                                                                      | 28-03-2022                                                                                   | 6              |
| 21  | Interface two 7-segment display with Arduino Uno board. Implement the a)odd counter and b)even counter and display the values in the seven segment display.                                                                                                                                                                                                | 11-04-2022                                                                                   | 7              |
| 22  | Interface the ambient light sensor with Arduino Uno board. Check the light value from the sensor, and switch on/off the bulb (based on the threshold value).                                                                                                                                                                                               | 11-04-2022                                                                                   | 7              |
| 23  | Interface the temperature and gas sensor with Arduino Uno board. Check the temperature and the gas value, if the limit is beyond the threshold, switch on the bulb and make alarm using buzzer.                                                                                                                                                            | 11-04-2022                                                                                   | 7              |
| 24  | Interface force sensor with Arduino board and display the amount of force given as input to sensor in LCD screen. Also, interface LED RGB and change color of the LED based on the some threshold values.                                                                                                                                                  | 18-04-2022                                                                                   | 8              |
| 25  | Interface the keypad and tilt sensor with Arduino board, if the sensor is being tilted, then take input from keypad and print it in the LCD.                                                                                                                                                                                                               | 18-04-2022                                                                                   | 8              |

\pagebreak

# Lab 1 \hfill Date: 31-01-2022

\lhead{Lab 1}
\rhead{Date: 31-01-2022}

### Questions

1. Blink LEDs in alternate order – 1 and 3 together and 2 and 4 together.
1. Blink LEDs – count from 1 to 15; if the board is counting odd value, wait for 1 sec, else wait for 2 sec.
1. Blink LEDs – for all composite number below 15.
1. Blink LEDs – to count even numbers

## \centering 1 Blink LEDs in alternate order – 1 and 3 together and 2 and 4 together.

### Question

Blink LEDs in alternate order – 1 and 3 together and 2 and 4 together.

### Aim

To blink LEDs in alternate order – 1 and 3 should blink together and 2 and 4 should blink together.

### Code

```cpp
#include "mbed.h"

BusOut myleds(LED1, LED2, LED3, LED4);

int main() {
  while (1) {
    // 1010
    // 0101
    int arr[] = {10, 5};
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
      myleds = arr[i];
      wait(1);
    }
  }
}
```

### Output

![](./pics/Lab1/q1.png)

![](./pics/Lab1/q1_2.png)

## \centering 2 Blink LEDs – count from 1 to 15; if the board is counting odd value, wait for 1 sec, else wait for 2 sec.

### Question

Blink LEDs – count from 1 to 15; if the board is counting odd value, wait for 1 sec, else wait for 2 sec.

### Aim

To blink LEDs and count from 1 to 15. If the board is counting odd value, it should wait for 1 sec, else it should wait for 2 sec.

### Code

```cpp
#include "mbed.h"

BusOut myleds(LED1, LED2, LED3, LED4);

int main() {
  while (1) {
    for (int i = 0; i < 16; i++) {
      myleds = i;
      if (i % 2 == 1) {
        printf("Waiting 1s for %d\n",i);
        wait(1);
      } else {
        printf("Waiting 2s for %d\n",i);
        wait(2);
      }
    }
  }
}
```

### Output

![](./pics/Lab1/q2.png)

## \centering 3 Blink LEDs – for all composite number below 15.

### Question

Blink LEDs – for all composite number below 15.

### Aim

To blink LEDs for all composite numbers below 15.

### Code

```cpp
#include "mbed.h"

BusOut myleds(LED1, LED2, LED3, LED4);

bool isComposite(int n) {
  if (n == 1)
    return false;
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0)
      return true;
  }
  return false;
}

int main() {
  while (1) {
    for (int i = 1; i < 16; i++) {
      if (isComposite(i)) {
        printf("%d\n",i);
        myleds = i;
        wait(1);
      }
    }
  }
}
```

### Output

![](./pics/Lab1/q3.png)

## \centering 4 Blink LEDs – to count even numbers

### Question

Blink LEDs – to count even numbers

### Aim

To blink LEDs to count even numbers

### Code

```cpp
#include "mbed.h"

BusOut myleds(LED1, LED2, LED3, LED4);

int main() {
  while (1) {
    for (int i = 0; i < 16; i += 2) {
      printf("%d\n", i);
      myleds = i;
      wait(0.5);
    }
  }
}
```

### Output

![](./pics/Lab1/q4.png)

\pagebreak

# Lab 2 \hfill Date: 07-02-2022

\lhead{Lab 2}
\rhead{Date: 07-02-2022}

### Questions

1. Switch between hex counter and decade counter using switches. Display the current value of the counter with the help of 4 LEDs and the screen. Libraries Used: InterruptIn, BusOut

1. Display the octal counter using the onboard LEDs using Ticker Object; After 10 second, reset all the values of the onboard LED using Timeout Object. Libraries Used: TimeOut, Ticker

1. Display the odd counter using the onboard LEDs and screen; After 10 seconds, reset all the values of the onboard LED and display even counter using Timeout Object. Give switch option to manually toggle between two counters. Libraries Used: InterruptIn, Ticker, TimeOut, BusOut

## \centering 5 Switch between hex counter and decade counter using switches. Display the current value of the counter with the help of 4 LEDs and the screen.

### Question

Switch between hex counter and decade counter using switches. Display the current value of the counter with the help of 4 LEDs and the screen. Libraries Used: InterruptIn, BusOut

### Aim

To switch between hex counter and decade counter using switches. It must display the current value of the counter with the help of 4 LEDs and the screen.

### Code

```cpp
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

```

### Output

![](./pics/Lab2/send2/1.png)

## \centering 6 Display the octal counter using the onboard LEDs using Ticker Object; After 10 second, reset all the values of the onboard LED using Timeout Object.

### Question

Display the octal counter using the onboard LEDs using Ticker Object; After 10 second, reset all the values of the onboard LED using Timeout Object. Libraries Used: TimeOut, Ticker

### Aim

To display the octal counter using the onboard LEDs using Ticker object. After 10 second, it must reset all the values of the onboard LED using timeout Object.

### Code

```cpp
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
```

### Output

![](./pics/Lab2/send2/2.1.png)

![](./pics/Lab2/send2/2.2.png)

## \centering 7 Display the odd counter using the onboard LEDs and screen; After 10 seconds, reset all the values of the onboard LED and display even counter using Timeout Object.

### Question

Display the odd counter using the onboard LEDs and screen; After 10 seconds, reset all the values of the onboard LED and display even counter using Timeout Object. Give switch option to manually toggle between two counters. Libraries Used: InterruptIn, Ticker, TimeOut, BusOut

### Aim

To display the odd counter using the onboard LEDs and screen. After 10 seconds, it reset all the values of the onboard LED and display even counter using Timeout Object. Switch should be there to manually toggle between two counters as well.

### Code

```cpp
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
```

### Output

![](./pics/Lab2/send2/3.1.png)

![](./pics/Lab2/send2/3.2.png)

![](./pics/Lab2/send2/3.3.png)

\pagebreak

# Lab 3 \hfill Date: 14-02-2022

\lhead{Lab 3}
\rhead{Date: 14-02-2022}

### Questions

1. Increase the intensity of one LED while descreasing the other LED's intensity at the same unit. Display the intensity value of the LEDs. Libraries Used: pwmout

1. Interface potentiometer with mbed board and based on the value of potentiometer, adjust the intensity of an external LED. Libraries To Be Used: pwmout, analogin

1. Interface switch, 2 LEDs, potentiometer with the mbed board. If the switch is on, control the intensity of the LEDs using potentiometer (one LED should be increasing and other should be decreasing at the rate given via potentiometer). If the switch is off, blink LEDs one at increasing rate and other at decreasing rate (same rate) and loop back.

## \centering 8 Increase the intensity of one LED while descreasing the other LED's intensity at the same unit. Display the intensity value of the LEDs.

### Question

Increase the intensity of one LED while descreasing the other LED's intensity at the same unit. Display the intensity value of the LEDs. Libraries Used: pwmout

### Aim

To increase the intensity of one LED while descreasing the other LED's intensity at the same unit. We must also display the intensity value of the LEDs.

### Code

```cpp
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
```

### Output

![](./pics/Lab3/Q1/Screenshot_20220403_155419.png)

## \centering 9 Interface potentiometer with mbed board and based on the value of potentiometer, adjust the intensity of an external LED.

### Question

Interface potentiometer with mbed board and based on the value of potentiometer, adjust the intensity of an external LED. Libraries To Be Used: pwmout, analogin

### Aim

To interface potentiometer with mbed board and based on the value of potentiometer and adjust the intensity of an external LED.

### Code

```cpp
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
```

### Output

![](./pics/Lab3/Q2/Screenshot_20220403_155519.png)

## \centering 10 Interface switch, 2 LEDs, potentiometer with the mbed board. If the switch is on, control the intensity of the LEDs using potentiometer (one LED should be increasing and other should be decreasing at the rate given via potentiometer). If the switch is off, blink LEDs one at increasing rate and other at decreasing rate (same rate) and loop back.

### Question

Interface switch, 2 LEDs, potentiometer with the mbed board. If the switch is on, control the intensity of the LEDs using potentiometer (one LED should be increasing and other should be decreasing at the rate given via potentiometer). If the switch is off, blink LEDs one at increasing rate and other at decreasing rate (same rate) and loop back.

### Aim

To interface switch, 2 LEDs, potentiometer with the mbed board. If the switch is on, we must control the intensity of the LEDs using potentiometer ,one LED should be increasing and other should be decreasing at the rate given via potentiometer. If the switch is off, we must blink LEDs one at increasing rate and other at decreasing rate (same rate) and loop back.

### Code

```cpp
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
```

### Output

![](./pics/Lab3/Q3/Screenshot_20220403_155313.png)

\pagebreak

# Lab 4 \hfill Date: 28-02-2022

\lhead{Lab 4}
\rhead{Date: 28-02-2022}

### Questions

1. Write a program to increase the intensity of external LED. At the same rate, increase the sound intensity of speaker.Libraries Used: pwmout

1. Design an alarm system, which makes double beep sound for every 5s using a speaker. Libraries To Be Used: pwmout, analogin

1. Have a switch, 2 LEDs and a speaker interfaced with mbed board. Upon switching on, the intensity of the sound should be increasing and the upon switching off, should make the intensity of the sound decreasing. Proportionally increase or decrease the intensity of two LEDs.

1. Design a program to make ambulance sound.

## \centering 11 Write a program to increase the intensity of external LED. At the same rate, increase the sound intensity of speaker

### Question

Write a program to increase the intensity of external LED. At the same rate, increase the sound intensity of speaker.Libraries Used: pwmout

### Aim

To write a program to increase the intensity of external LED. At the same rate, we must increase the sound intensity of speaker.

### Code

```cpp
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
```

### Output

![](./pics/Lab4/Q1/q1.png)

## \centering 12 Design an alarm system, which makes double beep sound for every 5s using a speaker

### Question

Design an alarm system, which makes double beep sound for every 5s using a speaker. Libraries To Be Used: pwmout, analogin

### Aim

To design an alarm system, which makes double beep sound for every 5s using a speaker.

### Code

```cpp
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
```

### Output

![](./pics/Lab4/Q2/q2.png)

## \centering 13 Have a switch, 2 LEDs and a speaker interfaced with mbed board. Upon switching on, the intensity of the sound should be increasing and the upon switching off, should make the intensity of the sound decreasing. Proportionally increase or decrease the intensity of two LEDs.

### Question

Have a switch, 2 LEDs and a speaker interfaced with mbed board. Upon switching on, the intensity of the sound should be increasing and the upon switching off, should make the intensity of the sound decreasing. Proportionally increase or decrease the intensity of two LEDs.

### Aim

To interface a switch, 2 LEDs and a speaker with mbed board. Upon switching on, the intensity of the sound is to be increased and upon switching off, the intensity of the sound is to be decreasded. The intensity of two LEDs is to be proportionally increased or decreased.

### Code

```cpp
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
```

### Output

![](./pics/Lab4/Q3/q3.png)

## \centering 14 Design a program to make ambulance sound.

### Question

Design a program to make ambulance sound.

### Aim

To design a program which will output ambulance sound.

### Code

```cpp
#include "mbed.h"
PwmOut speaker(p21);
int main(){
    int i;
    while(1){
        for(i=0; i <26; i++){
            speaker.period(1.0/259.0);
            speaker = float(i)/500.0;
            wait(0.5);
            speaker.period(1.0/340.0);
            wait(0.5);
        }
        for(i=26; i >= 0; i--){
            speaker.period(1.0/259.0);
            speaker = float(i)/500.0;
            wait(0.5);
            speaker.period(1.0/440.0);
            wait(0.5);
        }
    }
}
```

### Output

![](./pics/Lab4/Q4/Screenshot_20220403_181202.png)

\pagebreak

# Lab 5 \hfill Date: 07-03-2022

\lhead{Lab 5}
\rhead{Date: 07-03-2022}

### Questions

1. Blink LEDs in alternate order – 1 and 3 together and 2 and 4 together.

1. Blink LEDs – count from 1 to 15; if the board is counting odd value, wait for 1 sec, else wait for 2 sec.

1. Blink LEDs – for all composite number below 15.

1. Blink LEDs – to count even numbers

## \centering 15 Blink LEDs in alternate order – 1 and 3 together and 2 and 4 together.

### Question

Blink LEDs in alternate order – 1 and 3 together and 2 and 4 together.

### Aim

To blink LEDs in alternate order – 1 and 3 should blink together and 2 and 4 should blink together.

### Code

```cpp
// C++ code
//
#define F(x) x? HIGH: LOW
int pins[] = {13,12,11,10};
void setup()
{
  for(int i=0;i<4;i++)
  pinMode(pins[i], OUTPUT);
}
void show(int x){
  int vals[] = {F(x&8) ,F(x&4), F(x&2), F(x&1)} ;
  for(int i=0;i<4;i++){
    digitalWrite(pins[i],vals[i]);
  }
}

void loop()
{
  show(0b1010);
  delay(1000);
  show(0b0101);
  delay(1000);

}
```

### Output

![](./pics/Lab5/q1_1.png)

![](./pics/Lab5/q1_2.png)

## \centering 16 Blink LEDs – count from 1 to 15; if the board is counting odd value, wait for 1 sec, else wait for 2 sec.

### Question

Blink LEDs – count from 1 to 15; if the board is counting odd value, wait for 1 sec, else wait for 2 sec.

### Aim

To blink LEDs and count from 1 to 15. If the board is counting odd value, it should wait for 1 sec, else it should wait for 2 sec.

### Code

```cpp
// C++ code
//
#define F(x) x? HIGH: LOW
int pins[] = {13,12,11,10};
void setup()
{
  for(int i=0;i<4;i++)
  pinMode(pins[i], OUTPUT);
}
void show(int x){
  int vals[] = {F(x&8) ,F(x&4), F(x&2), F(x&1)} ;
  for(int i=0;i<4;i++){
    digitalWrite(pins[i],vals[i]);
  }
}

void loop()
{
  for(int i=1;i<16;i++){
    show(i);
    if(i%2==1)
      delay(1000);
    else
      delay(2000);
  }
}
```

### Output

![](./pics/Lab5/q2_1.png)

![](./pics/Lab5/q2_2.png)

![](./pics/Lab5/q2_3.png)

![](./pics/Lab5/q2_4.png)

## \centering 17 Blink LEDs – for all composite number below 15.

### Question

Blink LEDs – for all composite number below 15.

### Aim

To blink LEDs for all composite numbers below 15.

### Code

```cpp
// C++ code
//
#define F(x) x? HIGH: LOW

int pins[] = {13,12,11,10};

void setup()
{
  for(int i=0;i<4;i++)
 	 pinMode(pins[i], OUTPUT);
}
void show(int x){
  int vals[] = {F(x&8) ,F(x&4), F(x&2), F(x&1)} ;
  for(int i=0;i<4;i++){
    digitalWrite(pins[i],vals[i]);
  }
}

bool is_prime(int x){
  for(int i=2;i<x;i++){
    if(x%i==0)
      return false;
  }
  return true;
}

void loop()
{
  for(int i=2;i<16;i+=1){
    if(!is_prime(i)){
    	show(i);
    	delay(1000);
    }
  }
}
```

### Output

![](./pics/Lab5/q3_1.png)

![](./pics/Lab5/q3_2.png)

![](./pics/Lab5/q3_3.png)

![](./pics/Lab5/q3_4.png)


## \centering 18 Blink LEDs – to count even numbers

### Question

Blink LEDs – to count even numbers

### Aim

To blink LEDs to count even numbers

### Code

```cpp
// C++ code
//
#define F(x) x? HIGH: LOW

int pins[] = {13,12,11,10};

void setup()
{
  for(int i=0;i<4;i++)
 	 pinMode(pins[i], OUTPUT);
}
void show(int x){
  int vals[] = {F(x&8) ,F(x&4), F(x&2), F(x&1)} ;
  for(int i=0;i<4;i++){
    digitalWrite(pins[i],vals[i]);
  }
}

void loop()
{
  for(int i=0;i<16;i+=2){
    show(i);
    delay(1000);
  }
}
```

### Output

![](./pics/Lab5/q4_0.png)

![](./pics/Lab5/q4_1.png)

![](./pics/Lab5/q4_2.png)

![](./pics/Lab5/q4_3.png)

![](./pics/Lab5/q4_4.png)

\pagebreak

# Lab 6 \hfill Date: 28-03-2022

\lhead{Lab 6}
\rhead{Date: 28-03-2022}

### Questions

1. Interface an ultrasonic sensor and display the distance measured in a screen and glow red, blue and green led if the distance is close, moderate and far respectively. Play different tones for different cases.
1. Interface a PIR sensor with Arduino and blink a led if any movement is captured by the sensor and count the number of movements. Make a buzzer when movement detected

## \centering 19 Interface an ultrasonic sensor and display the distance measured in a screen and glow red, blue and green led if the distance is close, moderate and far respectively. Play different tones for different cases.

### Question

Interface an ultrasonic sensor and display the distance measured in a screen and glow red, blue and green led if the distance is close, moderate and far respectively. Play different tones for different cases.

### Aim

To interface an ultrasonic sensor and display the distance measured in a screen and glow red, blue and green led if the distance is close, moderate and far respectively. We must play different tones for different cases.

### Code

```cpp
// C++ code
//
#define F(x) x? HIGH: LOW

const int red = 3;
const int blue = 4;
const int green = 5;
const int speaker = 10;
const int ping = 7;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(speaker, OUTPUT);
}

void displayLight(int code) {
  digitalWrite(red,F(code==0) );
  digitalWrite(blue, F(code==1) );
  digitalWrite(green, F(code==2));
}

void playTone(long duration, int freq) {
  duration *= 1000;
  int period = (1.0 / freq) * 100000;
  long elapsed_time = 0;
  while (elapsed_time < duration) {
    digitalWrite(speaker, HIGH);
    delayMicroseconds(period / 2);
    digitalWrite(speaker, LOW);
    delayMicroseconds(period / 2);
    elapsed_time += (period);
  }
}

void loop() {
  long duration, inches, cm;

  pinMode(ping, OUTPUT);
  digitalWrite(ping, LOW);
  delayMicroseconds(2);
  digitalWrite(ping, HIGH);
  delayMicroseconds(5);
  digitalWrite(ping, LOW);

  pinMode(ping, INPUT);
  duration = pulseIn(ping, HIGH);

  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  if (cm < 50) {
  	displayLight(0);
    playTone(300, 100);
  } else if (cm < 150) {
    displayLight(1);
    playTone(300, 200);
  } else {
    displayLight(2);
    playTone(300, 300);
  }

  delay(100);
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

```

### Output

![](./pics/Lab6/q1_1.png)

![](./pics/Lab6/q1_2.png)

![](./pics/Lab6/q1_3.png)

## \centering 20 Interface a PIR sensor with Arduino and blink a led if any movement is captured by the sensor and count the number of movements. Make a buzzer when movement detected.

### Question

Interface a PIR sensor with Arduino and blink a led if any movement is captured by the sensor and count the number of movements. Make a buzzer when movement detected

### Aim

To interface a PIR sensor with Arduino and blink a led if any movement is captured by the sensor and count the number of movements. We must make a buzzer when movement detected.

### Code

```cpp
// C++ code
//
#define F(x) x? HIGH: LOW

const int led = 4;
const int pir = 3;
const int speaker = 10;

int totalMovements = 0;
bool isMoving = false;

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(pir, INPUT);
  pinMode(speaker, OUTPUT);
}

void playTone(long duration, int freq) {
  duration *= 1000;
  int period = (1.0 / freq) * 100000;
  long elapsed_time = 0;
  while (elapsed_time < duration) {
    digitalWrite(speaker, HIGH);
    delayMicroseconds(period / 2);
    digitalWrite(speaker, LOW);
    delayMicroseconds(period / 2);
    elapsed_time += (period);
  }
}

void loop()
{
  int pirStat = digitalRead(pir);
  if (pirStat == HIGH) {
    if (!isMoving) {
      playTone(300, 300);
      totalMovements += 1;
      Serial.print("Total movements: ");
      Serial.print(totalMovements);
      Serial.print("\n");
      isMoving = true;
    }
  	digitalWrite(led, HIGH);
  } else {
      isMoving = false;
  	digitalWrite(led, LOW);
  }
}

```

### Output

![](./pics/Lab6/q2_1.png)

![](./pics/Lab6/q2_2.png)

![](./pics/Lab6/q2_3.png)

\pagebreak

# Lab 7 \hfill Date: 11-04-2022

\lhead{Lab 7}
\rhead{Date: 11-04-2022}

### Questions

1. Interface two 7-segment display with Arduino Uno board. Implement the a)odd counter and b)even counter and display the values in the seven segment display.
2. Interface the ambient light sensor with Arduino Uno board. Check the light value from the sensor, and switch on/off the bulb (based on the threshold value).
3. Interface the temperature and gas sensor with Arduino Uno board. Check the temperature and the gas value, if the limit is beyond the threshold, switch on the bulb and make alarm using buzzer.

## \centering 21 Interface two 7-segment display with Arduino Uno board. Implement the a)odd counter and b)even counter and display the values in the seven segment display.

### Question

Interface two 7-segment display with Arduino Uno board. Implement the a)odd counter and b)even counter and display the values in the seven segment display.

### Aim

To interface two 7-segment display with Arduino Uno board. We must implement a)odd counter b)even counter and display the values in the seven segment display.

### Code

```cpp
unsigned const int A = 13;
unsigned const int B = 12;
unsigned const int C = 11;
unsigned const int D = 10;
unsigned const int E = 9;
unsigned const int F = 8;
unsigned const int G = 7;
unsigned const int H = 6;
unsigned const int btn = 4;

void setup(void)
{
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(H, OUTPUT);
  pinMode(btn, INPUT);
}
int pins[] = {A,B,C,D,E,F,G,H};

int zero = 0b01111110;
int one  = 0b00010010;
int two  = 0b10111100;
int three= 0b10110110;
int four = 0b11010010;
int five = 0b11100110;
int six  = 0b11101110;
int seven= 0b00110010;
int eight= 0b11111110;
int nine = 0b11110110;

//void (*nums[])() ={zero,one,two,three, four, five,six,seven,eight,nine};
int numbers[] = {zero,one,two,three, four, five,six,seven,eight,nine};

void show(int num){
	digitalWrite(H, num&1);
  	digitalWrite(G, num&2);
	digitalWrite(F, num&4);
	digitalWrite(E, num&8);
	digitalWrite(D, num&16);
	digitalWrite(C, num&32);
	digitalWrite(B, num&64);
	digitalWrite(A, num&128);
}

// Start
void loop(void)
{

  if(digitalRead(btn)==HIGH){
    for(int i=0;i<10;i+=2){
      show(numbers[i]);
      delay(1000);
    }
  }else{
    for(int i=1;i<10;i+=2){
	  show(numbers[i]);
      delay(1000);
    }
  }
}

```

### Output

- Odd and Even decided based on switch

### Odd Output

![](./Lab7/pics/q1_odd1.png)

![](./Lab7/pics/q1_odd2.png)

### Even Output

![](./Lab7/pics/q1_even1.png)

![](./Lab7/pics/q1_even2.png)

## \centering 22 Interface the ambient light sensor with Arduino Uno board. Check the light value from the sensor, and switch on/off the bulb (based on the threshold value).

### Question

Interface the ambient light sensor with Arduino Uno board. Check the light value from the sensor, and switch on/off the bulb (based on the threshold value).

### Aim

To interface the ambient light sensor with Arduino Uno board. We must check the light value from the sensor, and switch on/off the bulb (based on some threshold value).

### Code

```cpp
int LED = 12;
int MQ2pin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  float sensorValue;
  sensorValue = analogRead(MQ2pin); // read analog input pin 0

  if(sensorValue >= 10){
    digitalWrite(LED,HIGH);

    Serial.println("\nSensor Value: ");
    Serial.print(sensorValue);
    Serial.println("\nDANGER\n");
  }
  else{
    digitalWrite(LED,LOW);
    Serial.println("\nSensor Value: ");
    Serial.print(sensorValue);

  }
  delay(1000);
}

float getsensorValue(int pin){
  return (analogRead(pin));
}
```

### Output

![](./Lab7/pics/q2_1.png)

![](./Lab7/pics/q2_2.png)

## \centering 23 Interface the temperature and gas sensor with Arduino Uno board. Check the temperature and the gas value, if the limit is beyond the threshold, switch on the bulb and make alarm using buzzer.

### Question

Interface the temperature and gas sensor with Arduino Uno board. Check the temperature and the gas value, if the limit is beyond the threshold, switch on the bulb and make alarm using buzzer.

### Aim

To interface the temperature and gas sensor with Arduino Uno board. We must check the temperature and the gas value, if the limit is beyond the threshold, switch on the bulb and make alarm using buzzer.

### Code

```cpp
int LED = 12;
int gas = A0;
int tmppin= A2;
int piezo = 13;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(piezo, OUTPUT);
  pinMode(gas,INPUT);
  pinMode(tmppin,INPUT);

}

void loop() {
  float sensorValue, tempSensor;
  sensorValue = analogRead(gas); // read analog input pin 0

  tempSensor= analogRead(tmppin);

  bool smoke= sensorValue >= 300;
  bool temp= tempSensor >100;

  if(smoke&&temp){
    digitalWrite(LED,HIGH);
    digitalWrite(piezo, HIGH);

    Serial.println("\nSmoke Sensor Value: ");
    Serial.print(sensorValue);
    Serial.println("\nTemp Sensor Value: ");
    Serial.print(tempSensor);
    Serial.println(" \nDANGER\n");
  }
  else{
    digitalWrite(LED,LOW);
    digitalWrite(piezo, LOW);
    Serial.println("Smoke Sensor Value: ");
    Serial.print(sensorValue);
    Serial.println("\nTemp Sensor Value: ");
    Serial.print(tempSensor);
  }
  delay(1000);
}

float getsensorValue(int pin){
  return (analogRead(pin));
}
```

### Output

![](./Lab7/pics/q3_1.png)

![](./Lab7/pics/q3_2.png)

![](./Lab7/pics/q3_3.png)

\pagebreak

# Lab 8 \hfill Date: 18-04-2022

\lhead{Lab 8}
\rhead{Date: 18-04-2022}

### Questions

1. Interface force sensor with Arduino board and display the amount of force given as input to sensor in LCD screen. Also, interface LED RGB and change color of the LED based on the some threshold values.
2. Interface the keypad and tilt sensor with Arduino board, if the sensor is being tilted, then take input from keypad and print it in the LCD.

## \centering 24 Interface force sensor with Arduino board and display the amount of force given as input to sensor in LCD screen. Also, interface LED RGB and change color of the LED based on the some threshold values.

### Question

Interface force sensor with Arduino board and display the amount of force given as input to sensor in LCD screen. Also, interface LED RGB and change color of the LED based on the some threshold values.

### Aim

To interface force sensor with Arduino board and display the amount of force given as input to sensor in LCD screen. We must also interface LED RGB and change color of the LED based on the some threshold values.

### Code

```cpp
// C++ code
//
#include<LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

int force = 0;
int red = 4;
int blue = 3;
int green = 2;
void setup()
{
  lcd.begin(16, 2);
  pinMode(A0, INPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  force = analogRead(A0);
  Serial.println(force);
  lcd.clear();
  lcd.print(force);
  if(force<100){
   	digitalWrite(green, HIGH);
    digitalWrite(blue, LOW);
    digitalWrite(red, LOW);
  }else if(force < 300){
    digitalWrite(green, LOW);
    digitalWrite(blue, HIGH);
    digitalWrite(red, LOW);
  }else{
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(red, HIGH);
  }
  delay(1000);
}

```

### Output

![](./Lab8/pics/1_1.png)

![](./Lab8/pics/1_2.png)

![](./Lab8/pics/1_3.png)

## \centering 25 Interface the keypad and tilt sensor with Arduino board, if the sensor is being tilted, then take input from keypad and print it in the LCD.

### Question

Interface the keypad and tilt sensor with Arduino board, if the sensor is being tilted, then take input from keypad and print it in the LCD.

### Aim

To interface the keypad and tilt sensor with Arduino board. If the sensor is being tilted, we take input from keypad and print it in the LCD.

### Code

```cpp
#include <LiquidCrystal.h>
#include <Keypad.h>

const byte numRows= 4; //number of rows on the keypad
const byte numCols= 4; //number of columns on the keypad

//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]=
{
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {10,9,8,7}; //Rows 0 to 3
byte colPins[numCols]= {A0,A1,A2,A3}; //Columns 0 to 3

//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int tilt = A4;

char buf[16]={0};
int cnt =0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(tilt, INPUT);
}


void loop() {
  int reading = analogRead(tilt);


  char keypressed = myKeypad.getKey();

  Serial.println(reading);

  if(reading>100){

    buf[cnt] = keypressed;
    if(keypressed != 0) cnt++;
    cnt%=16;
    buf[cnt]=0;
    lcd.clear();
    lcd.print(buf);

  }else{
    lcd.clear();
    lcd.print("IDLE");
  }

  delay(50);
}
```

### Output

![](./Lab8/pics/2_1.png)

![](./Lab8/pics/2_2.png)

![](./Lab8/pics/2_3.png)
