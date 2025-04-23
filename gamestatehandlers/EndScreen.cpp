#include "EndScreen.h"
#include "EngineState.h"
#include "Events.h"
#include "Globals.h"
#include "images/images.h"
#include "images/ImageTools.h"
#include "images/FontPrint.h"
#include "../inc/ST7735.h"

void printEnd() {
    ST7735_FillScreen(MENU_TEXT);
    if (engineState.language == ENGLISH) {
        if (engineState.player1.hasLost()) {
            printText("PLAYER 2 WINS", 12, 12, MENU_BG, MENU_TEXT);
            printText("FINAL SCORE", 12, 20, MENU_BG, MENU_TEXT);
            char temp[4];
            temp[3] = '\0';
            temp[0] = engineState.player2.score / 100 - '0';
            temp[1] = (engineState.player2.score / 10) % 10  - '0';
            temp[2] = engineState.player2.score % 10 - '0';
            printText(temp, 12, 28, MENU_BG, MENU_TEXT);
        } else {
            printText("PLAYER 1 WINS", 12, 12, MENU_BG, MENU_TEXT);
            printText("FINAL SCORE", 12, 20, MENU_BG, MENU_TEXT);
            char temp[4];
            temp[3] = '\0';
            temp[0] = engineState.player1.score / 100 - '0';
            temp[1] = (engineState.player1.score / 10) % 10  - '0';
            temp[2] = engineState.player1.score % 10 - '0';
            printText(temp, 12, 28, MENU_BG, MENU_TEXT);
        }

        printText("PRESS SW4 TO CONTINUE", 12, 135, MENU_BG, MENU_TEXT);
    } else {
        if (engineState.player1.hasLost()) {
            printText("EL JUGADOR 2 GANA", 12, 12, MENU_BG, MENU_TEXT);
            printText("PUNTUACION FINAL", 12, 20, MENU_BG, MENU_TEXT);
            char temp[4];
            temp[3] = '\0';
            temp[0] = engineState.player2.score / 100 - '0';
            temp[1] = (engineState.player2.score / 10) % 10  - '0';
            temp[2] = engineState.player2.score % 10 - '0';
            printText(temp, 12, 28, MENU_BG, MENU_TEXT);
        } else {
            printText("EL JUGADOR 1 GANA", 12, 12, MENU_BG, MENU_TEXT);
            printText("PUNTUACION FINAL", 12, 20, MENU_BG, MENU_TEXT);
            char temp[4];
            temp[3] = '\0';
            temp[0] = engineState.player1.score / 100 - '0';
            temp[1] = (engineState.player1.score / 10) % 10  - '0';
            temp[2] = engineState.player1.score % 10 - '0';
            printText(temp, 12, 28, MENU_BG, MENU_TEXT);
        }

        printText("PRESIONE SW4 PARA", 12, 135, MENU_BG, MENU_TEXT);
        printText("CONTINUAR", 12, 143, MENU_BG, MENU_TEXT);
    }
}

void initEndScreen() {
    printEnd();
}

enum GameState handleEndScreen(enum Event event) {
    switch (event) {
        case BUTTON3_PRESS:
            return MENU;
        default:
            break;
    }
    return END_SCREEN;
}
