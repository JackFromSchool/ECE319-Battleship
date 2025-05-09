#include "Menu.h"
#include "EngineState.h"
#include "Events.h"
#include "Globals.h"
#include "Sound.h"
#include "images/images.h"
#include "images/ImageTools.h"
#include "images/FontPrint.h"
#include "../inc/ST7735.h"
#include "sounds/sounds.h"
#include "Sound.h"

enum Screen {
    MAIN_MENU,
    OPTIONS_MENU,
};

static enum Screen current_screen;

void printMain() {
    ST7735_FillScreen(MENU_TEXT);
    ST7735_DrawBitmap(12, 51, battleship_logo, 107, 17);

    if (engineState.language == ENGLISH) {
        printText("BY  JACK AND SHREYAS", 12, 62, MENU_BG, MENU_TEXT);
        printText("PRESS SW1 TO", 12, 110, MENU_BG, MENU_TEXT);
        printText("SWITCH LANGUAGE", 12, 118, MENU_BG, MENU_TEXT);
        printText("PRESS SW4 TO CONTINUE", 12, 135, MENU_BG, MENU_TEXT);
    } else {
        printText("BATALLA NAVAL", 12, 62, MENU_BG, MENU_TEXT);
        printText("POR  JACK Y SHREYAS", 12, 70, MENU_BG, MENU_TEXT);
        printText("PRESIONE SW1 PARA", 12, 110, MENU_BG, MENU_TEXT);
        printText("CAMBIAR DE IDIOMA", 12, 118, MENU_BG, MENU_TEXT);
        printText("PRESIONE SW4 PARA", 12, 135, MENU_BG, MENU_TEXT);
        printText("CONTINUAR", 12, 143, MENU_BG, MENU_TEXT);
    }
    
}

void printOptions() {
    ST7735_FillScreen(MENU_TEXT);

    if (engineState.language == ENGLISH) {
        printText("SW1", 12, 12, MENU_BG, MENU_TEXT);
        if (engineState.audio) {
            printText("AUDIO ON", 12, 20, MENU_BG, MENU_TEXT);
        } else {
            printText("AUDIO OFF", 12, 20, MENU_BG, MENU_TEXT);
        }
        
        printText("SW2", 12, 30, MENU_BG, MENU_TEXT);
        if (engineState.playmode == SINGLE_BOARD) {
            printText("SINGLE BOARD", 12, 38, MENU_BG, MENU_TEXT);
        } else {
            printText("DUAL BOARD", 12, 38, MENU_BG, MENU_TEXT);
        }

        printText("PRESS SW4 TO START", 12, 135, MENU_BG, MENU_TEXT);
    } else {
        printText("SW1", 12, 12, MENU_BG, MENU_TEXT);
        if (engineState.audio) {
            printText("AUDIO ENCENDIDO", 12, 20, MENU_BG, MENU_TEXT);
        } else {
            printText("AUDIO APAGADO", 12, 20, MENU_BG, MENU_TEXT);
        }
        
        printText("SW2", 12, 30, MENU_BG, MENU_TEXT);
        if (engineState.playmode == SINGLE_BOARD) {
            printText("JUNTA UNICA", 12, 38, MENU_BG, MENU_TEXT);
        } else {
            printText("TARJETA DOBLE", 12, 38, MENU_BG, MENU_TEXT);
        }

        printText("PRESIONE SW4 PARA", 12, 135, MENU_BG, MENU_TEXT);
        printText("COMENZAR", 12, 143, MENU_BG, MENU_TEXT);
    }
}

void initMenu() {
    current_screen = MAIN_MENU;
    engineState.audio = true;
    engineState.language = ENGLISH;
    engineState.player1 = Player();
    engineState.player2 = Player();
    engineState.playmode = SINGLE_BOARD;
    printMain();
}

enum GameState handleMenu(enum Event event) {
    if (current_screen == MAIN_MENU) {
        switch (event) {
            case BUTTON0_PRESS:
                if (engineState.language == ENGLISH) {
                    engineState.language = SPANISH;
                } else {
                    engineState.language = ENGLISH;
                }
                printMain();
                Sound_Start(tick, TICK_LEN);
                break;
            
            case BUTTON3_PRESS:
                current_screen = OPTIONS_MENU;
                Sound_Start(select, SELECT_LEN);
                printOptions();

            default: break;
        }
    } else {
        switch (event) {
            case BUTTON0_PRESS:
                engineState.audio = !engineState.audio;
                printOptions();
                Sound_Start(tick, TICK_LEN);
                break;
            
            case BUTTON2_PRESS:
                if (engineState.playmode == SINGLE_BOARD) {
                    engineState.playmode = DUAL_BOARD;
                } else {
                    engineState.playmode = SINGLE_BOARD;
                }
                printOptions();
                Sound_Start(tick, TICK_LEN);
                break;
            
            case BUTTON3_PRESS:
                engineState.isPlayer1Turn = false;
                engineState.switchPlayer();
                Sound_Start(select, SELECT_LEN);
                return BOARD_PLACEMENT;
                break;
            
            defualt: break;
        }
    }
    return MENU;
}
