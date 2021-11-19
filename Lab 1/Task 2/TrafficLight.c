/*
  Quan Vo
  EE 474 - Hussein
  October 20, 2021
  Lab 1 Task 2

  TrafficLight.c is the implementation of the functions required to
  implement a simple traffic light system.
*/

#include "TrafficLight.h"
#include "C:\Users\quanv\Documents\EE 474\EE 474 Labs\lab1\lab1.h"
#include <stdint.h>

void LED_init(PinPosition led1, PinPosition led2, PinPosition led3)
{
  volatile unsigned short delay = 0;
  PinPosition LEDs = led1 | led2 | led3;
  RCGCGPIO |= 0x400; // activate clock for Port L
  delay++;
  delay++;
  GPIOAMSEL_L &= ~LEDs; // disable analog function of PL2, PL3, PL4
  GPIODIR_L |= LEDs; // set PL2, PL3, PL4 to output
  GPIOAFSEL_L &= ~LEDs; // set PL2, PL3, PL4 regular port function
  GPIODEN_L |= LEDs; // enable digital output on PL2, PL3, PL4
}

void LED_on(PinPosition pin)
{
  GPIODATA_L |= pin;
}

void LED_off(PinPosition pin)
{
  GPIODATA_L &= ~pin;
}

void extern_switch_init(PinPosition switch1, PinPosition switch2)
{
  PinPosition switches = switch1 | switch2;
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x400; // Enable Port L Gating Clock
  delay++;
  delay++;
  GPIOAMSEL_L &= ~switches; // Disable PL0 & PL1 analog function
  GPIOAFSEL_L &= ~switches; // Select PL0 & PL1 regular port function
  GPIODIR_L &= ~switches; // Set PL0 & PL1 input direction
  GPIODEN_L |= switches; // Enable PL0 & PL1 digital function
}

Events switch_input(PinPosition pin)
{
  if ((GPIODATA_L & pin) == pin) { return push; }
  else { return not_push; }
}

void poll_switches(Button *switch1, Button *switch2)
{
  // get initial switch input
  switch1->event = switch_input(switch1->pin);
  switch2->event = switch_input(switch2->pin);
  for (int i = 0; i < 500000; i++)
  {
    switch1->event = (switch1->event == push) ? push : switch_input(switch1->pin);
    switch2->event = (switch2->event == push) ? push : switch_input(switch2->pin);
  }
}
