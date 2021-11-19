#include "C:\Users\quanv\Documents\EE 474\EE 474 Labs\lab2\lab2.h"
#include <stdint.h>

void timer_init()
{
  volatile unsigned short delay = 0;
  RCGCTIMER = 0x1; // enable GP timer module 0
  delay++; // delay 2 clock cycles before accessing register
  delay++;
  
  GPTMCTL_0 = 0x0; // disable timer
  GPTMCFG_0 = 0x0; // select 32 bit mode
  GPTMTAMR_0 = 0x2; // select periodic timer mode and count down mode
  GPTMTAILR_0 = 16000000; // achieve 1 Hz blink rate
  GPTMCTL_0 = 0x101; // enable timer
}

void timer_interrupt_init()
{
  volatile unsigned short delay = 0;
  RCGCTIMER = 0x1; // enable GP timer module 0
  delay++; // delay 2 clock cycles before accessing register
  delay++;
  
  GPTMCTL_0 = 0x0; // disable timer
  GPTMCFG_0 = 0x0; // select 32 bit mode
  GPTMTAMR_0 = 0x2; // select periodic timer mode and count down mode
  GPTMTAILR_0 = 16000000; // achieve 1 Hz blink rate
  GPTMIMR_0 = 0x1; // enable timer A time-out interrupt mask
  GPTMCTL_0 = 0x101; // enable timer
  
  EN0 = (0x1 << 19);
}

int is_timer_timed_out()
{
  return (GPTMRIS_0 & 0x1) == 0x1;
}

void restart_timer()
{
  GPTMICR_0 = 0x1;
}

void LED_on(uint8_t led_number)
{
  if (led_number == 1) { GPIODATA_N |= LED1; }
  else if (led_number == 2) { GPIODATA_N |= LED2; }
  else if (led_number == 3) { GPIODATA_F |= LED3; }
  else if (led_number == 4) { GPIODATA_F |= LED4; }
}

void LED_off(uint8_t led_number)
{
  if (led_number == 1) { GPIODATA_N &= ~LED1; }
  else if (led_number == 2) { GPIODATA_N &= ~LED2; }
  else if (led_number == 3) { GPIODATA_F &= ~LED3; }
  else if (led_number == 4) { GPIODATA_F &= ~LED4; }
}