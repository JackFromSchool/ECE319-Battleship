#include "ActiveGame.h"
#include "Events.h"
#include "Globals.h"

static bool isMyBoard;

static void tryMoveCursor(enum Event event) {
    if (isMyBoard) {
        return;
    }

    Cursor *c;
    if (engineState.isPlayer1Turn) {
        c = &engineState.player1.cursor;
    } else {
        c = &engineState.player2.cursor;
    }

    Cursor newCursor = Cursor();
    newCursor.x_pos = c->x_pos;
    newCursor.y_pos = c->y_pos;
    switch (event) {
        case JOYSTICK_UP:
            newCursor.y_pos--;
            break;
        case JOYSTICK_DOWN:
            newCursor.y_pos++;
            break;
        case JOYSTICK_UPLEFT:
            newCursor.y_pos--;
            newCursor.x_pos--;
            break;
        case JOYSTICK_UPRIGHT:
            newCursor.y_pos--;
            newCursor.x_pos++;
            break;
        case JOYSTICK_DOWNLEFT:
            newCursor.y_pos++;
            newCursor.x_pos--;
            break;
        case JOYSTICK_DOWNRIGHT:
            newCursor.y_pos++;
            newCursor.x_pos++;
            break;
        case JOYSTICK_LEFT:
            newCursor.x_pos--;
            break;
        case JOYSTICK_RIGHT:
            newCursor.x_pos++;
            break;
        default:
            break;
    }

    if (newCursor.x_pos >= 10 || newCursor.y_pos >= 10) {
        return;
    }
    c->x_pos = newCursor.x_pos;
    c->y_pos = newCursor.y_pos;
    
    if (engineState.isPlayer1Turn) {
        engineState.player1.drawEnemyBoard();
    } else {
        engineState.player2.drawEnemyBoard();
    }
}

static bool isValidMove() {
    // TODO
}

void initActiveGame() {
    engineState.isPlayer1Turn = true;
    engineState.player1.drawEnemyBoard();
    isMyBoard = false;
}

enum GameState handleActiveGame(enum Event event) {
    switch (event) {
        case JOYSTICK_UP: case JOYSTICK_DOWN:
        case JOYSTICK_UPLEFT: case JOYSTICK_UPRIGHT:
        case JOYSTICK_DOWNLEFT: case JOYSTICK_DOWNRIGHT:
        case JOYSTICK_LEFT: case JOYSTICK_RIGHT:
            tryMoveCursor(event);
            return ACTIVE_GAME;
            break;

        case BUTTON1_PRESS:
            isMyBoard = !isMyBoard;
            break;
        
        case BUTTON0_PRESS:
            if (!isMyBoard) return ACTIVE_GAME;

        default:
            return ACTIVE_GAME;
    }
}
