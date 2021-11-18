/*
  Quan Vo
  EE 474 - Hussein
  October 11, 2021
  Lab 1 Task 1a
  
  lab1task1a.c is the main file for task 1a of lab 1. The program turns the
  LEDs on and off in a periodic pattern. Specifically, turn on LED 1 to 4
  sequentially, then turn off in the same order.
*/

#include "../lab1.h"
#include <stdint.h>

// configure registers to use GPIO pins PF0, PF4, PN0, and PN1 as
// digital outputs for LEDs
void GPIO_init();

int main(void)
{
  GPIO_init();
  
  while (1)
  {
    // turn on
    GPIODATA_N |= LED1;
    delay();
    GPIODATA_N |= LED2;
    delay();
    GPIODATA_F |= LED3;
    delay();
    GPIODATA_F |= LED4;
    delay();
    
    // turn off
    GPIODATA_N &= ~LED1;
    delay();
    GPIODATA_N &= ~LED2;
    delay();
    GPIODATA_F &= ~LED3;
    delay();
    GPIODATA_F &= ~LED4;
    delay();
  }
  
  return 0;
}

void delay()
{
  for (int i = 0; i < 1000000; i++) {}
}

void GPIO_init()
{
//  volatile unsigned short delay = 0;
//  RCGCGPIO |= 0x1020 ;// enable GPIO Port F and Port N
//  delay++;  // delay 2 clock cycles before accessing register
//  delay++;
//  
//
//  GPIODIR_F = GPIODIR_F | LED3 | LED4; // Set PF0, PF4 to output
//  GPIODEN_F = GPIODEN_F | LED3 | LED4; // set PF0, PF4 to digital port
//  
//  GPIODIR_N = GPIODIR_N | LED1 | LED2; // Set PN0, PN1 to output
//  GPIODEN_N = GPIODEN_N | LED1 | LED2; // set PN0, PN1 to digital port
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x1020 ;// enable GPIO Port F and Port N
  delay++;  // delay 2 clock cycles before accessing register
  delay++;
  
  GPIODIR_F = 0x11; // Set PF0, PF4 to output
  GPIODEN_F = 0x11; // set PF0, PF4 to digital port
  
  GPIODIR_N = 0x3; // Set PN0, PN1 to output
  GPIODEN_N = 0x3; // set PF0, PN1 to digital port
}
