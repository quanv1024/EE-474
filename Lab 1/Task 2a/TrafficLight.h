/*
  Quan Vo
  EE 474 - Hussein
  October 20, 2021
  Lab 1 Task 1b
  
  TrafficLight.h is header file for a finite machine implementing a traffic
  light system using 2 external switches and 3 external colored LEDs connected
  to GPIO Port L. The file contains function prototypes to initialize the LEDs
  and switches, turn on and off the LEDs, and poll for switch inputs as well
  as addresses of the registers required. The functions are generalized to be
  for any GPIO Port L connections as long as the pin positions are defined.
  The switches are defined as structs to allow simultaneous polling.
*/

#ifndef __TRAFFIC_LIGHT_H__
#define __TRAFFIC_LIGHT_H__

#include <stdint.h>

// Port L registers
#define GPIOAMSEL_L (*((volatile uint32_t *)0x40062528))
#define GPIODIR_L (*((volatile uint32_t *)0x40062400))
#define GPIODEN_L (*((volatile uint32_t *)0x4006251C))
#define GPIOAFSEL_L (*((volatile uint32_t *)0x40062420))
#define GPIODATA_L (*((volatile uint32_t *)0x400623FC))

// A number indicating which bit in a register corresponds to the pin.
// Ex: PC4 has PinPosition 0x10
typedef uint8_t PinPosition;

// create states for traffic light
typedef enum TL_States {stop, go, warn, off, initial} States;

// create events for switches
typedef enum SWITCH_Events {push, not_push} Events;

typedef struct ExternalSwitches {
  PinPosition pin;
  Events event;
} Button;

// Takes 3 pin positions, representing the 3 external LEDs connected to GPIO
// Port L. Initialize GPIO port L and required registers 
void LED_init(PinPosition led1, PinPosition led2, PinPosition led3);

// Takes a PinPosition and turn on the LED connected
// to Port L at the pin position
void LED_on(PinPosition pin);

// Takes a PinPosition and turn off the LED connected
// to Port L at the pin position
void LED_off(PinPosition pin);

// Takes 2 pin positions, representing the 2 external switches connected to
// GPIO Port L. Initialize GPIO port L and required registers 
void extern_switch_init(PinPosition switch1, PinPosition switch2);

// Takes a PinPosition and read the input of the switch connected to Port L at
// the pin position. If the switch is closed, return push, else return not_push
Events switch_input(PinPosition pin);

// Polls to see if the switches has been pressed. Creates a delay
//
// Arguments:
// - switch1: output parameter to an Event for switch_onoff. If the switch was
//   been pressed, value will change to push, otherwise not_push
//
// - switch2: output parameter to an Event for switch_pedestrian. If the switch
//   was been pressed, value will change to push, otherwise not_push
void poll_switches(Button *switch1, Button *switch2);

#endif //__TRAFFIC_LIGHT_H__
