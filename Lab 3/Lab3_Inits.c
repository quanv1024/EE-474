/**
 * EE/CSE 474: Lab3 drivers starter code
 */

#include "PLL_Header.h"
#include "Lab3_Inits.h"

// STEP 0a: Include your header file here
#include "lab3.h"

int PLL_Init(enum frequency freq) {
    // Do NOT modify this function.
    MOSCCTL &= ~(0x4);                      // Power up MOSC
    MOSCCTL &= ~(0x8);                      // Enable MOSC
    while ((RIS & 0x100) == 0) {};          // Wait for MOSC to be ready
    RSCLKCFG |= (0x3 << 20);                // Select MOSC as system clock source
    RSCLKCFG |= (0x3 << 24);                // Select MOSC as PLL clock source

    PLLFREQ0 |= 0x60;                       // Set MINT field
    PLLFREQ1 |= 0x4;                        // Set N field

    MEMTIM0 &= ~((0xF << 22) | (0xF << 6));     // Reset FBCHT and EBCHT
    MEMTIM0 &= ~((0xF << 16) | (0xF << 0));     // Reset EWS and FWS
    MEMTIM0 &= ~((0x1 << 21) | (0x1 << 5));     // Reset FBCE and EBCE

    RSCLKCFG &= ~(0x1 << 28);                   // Temporarilly bypass PLL

    switch (freq) {
        case 120:
            MEMTIM0 |= (0x6 << 22) | (0x6 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x5 << 16) | (0x5 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x3;                        // Set PSYSDIV to use 120 MHZ clock
            RSCLKCFG &= ~0x3FC;                     // Update PSYSDIV field
            break;
        case 60:
            MEMTIM0 |= (0x3 << 22) | (0x3 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x2 << 16) | (0x2 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x7;                        // Set PSYSDIV to use 60 MHZ clock
            RSCLKCFG &= ~0x3F8;                     // Update PSYSDIV field
            break;
        case 12:
            MEMTIM0 |= (0x1 << 21) | (0x1 << 5);    // Set FBCE and EBCE
            RSCLKCFG |= 0x27;                       // Set PSYSDIV to use 12 MHZ clock
            RSCLKCFG &= ~0x3D8;                     // Update PSYSDIV field
            break;
        default:
            return -1;
    }

    RSCLKCFG |= (0x1 << 30);                // Enable new PLL settings
    PLLFREQ0 |= (0x1 << 23);                // Power up PLL
    while ((PLLSTAT & 0x1) == 0) {};        // Wait for PLL to lock and stabilize

    RSCLKCFG |= (0x1u << 31) | (0x1 << 28);  // Use PLL and update Memory Timing Register
    return 1;
}

void LED_Init(void) {
  // STEP 1: Initialize the 4 on board LEDs by initializing the corresponding
  // GPIO pins.

  volatile unsigned short delay = 0;
  RCGCGPIO = 0x1020 ;// enable GPIO Port F and Port N
  delay++;  // delay 2 clock cycles before accessing register
  delay++;
  
  // intialize D3 and D4
  GPIODIR_F = LED3 | LED4; // Set PF0, PF4 to output
  GPIODEN_F = LED3 | LED4; // set PF0, PF4 to digital port
  
  // intialize D1 and D2
  GPIODIR_N = LED1 | LED2; // Set PN0, PN1 to output
  GPIODEN_N = LED1 | LED2; // set PF0, PN1 to digital port
}

void ADCReadPot_Init(void) {
  // STEP 2: Initialize ADC0 SS3.
  // 2.1: Enable the ADC0 clock
  RCGCADC |= 0x1;
  
  // 2.2: Delay for RCGCADC (Refer to page 1073)
  volatile unsigned short delay = 0;
  delay++;
  delay++;
  
  // 2.3: Power up the PLL (if not already)
  PLLFREQ0 |= 0x00800000; // we did this for you
  
  // 2.4: Wait for the PLL to lock
  while (PLLSTAT != 0x1); // we did this for you
  
  // 2.5: Configure ADCCC to use the clock source defined by ALTCLKCFG
  ADCCC_0 |= 0x1;
  
  // 2.6: Enable clock to the appropriate GPIO Modules (Hint: Table 15-1)
  // Use AIN0 (PE3)
  RCGCGPIO |= 0x10;
  
  // 2.7: Delay for RCGCGPIO
  delay++;
  delay++;
  
  // 2.8: Set the GPIOAFSEL bits for the ADC input pins
  GPIOAFSEL_E |= 0x10;

  // 2.9: Clear the GPIODEN bits for the ADC input pins
  GPIODEN_E &= ~0x10;

  // 2.10: Disable the analog isolation circuit for ADC input pins (GPIOAMSEL)
  GPIOAMSEL_E |= 0x10;
  
  // 2.11: Disable sample sequencer 3 (SS3)
  ADCACTSS_0 &= ~0x8;

  // 2.12: Select timer as the trigger for SS3
  ADCEMUX_0 |= 0x5 << 12;

  // 2.13: Select the analog input channel for SS3 (Hint: Table 15-1)
  ADCSSMUX3_0 = 0x0;
  ADCSSEMUX3_0 = 0x0;
  
  // 2.14: Configure ADCSSCTL3 register
  ADCSSCTL3_0 = 0x6;

  // 2.15: Set the SS3 interrupt mask
  ADCIM_0 |= 0x8;

  // 2.16: Set the corresponding bit for ADC0 SS3 in NVIC
  // ADC0 SS3 vector 33 interrupt bit 17
  EN0 |= 0x1 << 17;

  // 2.17: Enable ADC0 SS3
  ADCACTSS_0 |= 0x8;
}

void ADCReadTemp_Init(void)
{
  // 2.1: Enable the ADC0 clock
  RCGCADC |= 0x1;
  
  // 2.2: Delay for RCGCADC (Refer to page 1073)
  volatile unsigned short delay = 0;
  delay++;
  delay++;
  
  // 2.3: Power up the PLL (if not already)
  PLLFREQ0 |= 0x00800000; // we did this for you
  
  // 2.4: Wait for the PLL to lock
  while (PLLSTAT != 0x1); // we did this for you
  
  // 2.5: Configure ADCCC to use the clock source defined by ALTCLKCFG
  ADCCC_0 |= 0x1;
  
  // 2.11: Disable sample sequencer 3 (SS3)
  ADCACTSS_0 &= ~0x8;

  // 2.12: Select timer as the trigger for SS3
  ADCEMUX_0 |= 0x5 << 12;

  // 2.14: Configure ADCSSCTL3 register
  ADCSSCTL3_0 = 0xE;

  // 2.15: Set the SS3 interrupt mask
  ADCIM_0 |= 0x8;

  // 2.16: Set the corresponding bit for ADC0 SS3 in NVIC
  // ADC0 SS3 vector 33 interrupt bit 17
  EN0 |= 0x1 << 17;

  // 2.17: Enable ADC0 SS3
  ADCACTSS_0 |= 0x8;
}

void TimerADCTriger_Init(void) {
  // STEP 3: Initialize Timer0A to trigger ADC0 at 1 HZ.
  // Hint: Refer to section 13.3.7 of the datasheet

  volatile unsigned short delay = 0;
  RCGCTIMER |= 0x1; // enable GP timer module 0
  delay++; // delay 2 clock cycles before accessing register
  delay++;
  
  GPTMCTL_0 = 0x0; // disable timer
  GPTMCFG_0 |= 0x0; // select 32 bit mode
  GPTMTAMR_0 |= 0x2; // select periodic timer mode and count down mode
  GPTMTAILR_0 = 60000000; // achieve 1 Hz blink rate
  GPTMADCEV_0 |= 0x1; // trigger interrupt on time-out
  GPTMCTL_0 |= 0x323; // enable timer and enable timer to tringger ADC
}

void TimerInterrupt_Init(void)
{
    // STEP 3: Initialize Timer0A to trigger ADC0 at 1 HZ.
  // Hint: Refer to section 13.3.7 of the datasheet

  volatile unsigned short delay = 0;
  RCGCTIMER |= 0x1; // enable GP timer module 0
  delay++; // delay 2 clock cycles before accessing register
  delay++;
  
  GPTMCTL_0 = 0x0; // disable timer
  GPTMCFG_0 |= 0x0; // select 32 bit mode
  GPTMTAMR_0 |= 0x2; // select periodic timer mode and count down mode
  GPTMTAILR_0 |= 60000000; // achieve 1 Hz blink rate
  GPTMIMR_0 |= 0x1; // enable timer A time-out interrupt mask
  GPTMADCEV_0 |= 0x1; // trigger interrupt on time-out
  GPTMCTL_0 |= 0x323; // enable timer and enable timer to tringger ADC
  EN0 = (0x1 << 19);
}

void GPIOInterrupt_Init(void)
{
  volatile unsigned short delay = 0;
  RCGCGPIO = 0x100; // enable GPIO Port J
  delay++;
  delay++;
  
  // configure registers for switch 1 and switch 2
  GPIODEN_J = SW1 | SW2;
  GPIOLOCK_J = 0x4C4F434B; // unlock GPIOCR register
  GPIOCR_J = SW1 | SW2; // allow pull up resistors to be hooked to PJ1 and PJ0
  GPIOPUR_J = SW1 | SW2; // connect pull up resistors to switches
  
    // configure registers for GPIO interrupts
  GPIOIM_J = 0x0; // mask interrupt
  GPIOIS_J &= ~0x3; // Pin 0 and 1 are edge sensitive
  GPIOIBE_J &= ~0x3; // interrupt controlled by IEV
  GPIOIEV_J &= ~0x3; // falling edge triggers interrupt (active low switch)
  GPIOICR_J |= 0x3; // clear interrupt flag
  GPIOIM_J |= 0x3; // mask interrupt
  EN1 = (0x1 << 19); // enable interrupt at NVIC
}

// NEXT STEP: Go to Lab3_Task1a.c and finish implementing ADC0SS3_Handler

void UART0_Init(void)
{
  volatile unsigned short delay  = 0;
  RCGCUART |= 0x1; // enable UART Module 0
  delay++;
  delay++;
  
  RCGCGPIO |= 0x1; // enable GPIO Port A
  delay++;
  delay++;
  
  // PA0 = Rx, PA1 = Tx
  GPIOAFSEL_A |= 0x3; // Use PA0 and PA1 alternate function
  GPIOPCTL_A |= 0x11; // PA0 and PA1 act as UART0 Rx and Tx
  GPIODEN_A |=0x3;
    
  UARTCTL_0 &= ~0x1; // disable UART0
  
  // configure UART Baud rate to 9600 for 16MHz clock
  UARTLCRH_0 &= ~0x10;
  UARTIBRD_0 |= 104;
  UARTFBRD_0 |= 11;
  
  UARTLCRH_0 |= 0x60; // 8 bit transmission
  UARTLCRH_0 |= 0x10; // FIFO
  UARTLCRH_0 &= ~0x8; // 1 stop bit
  UARTLCRH_0 &= ~0x2; // no parity
  
  UARTCC_0 = 0x5; // UART0 uses cvlock defined by ALTCLKCFG
  UARTCTL_0 |= 0x101; // enable UART0 Tx
}

void UART3_Init(void)
{
  volatile unsigned short delay  = 0;
  RCGCUART |= 0x8; // enable UART Module 3
  delay++;
  delay++;
  
  RCGCGPIO |= 0x1; // enable GPIO Port A
  delay++;
  delay++;
  
  // PA5 = Rx, PA5 = Tx
  GPIOAFSEL_A |= 0x30; // Use PA0 and PA1 alternate function
  GPIOPCTL_A |= 0x110000; // PA0 and PA1 act as UART0 Rx and Tx
  GPIODEN_A |= 0x30;
    
  UARTCTL_3 &= ~0x1; // disable UART0
  
  // configure UART Baud rate to 9600 for 16MHz clock
  UARTLCRH_3 &= ~0x10;
  UARTIBRD_3 |= 104;
  UARTFBRD_3 |= 11;
  
  UARTLCRH_3 |= 0x60; // 8 bit transmission
  UARTLCRH_3 &= ~0x10; // disable FIFO
  UARTLCRH_3 &= ~0x8; // 1 stop bit
  UARTLCRH_3 &= ~0x2; // no parity
  
  UARTCC_3 = 0x5; // UART0 uses cvlock defined by ALTCLKCFG
  UARTCTL_3 |= 0x101; // enable UART3 Tx
}




