/*
  Quan Vo
  EE 474-Fall 2021-Hussein
  October 24, 2021
  Lab 2 Task 1a
  
  lab2task1a.c
*/

#include "C:\Users\quanv\Documents\EE 474\EE 474 Labs\lab2\lab2.h"
#include <stdint.h>

// Initializes GPIO ports required for on-board LEDs D1 to D4
void GPIO_init();

int main(void)
{
  GPIO_init();
  timer_init();
  int state = 0;
  while (1)
  {
    // poll timer. When timer hits zero, turn on LED Di
    if (is_timer_timed_out())
    {
      if (state < 4)
      {
        LED_on(state + 1);
      }
      else if (state < 8)
      {
        LED_off((state % 4) + 1);
      }
      
      if (state == 7)
      {
        state = 0;
      }
      else
      {
        state += 1;
      }
      restart_timer();
    }
  }
}

void GPIO_init()
{
  volatile unsigned short delay = 0;
  RCGCGPIO = 0x1020 ;// enable GPIO Port F and Port N
  delay++;  // delay 2 clock cycles before accessing register
  delay++;
  
  GPIODIR_F = 0x11; // Set PF0, PF4 to output
  GPIODEN_F = 0x11; // set PF0, PF4 to digital port
  
  GPIODIR_N = 0x3; // Set PN0, PN1 to output
  GPIODEN_N = 0x3; // set PF0, PN1 to digital port
}
