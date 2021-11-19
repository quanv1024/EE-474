/*
  Quan Vo
  EE 474-Fall 2021-Hussein
  October 24, 2021
  Lab 2 Task 2c
  
  lab2task2c.c
*/

#include "C:\Users\quanv\Documents\EE 474\EE 474 Labs\lab2\lab2.h"
#include "TrafficLight.h"
#include <stdint.h>

// define pin positions for external LEDs and switches as global variables
#define sw_onoff 0x01
#define sw_pedestrian 0x02
#define led_red 0x04
#define led_yellow 0x08
#define led_green 0x10

// button and state elapsed time variables
int onoff_push_time;
int pedestrian_push_time;
int state_time_elapsed;

void timer_interrupt_init();

int main(void)
{
  // initiate external LED and switch GPIO pins
  LED_init(led_red, led_yellow, led_green);
  extern_switch_init(sw_pedestrian, sw_onoff);
  timer_interrupt_init();
  
  // initiate state and elapsed time variables
  States state = off;
  onoff_push_time = 0;
  pedestrian_push_time = 0;
  state_time_elapsed = 0;

  while (1)
  {    
    // button next state 
    switch(state)
    {
      case initial:
        state = off;
        break;
     
      case off:
        // turn off leds, then check power button input
        TL_LED_off(led_red);
        TL_LED_off(led_yellow);
        TL_LED_off(led_green);
        
        if (onoff_push_time == 2)
        {
          state = go;
          state_time_elapsed = 0;
          onoff_push_time = 0;
        }
        break;
        
      case stop:
        // turn on red, turn off yellow&green, then poll
        TL_LED_on(led_red);
        TL_LED_off(led_yellow);
        TL_LED_off(led_green);
        
        if (onoff_push_time == 2)
        {
          state = off;
          onoff_push_time = 0;
        }
        else if (state_time_elapsed == 5)
        {
          state = go;
          state_time_elapsed = 0;
          pedestrian_push_time = 0;
        }
        break;
      
      case go:
        // turn on green, turn off red&yellow, then poll
        TL_LED_off(led_red);
        TL_LED_off(led_yellow);
        TL_LED_on(led_green);
        
        if (onoff_push_time == 2)
        {
          state = off;
          onoff_push_time = 0;
        }
        else if (pedestrian_push_time == 3)
        {
          state = warn;
          state_time_elapsed = 0;
          pedestrian_push_time = 0;
        }
        else if (state_time_elapsed == 5)
        {
          state = stop;
          state_time_elapsed = 0;
        }
        break;
        
      case warn:
        // turn on yellow, turn off red&green, then poll
        TL_LED_off(led_red);
        TL_LED_on(led_yellow);
        TL_LED_off(led_green);
        
        if (onoff_push_time == 2)
        {
          state = off;
          onoff_push_time = 0;
        }
        else if (state_time_elapsed == 5)
        {
          state = stop;
          state_time_elapsed = 0;
        }
        break;
        
      default:
        state = initial;
        break;
    }
  }

  return 0;
}

void Timer0A_Handler()
{
  restart_timer();
  
  if (switch_input(sw_onoff) == not_push)
  {
    onoff_push_time = 0;
  }
  else
  {
    onoff_push_time += 1;
  }
  
  if (switch_input(sw_pedestrian) == not_push)
  {
    pedestrian_push_time = 0;
  }
  else
  {
    pedestrian_push_time += 1;
  }
  
  state_time_elapsed += 1;
}


