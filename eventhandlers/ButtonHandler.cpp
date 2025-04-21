#include "ButtonHandler.h"
#include "Events.h"


class ButtonState {
  public:
    uint32_t lastValue0;
    uint32_t lastValue1;
    uint32_t lastValue2;
    uint32_t lastValue3;
    ButtonState();
};



void ButtonHandlerInit() {
    // Configure Button IO
    IOMUX->SECCFG.PINCM[PA15INDEX] = 0x40081; //SW4
    IOMUX->SECCFG.PINCM[PA16INDEX] = 0x40081; //SW3
    IOMUX->SECCFG.PINCM[PA17INDEX] = 0x40081; //SW2
    IOMUX->SECCFG.PINCM[PA18INDEX] = 0x40081; //SW1    

/*
    GPIOB->POLARITY31_16 &= ~((1<<16)|(1<<17)|(1<<18)); // configuring pins 16-18 to detect rising edge
    GPIOB->POLARITY15_0 &= ~(1<<15); //configures pin 15 to detect rising edge 
    GPIOB->CPU_INT.ICLR = (1<<15)|(1<<16)|(1<<17)|(1<<18); // clear bits 15-18
    GPIOB->CPU_INT.IMASK = (1<<15)|(1<<16)|(1<<17)|(1<<18); // arm 15-18
    NVIC->IP[0] = (NVIC->IP[0]&(~0x0000FF00))|2<<14; // set priority (bits 15,14) IRQ 1
    NVIC->ISER[0] = 1 << 1; // Button interrupt
    */
}


void Button_IRQHandler(void) { 
  //Count++; // number of touches
  //GPIOB->DOUTTGL31_0 = RED; // toggle PB26
  //Button0 is 18, Button 2 is 17, button 1 is 16, button 3 is 15
  //Maybe changing the polarity register to detect falling edge after it detects a rising edge
  
  //Check which pin is set high, then queue the ENUM for that pin onto the global Queue, wait for the button to be released (while loop),
  //How to represent low values because edge triggered interrupt doesn't do that


  //Each condition checks current value of pin and previous value to determine if button is pressed and unpressed
  if((GPIOB->DOUT31_0 &= (1<<15) != 0) && engineState.eventQueue.getLastElement() == BUTTON3_UNPRESS)
  {
    engineState.eventQueue.put(BUTTON3_PRESS);
    //while(GPIOB->DOUT31_0 &= (1<<15) != 0) {}
    //allEvents.put(BUTTON3_UNPRESS);
  }
  else if((GPIOB->DOUT31_0 &= (1<<15) == 0) && engineState.eventQueue.getLastElement() == BUTTON3_PRESS)
  {
    engineState.eventQueue.put(BUTTON3_UNPRESS);
  }
  else if((GPIOB->DOUT31_0 &= (1<<16) != 0) && engineState.eventQueue.getLastElement() == BUTTON1_UNPRESS)
  {
    engineState.eventQueue.put(BUTTON1_PRESS);
    //while(GPIOB->DOUT31_0 &= (1<<16) != 0) {}
    //allEvents.put(BUTTON1_UNPRESS);
  }
  else if((GPIOB->DOUT31_0 &= (1<<16) == 0) && engineState.eventQueue.getLastElement() == BUTTON1_PRESS)
  {
    engineState.eventQueue.put(BUTTON1_UNPRESS);
  }
  else if((GPIOB->DOUT31_0 &= (1<<17) != 0) && engineState.eventQueue.getLastElement() == BUTTON2_PRESS)
  {
    engineState.eventQueue.put(BUTTON2_PRESS);
    //while(GPIOB->DOUT31_0 &= (1<<17) != 0) {}
    //allEvents.put(BUTTON2_UNPRESS);
  }
  else if((GPIOB->DOUT31_0 &= (1<<17) == 0) && engineState.eventQueue.getLastElement() == BUTTON2_UNPRESS)
  {
    engineState.eventQueue.put(BUTTON2_UNPRESS);
  }
  else if((GPIOB->DOUT31_0 &= (1<<18) != 0) && engineState.eventQueue.getLastElement() == BUTTON0_UNPRESS)
  {
    engineState.eventQueue.put(BUTTON0_PRESS);
    //while(GPIOB->DOUT31_0 &= (1<<18) != 0) {}
    //allEvents.put(BUTTON0_UNPRESS);
  }
  else if((GPIOB->DOUT31_0 &= (1<<18) == 0) && engineState.eventQueue.getLastElement() == BUTTON0_UNPRESS)
  {
    engineState.eventQueue.put(BUTTON0_UNPRESS);
  }
  //GPIOB->CPU_INT.ICLR = 0x00200000; // clear bit 21
}
