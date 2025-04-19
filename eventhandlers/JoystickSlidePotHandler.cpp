#include "JoystickSlidePotHandler.h"
#include "../inc/Clock.h"
#include "../inc/Timer.h"
#include "Events.h"
#include "Globals.h"

// PA27 is Vertical
// PA26 is Horrizontal
// PB18 is SlidePot

class JoystickSlidePotState {
    public:
        enum Event lastJoystickEvent;
        enum Event lastSlidePotEvent;
        JoystickSlidePotState();
};

JoystickSlidePotState::JoystickSlidePotState() {
    this->lastJoystickEvent = JOYSTICK_RETURN;
    this->lastSlidePotEvent = SLIDEPOT0;
}

static JoystickSlidePotState state = JoystickSlidePotState();

void joystickSlidePotHandlerInit() {
    // Init Inputs
    IOMUX->SECCFG.PINCM[PA26INDEX] = 0x40081;
    IOMUX->SECCFG.PINCM[PA27INDEX] = 0x40081;

    // ADC0 Initialization - Joystick
    ADC0->ULLMEM.GPRCM.RSTCTL = 0xB1000003; // 1) reset
    ADC0->ULLMEM.GPRCM.PWREN = 0x26000001;  // 2) activate
    Clock_Delay(24);                        // 3) wait
    ADC0->ULLMEM.GPRCM.CLKCFG = 0xA9000000; // 4) ULPCLK
    ADC0->ULLMEM.CLKFREQ = 7;               // 5) 40-48 MHz
    ADC0->ULLMEM.CTL0 = 0x03010000;         // 6) divide by 8
    ADC0->ULLMEM.CTL1 = 0x00010000;         // 7) mode
    ADC0->ULLMEM.CTL2 = 0x01000000;         // 8) MEMRES
    ADC0->ULLMEM.MEMCTL[0] = 0;             // 9) channel 6 is PB20
    ADC0->ULLMEM.MEMCTL[1] = 1;
    ADC0->ULLMEM.SCOMP0 = 0;                // 10) 8 sample clocks
    ADC0->ULLMEM.CPU_INT.IMASK = 0;         // 11) no interrupt

    // ADC1 Initialization - SlidePot
    ADC1->ULLMEM.GPRCM.RSTCTL = 0xB1000003; // 1) reset
    ADC1->ULLMEM.GPRCM.PWREN = 0x26000001;  // 2) activate
    Clock_Delay(24);                        // 3) wait
    ADC1->ULLMEM.GPRCM.CLKCFG = 0xA9000000; // 4) ULPCLK
    ADC1->ULLMEM.CLKFREQ = 7;               // 5) 40-48 MHz
    ADC1->ULLMEM.CTL0 = 0x03010000;         // 6) divide by 8
    ADC1->ULLMEM.CTL1 = 0x00000000;         // 7) mode
    ADC1->ULLMEM.CTL2 = 0x00000000;         // 8) MEMRES
    ADC1->ULLMEM.MEMCTL[0] = 5;
    ADC1->ULLMEM.SCOMP0 = 0;                // 10) 8 sample clocks
    ADC1->ULLMEM.CPU_INT.IMASK = 0;         // 11) no interrupt
    // Arm Interrupts
    TimerG12_IntArm(2666666, 2);

}

extern "C"
void TIMG12_IRQHandler(void) {
    if ((TIMG12->CPU_INT.IIDX) == 1) {
        ADC0->ULLMEM.CTL0 |= 0x00000001;             // 1) enable conversions
        ADC0->ULLMEM.CTL1 |= 0x00000100;             // 2) start ADC
        uint32_t volatile delay=ADC0->ULLMEM.STATUS; // 3) time to let ADC start
        while((ADC0->ULLMEM.STATUS&0x01)==0x01){}    // 4) wait for completion
        uint16_t horrizontal_result = ADC0->ULLMEM.MEMRES[0];
        uint16_t vertical_result = ADC0->ULLMEM.MEMRES[1];

        ADC1->ULLMEM.CTL0 |= 0x00000001;             // 1) enable conversions
        ADC1->ULLMEM.CTL1 |= 0x00000100;             // 2) start ADC
        uint32_t volatile delay2=ADC1->ULLMEM.STATUS; // 3) time to let ADC start
        while((ADC1->ULLMEM.STATUS&0x01)==0x01){}    // 4) wait for completion
        uint16_t slidepot_result = ADC1->ULLMEM.MEMRES[0];

        enum Event slideEvent;
        if (slidepot_result > 3510) {
            slideEvent = SLIDEPOT0;
        } else if (slidepot_result > 2925) {
            slideEvent = SLIDEPOT1;
        } else if (slidepot_result > 2340) {
            slideEvent = SLIDEPOT2;
        } else if (slidepot_result > 1755) {
            slideEvent = SLIDEPOT3;
        } else if (slidepot_result > 1170) {
            slideEvent = SLIDEPOT4;
        } else if (slidepot_result > 585) {
            slideEvent = SLIDEPOT5;
        } else {
            slideEvent = SLIDEPOT6;
        }
        
        if (state.lastSlidePotEvent != slideEvent) {
            engineState.eventQueue.put(slideEvent);
            state.lastSlidePotEvent = slideEvent;
        }

        enum Event joystickEvent;
        if (vertical_result > 3500) {
            if (horrizontal_result < 500) {
                joystickEvent = JOYSTICK_UPLEFT;
            } else if (horrizontal_result > 3500) {
                joystickEvent = JOYSTICK_UPRIGHT;
            } else {
                joystickEvent = JOYSTICK_UP;
            }
        } else if (vertical_result < 500) {
            if (horrizontal_result < 500) {
                joystickEvent = JOYSTICK_DOWNLEFT;
            } else if (horrizontal_result > 3500) {
                joystickEvent = JOYSTICK_DOWNRIGHT;
            } else {
                joystickEvent = JOYSTICK_DOWN;
            }
        } else {
            if (horrizontal_result < 500) {
                joystickEvent = JOYSTICK_LEFT;
            } else if (horrizontal_result > 3500) {
                joystickEvent = JOYSTICK_RIGHT;
            } else {
                joystickEvent = JOYSTICK_RETURN;
            }
        }

        if (state.lastJoystickEvent != joystickEvent) {
            engineState.eventQueue.put(joystickEvent);
            state.lastJoystickEvent = joystickEvent;
        }
    }
}