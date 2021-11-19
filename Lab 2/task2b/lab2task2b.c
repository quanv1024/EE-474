
#include "C:\Users\quanv\Documents\EE 474\EE 474 Labs\lab2\lab2.h"
#include <stdint.h>

void GPIO_interrupt_init();
void LED_on(uint8_t led_number);
void LED_off(uint8_t led_number);
void clear_GPIO_interrupt();

int main(void)
{
  GPIO_interrupt_init();
  timer_init();
  // led on = 1, led off = 0
  uint8_t led_state = 0;
  
  // continuously poll timer. Change led state when timed-out
  // When sw2 is pressed, timer will stop counting and blinking will stop
  while (1)
  {
    if (is_timer_timed_out())
    {
      if (led_state == 0)
      {
        LED_on(1);
        led_state = 1;
      }
      else if (led_state == 1)
      {
        LED_off(1);
        led_state = 0; 
      }
      restart_timer();
    }
  }
  return 0;
}

void GPIO_interrupt_init()
{
  volatile unsigned short delay = 0;
  RCGCGPIO = 0x1100 ;// enable GPIO Port J and Port N
  delay++;  // delay 2 clock cycles before accessing register
  delay++;
  
  // configure registers for LED1 and LED2
  GPIODIR_N = LED1 | LED2; // Set PN0, PN1 to output
  GPIODEN_N = LED1 | LED2; // set PN0, PN1 to digital port
  
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
  PRI12 &= ~(0x7<<29); // priority level 0 
}

void clear_GPIO_interrupt()
{
  GPIOICR_J |= 0x3;
}

void GPIOJ_Handler(void)
{
  clear_GPIO_interrupt();
  // sw1 pressed
  if ((~GPIODATA_J & SW1) == SW1)
  {
    // stop timer
    GPTMCTL_0 = 0x0;
    // turn on led2
    LED_on(2);
  }
  else if ((~GPIODATA_J & SW2) == SW2) // sw2 pressed
  {
    // turn off led2
    LED_off(2);
    // resume timer
    GPTMCTL_0 = 0x101; // enable timer
  }
}