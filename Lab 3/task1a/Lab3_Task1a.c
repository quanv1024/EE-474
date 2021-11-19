/**
 * EE/CSE 474: Lab3 Task1a main function
 */

// NOTE: This is the main function for Task 1a. You should start by
// implementing Lab3_Driver.c (STEP 0a, 1-3) and then come back to finish
// the ISR and the main function (STEP 0b, 4-5).

#include <stdint.h>
#include <stdio.h>
#include "../Lab3_Inits.h"

// STEP 0b: Include your header file here
#include "../lab3.h"

// Takes a number and turn on the on-board LED of that number. The parameter
// must be between 1 and 4, inclusive
// Ex: LED_on(4) turns on LED D4
void LED_on(char led_number);

// Takes a number and turn off the on-board LED of that number. The parameter
// must be between 1 and 4, inclusive
// Ex: LED_off(4) turns on LED D4
void LED_off(char led_number);

uint32_t ADC_value;

int main(void) {
  // Select system clock frequency preset
  enum frequency freq = PRESET2; // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  LED_Init();            // Initialize the 4 onboard LEDs (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  
  float resistance;
  
  while(1) {
    // STEP 5: Change the pattern of LEDs based on the resistance.
    // 5.1: Convert ADC_value to resistance in kilo-ohm
    resistance = ADC_value / 4095.0 * 10.0;

    temperature = 147.5 - ((75 * (3.3 - 0) * ADC_value) / 4096);
    // 5.2: Change the pattern of LEDs based on the resistance
    if (resistance < 2.5) {
      LED_on(1);
      LED_off(2);
      LED_off(3);
      LED_off(4);
    } else if (resistance < 5.0) {
      LED_on(1);
      LED_on(2);
      LED_off(3);
      LED_off(4);
    } else if (resistance < 7.5) {
      LED_on(1);
      LED_on(2);
      LED_on(3);
      LED_off(4);
    } else {
      LED_on(1);
      LED_on(2);
      LED_on(3);
      LED_on(4);
    }
    
  }
  return 0;
}

void ADC0SS3_Handler(void) {
  // STEP 4: Implement the ADC ISR.
  // 4.1: Clear the ADC0 interrupt flag
  ADCISC_0 |= 0x8;
  
  // 4.2: Save the ADC value to global variable ADC_value
  ADC_value = ADCSSFIFO3_0 & 0xFFF;
}

void LED_on(char led_number)
{
  if (led_number == 1) { GPIODATA_N |= LED1; }
  else if (led_number == 2) { GPIODATA_N |= LED2; }
  else if (led_number == 3) { GPIODATA_F |= LED3; }
  else if (led_number == 4) { GPIODATA_F |= LED4; }
}

void LED_off(char led_number)
{
  if (led_number == 1) { GPIODATA_N &= ~LED1; }
  else if (led_number == 2) { GPIODATA_N &= ~LED2; }
  else if (led_number == 3) { GPIODATA_F &= ~LED3; }
  else if (led_number == 4) { GPIODATA_F &= ~LED4; }
}