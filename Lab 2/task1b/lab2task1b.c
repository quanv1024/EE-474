/*
  Quan Vo
  EE 474-Fall 2021-Hussein
  October 24, 2021
  Lab 2 Task 1b
  
  lab2task1b.c
*/

#include "C:\Users\quanv\Documents\EE 474\EE 474 Labs\lab2\lab2.h"
#include "TrafficLight.h"
#include <stdint.h>

// define pin positions for external LEDs and switches as global variables
#define sw_onoff 0x01;
#define sw_pedestrian = 0x02;
#define led_red = 0x04;
#define led_yellow = 0x08;
#define led_green = 0x10;

// Poll timer and switch input. If switch is push and timer timed out,
// increment switch_push_time; if switch is push and timer has not
// timed out, no change; if switch not pushed, reset switch_push_time to zero
int poll_timer_switch(PinPosition pin, int currentSwitchVal);

// Poll timer. If timer has timed out, increment time elapsed since
// state started
int update_state_time_elapsed(int currentValue);

int main(void)
{
  // initiate external LED and switch GPIO pins
  LED_init(led_red, led_yellow, led_green);
  extern_switch_init(sw_pedestrian, sw_onoff);
  timer_init();
  
  // initiate state and button variables
  States state = off;
  int onoff_push_time = 0;
  int pedestrian_push_time = 0;
  int time_elapsed = 0;
  
  while (1)
  {
    onoff_push_time = poll_timer_switch(sw_onoff, onoff_push_time);
    pedestrian_push_time = poll_timer_switch(sw_pedestrian,
                                             pedestrian_push_time);
    time_elapsed = update_state_time_elapsed(time_elapsed);
    if (is_timer_timed_out())
    {
      restart_timer();
    }
    
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
          time_elapsed = 0;
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
        else if (time_elapsed == 5)
        {
          state = go;
          time_elapsed = 0;
          pedestrian_push_time = 0;
        }
        break;
      
      case go:
        // turn on green, turn off red&yellow, then poll
        LED_off(led_red);
        LED_off(led_yellow);
        LED_on(led_green);
        
        if (onoff_push_time == 2)
        {
          state = off;
          onoff_push_time = 0;
        }
        else if (pedestrian_push_time == 2)
        {
          state = warn;
          time_elapsed = 0;
          pedestrian_push_time = 0;
        }
        else if (time_elapsed == 5)
        {
          state = stop;
          time_elapsed = 0;
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
        else if (time_elapsed == 5)
        {
          state = stop;
          time_elapsed = 0;
        }
        break;
        
      default:
        state = initial;
        break;
    }
  }
}

int poll_timer_switch(PinPosition pin, int currentSwitchVal)
{
  if (switch_input(pin) == not_push)
  { 
    return 0;
  }
  else if (is_timer_timed_out())
  {
    return currentSwitchVal + 1;
  }
  else
  {
    return currentSwitchVal;
  }
}

int update_state_time_elapsed(int currentValue)
{
  if (is_timer_timed_out())
  {
    return currentValue + 1;
  }
  else
  {
    return currentValue;
  }
}