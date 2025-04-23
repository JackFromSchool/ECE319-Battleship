// Sound.cpp
// Runs on MSPM0
// Sound assets in sounds/sounds.h
// your name
// your data 
#include <cstddef>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "LaunchPad.h"
#include "Sound.h"
#include "../inc/DAC5.h"

class SoundState {
  public:
    const uint8_t *current_sound;
    uint32_t index;
    uint32_t end;
    SoundState() {
      current_sound = NULL;
      index = 0;
      end = 0;
    }
};

static SoundState state;

void Sound_Init() {
  SysTick->CTRL  = 0x00;// disable SysTick during setup
  SysTick->LOAD = 7255;
  SysTick->VAL = 0;
  SCB->SHP[1] = SCB->SHP[1]&(~0xC0000000);  // set priority = 0 (bits 31,30)
  SysTick->CTRL = 0x00000006; // enable with core clock and interrupts

  DAC5_Init();
  state = SoundState();
}

void Sound_Start(const uint8_t *pt, uint32_t count) {
  if (state.current_sound != NULL) return;
  state.current_sound = pt;
  state.end = count;
  state.index = 0;
  SysTick->VAL = 0;
  SysTick->CTRL |= 0x1;
}


extern "C"
void SysTick_Handler(void) {
  if (state.index >= state.end) {
    state.current_sound = NULL;
    SysTick->CTRL &= ~(0x1);
    return;
  }
  uint8_t data = state.current_sound[state.index];
  DAC5_Out(data);
  state.index++;
}

