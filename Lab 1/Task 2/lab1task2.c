/*
  Quan Vo
  EE 474 - Hussein
  October 15, 2021
  Lab 1 Task 2
  
  lab1task2.c is the main program to implement a traffic light system
  using 2 external switches and three external colored LEDs connected
  to GPIO Poirt L of the TIVA board.
*/

#include "../lab1.h"
#include "TrafficLight.h"
#include <stdint.h>

int main(void)
{
  // define pin positions for external LEDs and switches in Lab 1 Task 2
  PinPosition sw_onoff = 0x01;
  PinPosition sw_pedestrian = 0x02;
  PinPosition led_red = 0x04;
  PinPosition led_yellow = 0x08;
  PinPosition led_green = 0x10;

  // initiate external LED and switch GPIO pins
  LED_init(led_red, led_yellow, led_green);
  extern_switch_init(sw_pedestrian, sw_onoff);
  
  // initiate state and button variables
  States state = off;
  Button pedestrian_button, power_button;
  power_button.pin = sw_onoff;
  pedestrian_button.pin = sw_pedestrian;
  
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
        LED_off(led_red);
        LED_off(led_yellow);
        LED_off(led_green);
        
        poll_switches(&power_button, &pedestrian_button);
        
        if (power_button.event == push) { state = stop; }
        break;
        
      case stop:
        // turn on red, turn off yellow&green, then poll
        LED_on(led_red);
        LED_off(led_yellow);
        LED_off(led_green);
        
        poll_switches(&power_button, &pedestrian_button);
        
        if (power_button.event == push) { state = off; }
        else { state = go; }
        break;
      
      case go:
        // turn on green, turn off red&yellow, then poll
        LED_off(led_red);
        LED_off(led_yellow);
        LED_on(led_green);
        
        poll_switches(&power_button, &pedestrian_button);
        
        if (power_button.event == push) { state = off; }
        else if (pedestrian_button.event == push) { state = warn; }
        else { state = stop; }
        break;
        
      case warn:
        // turn on yellow, turn off red&green, then poll
        LED_off(led_red);
        LED_on(led_yellow);
        LED_off(led_green);
        
        poll_switches(&power_button, &pedestrian_button);
        
        if (power_button.event == push) { state = off; }
        else { state = stop; }
        break;
        
      default:
        state = initial;
        break;
    }
  }
  return 0;
}
