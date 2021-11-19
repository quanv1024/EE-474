/**
 * EE/CSE 474: Lab3 drivers header file
 */

// NOTE: All necessary functions for Task 1a have been declared in
// this header file, and thus you should not modify it for task 1a.
// However, you may modify it if you want to reuse it for other tasks.

#ifndef _Lab3_Inits_H_
#define _Lab3_Inits_H_

// Preset frequency for 120 MHZ, 60 MHZ, and 12 MHZ clock
// Pass in the preset to Timer1_Init and PLL_Init to configure
// the system clock to specified frequency
enum frequency {PRESET1 = 120, PRESET2 = 60, PRESET3 = 12};

// Initializes the PLL module and generates a system clock frequency
// that equal to the frequency preset.
// Returns 1 if configured successfully, -1 if you select a non-exist preset.
int PLL_Init(enum frequency freq);

// Initializes the 4 onboard LEDs.
void LED_Init(void);

// Initializes ADC Module 0 Sample Sequencer 3. The module is triggered by
// Timer module 0 subtimer A at 1 HZ. The interupt of ADC0 SS3 will be
// generated whenever the A/D conversion is done.
void ADCReadPot_Init(void);

// Initializes ADC Module 0 Sample Sequencer 3 to read from the internal
// temperature sensor. The module is triggered by Timer module 0 subtimer A
// at 1 HZ. The interupt of ADC0 SS3 will be generated whenever the A/D
// conversion is done.
void ADCReadTemp_Init(void);

// Initializes Timer 0A to trigger ADC0 at 1 HZ.
void TimerADCTriger_Init(void);

// Initializes Timer 0A to trigger interrupt at 1Hz
void TimerInterrupt_Init(void);

// Initializes GPIO to allow switches SW1 and SW2 to trigger interrupts
void GPIOInterrupt_Init(void);

// Initializes UART Module 0 with Baud rate of 9600, 1 stop bit, no parity bit,
// and 8-bit data transfer.
void UART0_Init(void);

// Initializes UART Module 2 with Baud rate of 9600, 1 stop bit, no parity bit,
// and 8-bit data transfers
void UART3_Init(void);
#endif  // _Lab3_Inits_H_
