#include "ActiveGame.h"
#include "Events.h"
#include "Globals.h"

static bool isMyBoard;

static void tryMoveCursor(enum Event event) {
    if (!isMyBoard) {
        return;
    }

    Cursor &ptr;
    if (engineState.isPlayer1Turn) {
        
    } else {

    }
}

static bool isValidMove() {
    if (engineState.pl)
}

void initActiveGame() {
    engineState.isPlayer1Turn = true;
    engineState.player1.drawMyBoard();
    isMyBoard = true;
}

enum GameState handleActiveGame(enum Event event) {
    switch (event) {
        case JOYSTICK_UP: case JOYSTICK_DOWN:
        case JOYSTICK_UPLEFT: case JOYSTICK_UPRIGHT:
        case JOYSTICK_DOWNLEFT: case JOYSTICK_DOWNRIGHT:
        case JOYSTICK_LEFT: case JOYSTICK_RIGHT:

        case BUTTON1_PRESS:
            isMyBoard = !isMyBoard;
            break;
        
        case BUTTON0_PRESS:
            if (!isMyBoard) break;

    }
}
