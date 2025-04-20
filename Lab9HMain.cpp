// Lab9HMain.cpp
// Runs on MSPM0G3507
// Lab 9 ECE319H
// Your name
// Last Modified: 12/26/2024

#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "../inc/SlidePot.h"
#include "../inc/DAC5.h"
#include "../inc/UART.h"
#include "EngineState.h"
#include "SmallFont.h"
#include "Sound.h"
#include "Events.h"
#include "Globals.h"
#include "images/ImageTools.h"
#include "images/images.h"
#include "eventhandlers/JoystickSlidePotHandler.h"
#include "eventhandlers/ButtonHandler.h"
extern "C" void __disable_irq(void);
extern "C" void __enable_irq(void);
extern "C" void TIMG12_IRQHandler(void);
// ****note to ECE319K students****
// the data sheet says the ADC does not work when clock is 80 MHz
// however, the ADC seems to work on my boards at 80 MHz
// I suggest you try 80MHz, but if it doesn't work, switch to 40MHz
void PLL_Init(void){ // set phase lock loop (PLL)
  // Clock_Init40MHz(); // run this line for 40MHz
  Clock_Init80MHz(0);   // run this line for 80MHz
}

uint32_t M=1;
uint32_t Random32(void){
  M = 1664525*M+1013904223;
  return M;
}
uint32_t Random(uint32_t n){
  return (Random32()>>16)%n;
}

SlidePot Sensor(1500,0); // copy calibration from Lab 7
/*
void TIMG12_IRQHandler(void){uint32_t pos,msg;
  if((TIMG12->CPU_INT.IIDX) == 1){
    Button_IRQHandler();
  }
}
*/

//So if I have a timer that checks the button's input every certain period, then it needs to check both the current input and the previous input
//in order to determine whether the button has been pressed or not. How can I determine the button's previous input? Static Variable?

uint8_t TExaS_LaunchPadLogicPB27PB26(void){
  return (0x80|((GPIOB->DOUT31_0>>26)&0x03));
}

typedef enum {English, Spanish, Portuguese, French} Language_t;
Language_t myLanguage=English;
typedef enum {HELLO, GOODBYE, LANGUAGE} phrase_t;
const char Hello_English[] ="Hello";
const char Hello_Spanish[] ="\xADHola!";
const char Hello_Portuguese[] = "Ol\xA0";
const char Hello_French[] ="All\x83";
const char Goodbye_English[]="Goodbye";
const char Goodbye_Spanish[]="Adi\xA2s";
const char Goodbye_Portuguese[] = "Tchau";
const char Goodbye_French[] = "Au revoir";
const char Language_English[]="English";
const char Language_Spanish[]="Espa\xA4ol";
const char Language_Portuguese[]="Portugu\x88s";
const char Language_French[]="Fran\x87" "ais";
const char *Phrases[3][4]={
  {Hello_English,Hello_Spanish,Hello_Portuguese,Hello_French},
  {Goodbye_English,Goodbye_Spanish,Goodbye_Portuguese,Goodbye_French},
  {Language_English,Language_Spanish,Language_Portuguese,Language_French}
};
// use main1 to observe special characters
int main1(void){ // main1
    char l;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  buttonHandlerInit();
  TimerG12_IntArm(2666667, 0); //Initialize the timer at 30Hz
  __enable_irq();

  /*
  ST7735_InitPrintf();
  ST7735_FillScreen(0x0000);            // set screen to black
  for(int myPhrase=0; myPhrase<= 2; myPhrase++){
    for(int myL=0; myL<= 3; myL++){
         ST7735_OutString((char *)Phrases[LANGUAGE][myL]);
      ST7735_OutChar(' ');
         ST7735_OutString((char *)Phrases[myPhrase][myL]);
      ST7735_OutChar(13);
    }
  }
  Clock_Delay1ms(3000);
  ST7735_FillScreen(0x0000);       // set screen to black
  l = 128;
  while(1){
    Clock_Delay1ms(2000);
    for(int j=0; j < 3; j++){
      for(int i=0;i<16;i++){
        ST7735_SetCursor(7*j+0,i);
        ST7735_OutUDec(l);
        ST7735_OutChar(' ');
        ST7735_OutChar(' ');
        ST7735_SetCursor(7*j+4,i);
        ST7735_OutChar(l);
        l++;
      }
    }
  }
  */
}

// use main2 to observe graphics
int main(void){ // main2
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  //ST7735_SetRotation(2);
  ST7735_FillScreen(ST7735_BLACK);

  Sprite TwoSpaceBattleship1 = Sprite(two_space_battleship1, BOARDSPACEX(0), BOARDSPACEY(9, 22), 11, 22);
  Sprite TwoSpaceBattleship2 = Sprite(two_space_battleship2, BOARDSPACEX(2), BOARDSPACEY(9, 22), 11, 22);
  Sprite ThreeSpaceBattleship = Sprite(three_space_battleship, BOARDSPACEX(4), BOARDSPACEY(9, 33), 11, 33);
  Sprite FourSpaceBattleship = Sprite(four_space_battleship, BOARDSPACEX(6), BOARDSPACEY(9, 44), 11, 44);
  Sprite FiveSpaceBattleship = Sprite(five_space_battleship, BOARDSPACEX(8), BOARDSPACEY(9, 55), 11, 55);

  ST7735_DrawBitmap(0, 160, battleship_board, 128, 160);

  {
    uint16_t sprite_temp[TwoSpaceBattleship1.size()];
    TwoSpaceBattleship1.fill_background(battleship_board, sprite_temp);
    DRAWSPRITE(TwoSpaceBattleship1, sprite_temp);
  }

  {
    uint16_t sprite_temp[TwoSpaceBattleship2.size()];
    TwoSpaceBattleship2.fill_background(battleship_board, sprite_temp);
    DRAWSPRITE(TwoSpaceBattleship2, sprite_temp);
  }

  {
    uint16_t sprite_temp[ThreeSpaceBattleship.size()];
    ThreeSpaceBattleship.fill_background(battleship_board, sprite_temp);
    DRAWSPRITE(ThreeSpaceBattleship, sprite_temp);
  }

  {
    uint16_t sprite_temp[FourSpaceBattleship.size()];
    FourSpaceBattleship.fill_background(battleship_board, sprite_temp);
    DRAWSPRITE(FourSpaceBattleship, sprite_temp);
  }

  {
    uint16_t sprite_temp[FiveSpaceBattleship.size()];
    FiveSpaceBattleship.fill_background(battleship_board, sprite_temp);
    DRAWSPRITE(FiveSpaceBattleship, sprite_temp);
  }
  
  
  while(1){
  }
}

// use main3 to test switches and LEDs
int main3(void){ // main3
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  joystickSlidePotHandlerInit();
  ST7735_InitPrintf();
  ST7735_SetCursor(0, 0);
  ST7735_FillScreen(ST7735_BLACK);
  __enable_irq();
  IOMUX->SECCFG.PINCM[PA31INDEX] = 0x81;
  IOMUX->SECCFG.PINCM[PA28INDEX] = 0x81;
  IOMUX->SECCFG.PINCM[PA24INDEX] = 0x81;
  GPIOA->DOE31_0 |= (1<<31) | (1<<28) | (1<<24);
  GPIOA->DOUT31_0 = (1<<31) | (1<<28) | (1<<24);
  while(1){
    enum Event next = engineState.pollQueue();
    switch (next) {
      case JOYSTICK_RETURN:
        printf("Joystick Return"); break;
      case JOYSTICK_DOWN:
        printf("Joystick Down"); break;
      case JOYSTICK_DOWNLEFT:
        printf("Joystick Down Left"); break;
      case JOYSTICK_DOWNRIGHT:
        printf("Joystick Down Right"); break;
      case JOYSTICK_RIGHT:
        printf("Joystick Right"); break;
      case JOYSTICK_UPRIGHT:
        printf("Joystick Up Right"); break;
      case JOYSTICK_UPLEFT:
        printf("Joystick Up Left"); break;
      case JOYSTICK_LEFT:
        printf("Joystick Left"); break;
      case JOYSTICK_UP:
        printf("Joystick Up"); break;
      case BUTTON0_UNPRESS:
        printf("Button0 Unpress"); break;
      case BUTTON1_UNPRESS:
        printf("Button1 Unpress"); break;
      case BUTTON2_UNPRESS:
        printf("Button2 Unpress"); break;
      case BUTTON3_UNPRESS:
        printf("Button3 Unpress"); break;
      case BUTTON0_PRESS:
        printf("Button0 Press"); break;
      case BUTTON1_PRESS:
        printf("Button1 Press"); break;
      case BUTTON2_PRESS:
        printf("Button2 Press"); break;
      case BUTTON3_PRESS:
        printf("Button3 Press"); break;
      case SLIDEPOT0:
        printf("SlidePot 0"); break;
      case SLIDEPOT1:
        printf("SlidePot 1"); break;
      case SLIDEPOT2:
        printf("SlidePot 2"); break;
      case SLIDEPOT3:
        printf("SlidePot 3"); break;
      case SLIDEPOT4:
        printf("SlidePot 4"); break;
      case SLIDEPOT5:
        printf("SlidePot 5"); break;
      case SLIDEPOT6:
        printf("SlidePot 6"); break;
      default:
        printf("Unknown Event,\nvalue = %d", next); break;
    }
    Clock_Delay1ms(250);
    ST7735_SetCursor(0, 0);
    printf("                  \n                 ");
    ST7735_SetCursor(0, 0);
  }
}
// use main4 to test sound outputs
int main4(void){ uint32_t last=0,now;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Sound_Init();  // initialize sound
  TExaS_Init(ADC0,6,0); // ADC1 channel 6 is PB20, TExaS scope
  __enable_irq();
  while(1){
    if((last == 0)&&(now == 1)){
      Sound_Shoot(); // call one of your sounds
    }
    if((last == 0)&&(now == 2)){
      Sound_Killed(); // call one of your sounds
    }
    if((last == 0)&&(now == 4)){
      Sound_Explosion(); // call one of your sounds
    }
    if((last == 0)&&(now == 8)){
      Sound_Fastinvader1(); // call one of your sounds
    }
    // modify this to test all your sounds
  }
}
// ALL ST7735 OUTPUT MUST OCCUR IN MAIN
int main5(void){ // final main
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  ST7735_FillScreen(ST7735_BLACK);
  Sensor.Init(); // PB18 = ADC1 channel 5, slidepot
  Sound_Init();  // initialize sound
  TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
    // initialize interrupts on TimerG12 at 30 Hz
  
  // initialize all data structures
  __enable_irq();

  while(1){
    // wait for semaphore
       // clear semaphore
       // update ST7735R
    // check for end game or level switch
  }
}
