/*
  Quan Vo
  EE 474-Fall 2021-Hussein
  November 9, 2021
  Lab 3 Task 1b
  
  lab3task1b.c is the main file for Lab 3 Task 1b. The program reads the
  board's internal temperature sensor and outputs the data to the Terminal I/O.
  The system clock frequency can be changed to 12 MHz or 120 MHz by using the
  onboard switch SW1 and SW2, respectively.
*/

#include "..\Lab3_Inits.h"
#include "..\lab3.h"

#include <stdint.h>
#include <stdio.h>

uint32_t ADC_value;

int main(void) {
  // Select system clock frequency preset
  enum frequency freq = PRESET2; // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  ADCReadTemp_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  TimerInterrupt_Init();
  GPIOInterrupt_Init();
  
  while(1) { }
  return 0;
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
    printf("System Clock Speed: 12MHz\n");
  }
  else if ((~GPIODATA_J & SW2) == SW2) // sw2 pressed
  {
    GPTMCTL_0 = 0x0;
    GPTMTAILR_0 = 120000000;
    PLL_Init(PRESET1);
    GPTMCTL_0 = 0x323;
    printf("System Clock Speed: 120MHz\n");
  }
}

void TimerA0_Handler(void)
{
  GPTMICR_0 |= 0x1;
  // on time out, calulate and print temperature info
  float temperature = 147.5 - ((75 * (3.3 - 0) * ADC_value) / 4096);
  printf("Temperature: %.2f degrees C\n", temperature);
}