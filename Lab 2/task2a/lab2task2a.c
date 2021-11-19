/*
  Quan Vo
  EE 474-Fall 2021-Hussein
  November , 2021
  Lab 2 Task 2A
  
  lab2task2a.c 
*/

#include "C:\Users\quanv\Documents\EE 474\EE 474 Labs\lab2\lab2.h"
#include <stdint.h>

// Initializes GPIO ports required for on-board LEDs D1 to D4
void GPIO_init();

// Takes a number and turn on the on-board LED of that number. The parameter
// must be between 1 and 4, inclusive
// Ex: LED_on(4) turns on LED D4
void LED_on(uint8_t led_number);

// Takes a number and turn off the on-board LED of that number. The parameter
// must be between 1 and 4, inclusive
// Ex: LED_off(4) turns on LED D4
void LED_off(uint8_t led_number);

volatile uint8_t State = 0;

int main(void)
{
  GPIO_init();
  timer_interrupt_init();
  
  while (1) {}
  
  return 0;
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

void Timer0A_Handler(void)
{
  restart_timer();
  if (State < 4)
  {
    LED_on(State + 1);
  }
  else if (State < 8)
  {
    LED_off((State % 4) + 1);
  }
  
  if (State == 7)
  {
    State = 0;
  }
  else
  {
    State += 1;
  }
}
