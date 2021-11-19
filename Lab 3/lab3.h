/*
  Quan Vo
  EE 474-Fall 2021-Hussein
  November 9, 2021
  Lab 3
  
  lab3.h is a header file for all of lab 3. This file contains definitions of
  register addresses required for lab 3, not including the clock registers
*/

#ifndef _Lab3_H_
#define _Lab3_H_

#define RCGCGPIO        (*((volatile uint32_t *) 0x400FE608))
#define RCGCUART        (*((volatile uint32_t *) 0x400FE618))

// PA0 = U0Rx
// PA1 = U0Tx
// GPIO Port A Registers
#define GPIOAFSEL_A     (*((volatile uint32_t *) 0x40058420))
#define GPIOPCTL_A      (*((volatile uint32_t *) 0x4005852C))
#define GPIODEN_A       (*((volatile uint32_t *) 0x4005851C))

// GPIO Port F Registers
#define GPIODIR_F       (*((volatile uint32_t *) 0x4005D400))
#define GPIODEN_F       (*((volatile uint32_t *) 0x4005D51C))
#define GPIODATA_F      (*((volatile uint32_t *) 0x4005D3FC))

// Port J registers
#define GPIODIR_J       (*((volatile uint32_t *) 0x40060400))
#define GPIODEN_J       (*((volatile uint32_t *) 0x4006051C))
#define GPIODATA_J      (*((volatile uint32_t *) 0x400603FC))
#define GPIOPUR_J       (*((volatile uint32_t *) 0x40060510))
#define GPIOCR_J        (*((volatile uint32_t *) 0x40060524))
#define GPIOLOCK_J      (*((volatile uint32_t *) 0x40060520))
#define GPIOIS_J        (* ((volatile uint32_t *)0x40060404))
#define GPIOIBE_J       (* ((volatile uint32_t *)0x40060408))
#define GPIOIEV_J       (* ((volatile uint32_t *)0x4006040C))
#define GPIOIM_J        (* ((volatile uint32_t *)0x40060410))
#define GPIORIS_J       (* ((volatile uint32_t *)0x40060414))
#define GPIOICR_J       (* ((volatile uint32_t *)0x4006041C))

// GPIO Port N registers
#define GPIODIR_N       (*((volatile uint32_t *) 0x40064400))
#define GPIODEN_N       (*((volatile uint32_t *) 0x4006451C))
#define GPIODATA_N      (*((volatile uint32_t *) 0x400643FC))

// GPIO Port E registers
#define GPIOAFSEL_E     (*((volatile uint32_t *) 0x4005C420))
#define GPIODEN_E       (*((volatile uint32_t *) 0x4005C51C))
#define GPIOAMSEL_E     (*((volatile uint32_t *) 0x4005C528))

// define on-board LED pins and switches
#define LED1    0x2
#define LED2    0x1
#define LED3    0x10
#define LED4    0x1
#define SW1     0x1
#define SW2     0x2

// ADC0 Control Registers
#define RCGCADC         (*((volatile uint32_t*) 0x400FE638))
#define ADCCC_0         (*((volatile uint32_t*) 0x40038FC8))
#define ADCACTSS_0      (*((volatile uint32_t*) 0x40038000))
#define ADCEMUX_0       (*((volatile uint32_t*) 0x40038014))
#define ADCSSMUX3_0     (*((volatile uint32_t*) 0x400380A0))
#define ADCSSEMUX3_0    (*((volatile uint32_t*) 0x400380B8))
#define ADCSSCTL3_0     (*((volatile uint32_t*) 0x400380A4))
#define ADCIM_0         (*((volatile uint32_t*) 0x40038008))
#define ADCISC_0        (*((volatile uint32_t*) 0x4003800C))
#define ADCSSFIFO3_0    (*((volatile uint32_t*) 0x400380A8))

// General Purpose Timer 0 Registers
#define RCGCTIMER       (*((volatile uint32_t *) 0x400FE604))
#define GPTMCTL_0       (*((volatile uint32_t *) 0x4003000C))
#define GPTMCFG_0       (*((volatile uint32_t *) 0x40030000))
#define GPTMTAMR_0      (*((volatile uint32_t *) 0x40030004))
#define GPTMTAILR_0     (*((volatile uint32_t *) 0x40030028))
#define GPTMCTL_0       (*((volatile uint32_t *) 0x4003000C))
#define GPTMRIS_0       (*((volatile uint32_t *) 0x4003001C))
#define GPTMICR_0       (*((volatile uint32_t *) 0x40030024))
#define GPTMIMR_0       (*((volatile uint32_t *) 0x40030018))
#define GPTMADCEV_0     (*((volatile uint32_t *) 0x40030070))

// Interrupt Registers
#define EN0             (*((volatile uint32_t *) 0xE000E100))
#define EN1             (*((volatile uint32_t *) 0xE000E104))
#define PRI12           (*((volatile uint32_t *) 0xE000E430))

// UART Module 0 Registers
#define UARTDR_0        (*((volatile uint32_t *) 0x4000C000))
#define UARTFR_0        (*((volatile uint32_t *) 0x4000C018))
#define UARTIBRD_0      (*((volatile uint32_t *) 0x4000C024))
#define UARTFBRD_0      (*((volatile uint32_t *) 0x4000C028))
#define UARTLCRH_0      (*((volatile uint32_t *) 0x4000C02C))
#define UARTCTL_0       (*((volatile uint32_t *) 0x4000C030))
#define UARTCC_0        (*((volatile uint32_t *) 0x4000CFC8))

// UART Module 3 Registers
#define UARTDR_3        (*((volatile uint32_t *) 0x4000F000))
#define UARTFR_3        (*((volatile uint32_t *) 0x4000F018))
#define UARTIBRD_3      (*((volatile uint32_t *) 0x4000F024))
#define UARTFBRD_3      (*((volatile uint32_t *) 0x4000F028))
#define UARTLCRH_3      (*((volatile uint32_t *) 0x4000F02C))
#define UARTCTL_3       (*((volatile uint32_t *) 0x4000F030))
#define UARTCC_3        (*((volatile uint32_t *) 0x4000FFC8))

#endif //_Lab3_H_