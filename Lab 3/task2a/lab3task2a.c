/*
  Quan Vo
  EE 474-Fall 2021-Hussein
  November 9, 2021
  Lab 3 Task 2a
  
  lab3task2a.c is the main file for Lab 3 Task 2a. The program reads the
  board's internal temperature sensor and output the data to the PuTTY terminal.
  The system clock frequency can be changed to 12 MHz or 120 MHz by using the
  onboard switch SW1 and SW2, respectively.
*/

#include "..\Lab3_Inits.h"
#include "..\lab3.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint32_t ADC_value;

// flag for 1sec. Assert flag in timer ISR.
char timeout_flag;

// calculates the internal temperature and prints externl terminal 
// using UART Module 0
void CalcAndPrint(void);

int main(void) {
  // Select system clock frequency preset
  enum frequency freq = PRESET2; // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  ADCReadTemp_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  TimerInterrupt_Init();
  GPIOInterrupt_Init();
  UART0_Init();
  timeout_flag = 0;
  
  // buffer to hold string to print. 29 chars long
  char buffer[100];
  int length;
  
  while(1)
  {
    // poll ~BUSY & timeout_flag
    // transmit only when UART is not busy and it has been 1 sec
    if (((UARTFR_0 & 0x8) == 0 ) && timeout_flag)
    {
      CalcAndPrint();
    }
  }
  return 0;
}

void CalcAndPrint(void)
{
   // turn ADC_val to temp
  float temperature = 147.5 - ((75 * (3.3 - 0) * ADC_value) / 4096);
  
  // turn temp (float) to string   and store in buffer
  length = sprintf(buffer, "Temperature: %.2f degrees C\r\n", temperature);
  
  // transmit string char by char
  for (int i = 0; i < length; i++)
  {
    // wait until UART is not busy, then write to UARTDR (transmit)
    while ((UARTFR_0 & 0x8) != 0) {}
    UARTDR_0 = buffer[i];
  }
  // deassert timeout_flag
  timeout_flag = 0;
}

void ADC0SS3_Handler(void) {
  // STEP 4: Implement the ADC ISR.
  // 4.1: Clear the ADC0 interrupt flag
  ADCISC_0 |= 0x8;
  
  // 4.2: Save the ADC value to global variable ADC_value
  ADC_value = ADCSSFIFO3_0 & 0xFFF;
}

void GPIOJ_Handler(void)
{
  // if sw1 pressed, call PLL_Init for 12MHz and change timer to load 12,000,000
  // if sw2 pressed, call PLL_Init for 120MHz and change timer to load 120,000,000
  GPIOICR_J |= 0x3;
  // sw1 pressed
  if ((~GPIODATA_J & SW1) == SW1)
  {
    GPTMCTL_0 = 0x0;
    GPTMTAILR_0 = 12000000;
    PLL_Init(PRESET3);
    GPTMCTL_0 = 0x323;
  }
  else if ((~GPIODATA_J & SW2) == SW2) // sw2 pressed
  {
    GPTMCTL_0 = 0x0;
    GPTMTAILR_0 = 120000000;
    PLL_Init(PRESET1);
    GPTMCTL_0 = 0x323;
  }
}

void TimerA0_Handler(void)
{
  GPTMICR_0 |= 0x1;
  // on time out, assert a timer_flag
  timeout_flag = 1;
}

