/*
  Quan Vo
  EE 474-Fall 2021-Hussein
  October 24, 2021
  Lab 2
  
  lab2.h is a header file for all of lab 2. This file contains definitions of
  register addresses required for lab 2. Also includes lab1.h for GPIO port
  register addresses
*/

#ifndef __HEADER2_H__
#define __HEADER2_H__

#include "C:\Users\quanv\Documents\EE 474\EE 474 Labs\lab1\lab1.h"
#include <stdint.h>

// General Purpose Timer 0 registers
#define RCGCTIMER (*((volatile uint32_t *) 0x400FE604))
#define GPTMCTL_0 (*((volatile uint32_t *) 0x4003000C))
#define GPTMCFG_0 (*((volatile uint32_t *) 0x40030000))
#define GPTMTAMR_0 (*((volatile uint32_t *) 0x40030004))
#define GPTMTAILR_0 (*((volatile uint32_t *) 0x40030028))
#define GPTMCTL_0 (*((volatile uint32_t *) 0x4003000C))
#define GPTMRIS_0 (*((volatile uint32_t *) 0x4003001C))
#define GPTMICR_0 (*((volatile uint32_t *) 0x40030024))

// Interrupt Registers
#define GPTMIMR_0 (*((volatile uint32_t *) 0x40030018))
#define EN0 (*((volatile uint32_t *) 0xE000E100))
#define EN1 (*((volatile uint32_t *) 0xE000E104))
#define PRI12 (*((volatile uint32_t *) 0xE000E430))

// Port J registers
#define GPIOIS_J (* ((volatile uint32_t *)0x40060404))
#define GPIOIBE_J (* ((volatile uint32_t *)0x40060408))
#define GPIOIEV_J (* ((volatile uint32_t *)0x4006040C))
#define GPIOIM_J (* ((volatile uint32_t *)0x40060410))
#define GPIORIS_J (* ((volatile uint32_t *)0x40060414))
#define GPIOICR_J (* ((volatile uint32_t *)0x4006041C))

// Initializes GP Timer module 0 to a periodic timer w/ 1 Hz blink rate
void timer_init();

// Initializes GP Timer module 0 to a periodic timer w/ 1 Hz blink rate
// and enable interrupt
void timer_interrupt_init();

// Restart the timer by clearing the TATORIS bit in GPTMRIS
void restart_timer();

int is_timer_timed_out();

// Takes a number and turn on the on-board LED of that number. The parameter
// must be between 1 and 4, inclusive
// Ex: LED_on(4) turns on LED D4
void LED_on(uint8_t led_number);

// Takes a number and turn off the on-board LED of that number. The parameter
// must be between 1 and 4, inclusive
// Ex: LED_off(4) turns on LED D4
void LED_off(uint8_t led_number);

#endif // __HEADER2_H__