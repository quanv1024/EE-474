/*
  Quan Vo
  EE 474 - Hussein
  October 11, 2021
  Lab 1 Task 1b
  
  lab1task1b.c is the main file for task 1b of lab 1. The program turns LED1
  (D1) when switch 1 (SW1) is pressed, and turn on LED2 (D2) when switch 2 (SW2)
  is pressed.
*/

#include "C:\Users\quanv\Documents\EE 474\EE 474 Labs\lab1\lab1.h"
#include <stdint.h>

// configure registers to use GPIO pins PJ0, PJ4, PN0, and PN1 as
// digital outputs for LEDs and switches
void GPIO_init();

int main(void)
{
  GPIO_init();
  
  while (1)
  {
    // if switch 1 is on, turn LED 1 on. Else, turn off LED 1
    if ((~GPIODATA_J & SW1) == SW1)
    {
      GPIODATA_N |= LED1;
    }
    else
    {
      GPIODATA_N &= ~LED1;
    }
    
    // if switch 2 is on, turn LED2 on. Else, turn off LED2
    if ((~GPIODATA_J & SW2) == SW2)
    {
      GPIODATA_N |= LED2;
    }
    else
    {
      GPIODATA_N &= ~LED2;
    }
  }
  
  return 0;
}

void GPIO_init()
{
  volatile unsigned short delay = 0;
  RCGCGPIO = 0x1100 ;// enable GPIO Port J and Port N
  delay++;  // delay 2 clock cycles before accessing register
  delay++;

  // configure registers for LED1 and LED2
  GPIODIR_N = LED1 | LED2; // Set PN0, PN1 to output
  GPIODEN_N = LED1 | LED2; // set PN0, PN1 to digital port
  
  // configure registers for switch 1 and switch 2
  GPIODEN_J = SW1 | SW2;
  GPIOLOCK_J = 0x4C4F434B; // unlock GPIOCR register
  GPIOCR_J = SW1 | SW2; // allow pull up resistors to be hooked to PJ1 and PJ0
  GPIOPUR_J = SW1 | SW2; // connect pull up resistors to switches
}