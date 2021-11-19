/*
  Quan Vo
  EE 474-Fall 2021-Hussein
  November 17, 2021
  Lab 3 Task 2b
  
  lab3task2b.c is the main file for Lab 3 Task 2b.
*/

#include "..\Lab3_Inits.h"
#include "..\lab3.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
  UART3_Init();
  char input_char;
  while (1)
  {
  // wait until recieves a character
    // copy character into UARTDR
    if ((UARTFR_3 & 0x40) != 0)
    {
      input_char = UARTDR_3 & 0xFF;
      while ((UARTFR_3 & 0x8) != 0) {}
      UARTDR_3 = input_char;
    }
  }
  return 0; 
}