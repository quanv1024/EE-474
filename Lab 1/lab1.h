/*
  Quan Vo
  EE 474 - Hussein
  October 11, 2021
  Lab 1
  
  lab1.h is the header file to be used for all of lab 1. Contains pointers to
  the required registers.
*/

#ifndef __HEADER1_H__
#define __HEADER1_H__

#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))

// Port F registers
#define GPIODIR_F (*((volatile uint32_t *)0x4005D400))
#define GPIODEN_F (*((volatile uint32_t *)0x4005D51C))
#define GPIODATA_F (*((volatile uint32_t *)0x4005D3FC))

// Port J registers
#define GPIODIR_J (*((volatile uint32_t *)0x40060400))
#define GPIODEN_J (*((volatile uint32_t *)0x4006051C))
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC))
#define GPIOPUR_J (* ((volatile uint32_t *)0x40060510))
#define GPIOCR_J (* ((volatile uint32_t *)0x40060524))
#define GPIOLOCK_J (* ((volatile uint32_t *)0x40060520))

// Port N registers
#define GPIODIR_N (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))

// Pin number of switches and LEDs in Lab 1 Task 1
#define SW1 0x1
#define SW2 0x2
#define LED4 0x1
#define LED3 0x10
#define LED2 0x1
#define LED1 0x2

// delay creates a delay of about 0.3 seconds
void delay();

#endif //__HEADER1_H__
