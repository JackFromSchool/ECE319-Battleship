// Sound.cpp
// Runs on MSPM0
// Sound assets in sounds/sounds.h
// your name
// your data 
#include <cstddef>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "Sound.h"
#include "../inc/DAC5.h"

static const uint8_t *current_sound;
static int32_t current_sound_count;
static int32_t count;

void SysTick_IntArm(uint32_t period, uint32_t priority){
  SysTick->CTRL = 0x00;      // disable SysTick during setup

  SysTick->LOAD = period-1;  // reload value
  SCB->SHP[1] = (SCB->SHP[1]&(~0xC0000000))|(priority<<30); // priority 2
  SysTick->VAL = 0;          // any write to VAL clears COUNT and sets VAL equal to LOAD
  SysTick->CTRL = 0x07;      // enable SysTick with 80 MHz bus clock and interrupts
}

// initialize a 11kHz SysTick, however no sound should be started
// initialize any global variables
// Initialize the 5 bit DAC
void Sound_Init(void){
  current_sound = NULL;
  current_sound_count = 0;
  count = 0;

  DAC5_Init();
  SysTick_IntArm(7111, 0);
}

extern "C" void SysTick_Handler(void);
void SysTick_Handler(void){ // called at 11 kHz
  if (count >= current_sound_count) {
    count = 0;
    current_sound_count = 0;
    current_sound = NULL;
    SysTick->CTRL &= ~(0x1);
    return;
  }

  DAC5_Out(current_sound[count]);
  count++;
}

//******* Sound_Start ************
// This function does not output to the DAC. 
// Rather, it sets a pointer and counter, and then enables the SysTick interrupt.
// It starts the sound, and the SysTick ISR does the output
// feel free to change the parameters
// Sound should play once and stop
// Input: pt is a pointer to an array of DAC outputs
//        count is the length of the array
// Output: none
// special cases: as you wish to implement
void Sound_Start(const uint8_t *pt, uint32_t count){
  if (current_sound != NULL) return;

  current_sound = pt;
  current_sound_count = count;
  count = 0;
  SysTick->VAL = 0;
  SysTick->CTRL |= 0x1;
}
