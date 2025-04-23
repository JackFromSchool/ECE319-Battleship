#include "ActiveGame.h"
#include "EngineState.h"
#include "Events.h"
#include "Globals.h"
#include "../inc/Clock.h"
#include "../inc/ST7735.h"
#include "images/ImageTools.h"
#include "sounds/sounds.h"
#include "Sound.h"

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

    Sound_Start(tick, TICK_LEN);
    if (engineState.isPlayer1Turn) {
        engineState.player1.drawEnemyBoard(true);
    } else {
        engineState.player2.drawEnemyBoard(true);
    }
}

static bool isValidMove() {
    Player *current_player;
    if (engineState.isPlayer1Turn) {
        current_player = &engineState.player1;
    } else {
        current_player = &engineState.player2;
    }

    return current_player->enemy.board[current_player->cursor.y_pos][current_player->cursor.x_pos] == WATER;
}

bool registerHit() {
    Player *current_player;
    Player *enemy;
    if (engineState.isPlayer1Turn) {
        current_player = &engineState.player1;
        enemy = &engineState.player2;
    } else {
        current_player = &engineState.player2;
        enemy = &engineState.player1;
    }

    bool hit = true;
    bool sunk = false;
    enum BoardSpace *enemy_space = &enemy->mine.board[current_player->cursor.y_pos][current_player->cursor.x_pos];
    enum BoardSpace *my_space = &current_player->enemy.board[current_player->cursor.y_pos][current_player->cursor.x_pos];
    switch (*enemy_space) {
        case TWO_SHIP0:
            *enemy_space = TWO_SHIP0_HIT;
            *my_space = HIT;
            sunk = enemy->two_ship0.hit();
            break;
        case TWO_SHIP1:
            *enemy_space = TWO_SHIP1_HIT;
            *my_space = HIT;
            sunk = enemy->two_ship1.hit();
            break;
        case THREE_SHIP:
            *enemy_space = THREE_SHIP_HIT;
            *my_space = HIT;
            sunk = enemy->three_ship.hit();
            break;
        case FOUR_SHIP:
            *enemy_space = FOUR_SHIP_HIT;
            *my_space = HIT;
            sunk = enemy->four_ship.hit();
            break;
        case FIVE_SHIP:
            *enemy_space = FIVE_SHIP_HIT;
            *my_space = HIT;
            sunk = enemy->five_ship.hit();
            break;
        case WATER:
            *enemy_space = MISS;
            *my_space = MISS;
            hit = false;
            current_player->score--;
            break;
        default:
            break;
    }

    if (sunk) {
        enemy->alive_ships--;
        current_player->sunk_ships++;   
    }

    if (engineState.isPlayer1Turn) {
        engineState.player1.drawEnemyBoard(false);
    } else {
        engineState.player2.drawEnemyBoard(false);
    }

    if (hit) {
        Sound_Start(kaboom, KABOOM_LEN);
        Clock_Delay1ms(250);
        {   
            Sprite sp = Sprite(explosion1, BOARDSPACEX(current_player->cursor.x_pos), BOARDSPACEY(current_player->cursor.y_pos), 11, 11);
            uint16_t temp[sp.size()];
            sp.fill_background(battleship_board, temp);
            DRAWSPRITE(sp, temp);
        }
        Clock_Delay1ms(250);
        {   
            Sprite sp = Sprite(explosion2, BOARDSPACEX(current_player->cursor.x_pos), BOARDSPACEY(current_player->cursor.y_pos), 11, 11);
            uint16_t temp[sp.size()];
            sp.fill_background(battleship_board, temp);
            DRAWSPRITE(sp, temp);
        }
        Clock_Delay1ms(250);
        {   
            Sprite sp = Sprite(explosion3, BOARDSPACEX(current_player->cursor.x_pos), BOARDSPACEY(current_player->cursor.y_pos), 11, 11);
            uint16_t temp[sp.size()];
            sp.fill_background(battleship_board, temp);
            DRAWSPRITE(sp, temp);
        }
        Clock_Delay1ms(250);
        {   
            Sprite sp = Sprite(explosion1, BOARDSPACEX(current_player->cursor.x_pos), BOARDSPACEY(current_player->cursor.y_pos), 11, 11);
            uint16_t temp[sp.size()];
            sp.fill_background(battleship_board, temp);
            DRAWSPRITE(sp, temp);
        }
        Clock_Delay1ms(250);
        {   
            Sprite sp = Sprite(explosion2, BOARDSPACEX(current_player->cursor.x_pos), BOARDSPACEY(current_player->cursor.y_pos), 11, 11);
            uint16_t temp[sp.size()];
            sp.fill_background(battleship_board, temp);
            DRAWSPRITE(sp, temp);
        }
        Clock_Delay1ms(250);
        {   
            Sprite sp = Sprite(explosion3, BOARDSPACEX(current_player->cursor.x_pos), BOARDSPACEY(current_player->cursor.y_pos), 11, 11);
            uint16_t temp[sp.size()];
            sp.fill_background(battleship_board, temp);
            DRAWSPRITE(sp, temp);
        }
        Clock_Delay1ms(250);
        {   
            Sprite sp = Sprite(explosion3, BOARDSPACEX(current_player->cursor.x_pos), BOARDSPACEY(current_player->cursor.y_pos), 11, 11);
            uint16_t temp[sp.size()];
            sp.fill_background(battleship_board, temp);
            DRAWSPRITE(sp, temp);
        }
        Clock_Delay1ms(250);
    } else {
        Sound_Start(kersplash, KERSPLASH_LEN);
        Clock_Delay1ms(2000);
    }

    return enemy->hasLost();
}

void initActiveGame() {
    engineState.isPlayer1Turn = true;
    engineState.player1.drawEnemyBoard(true);
    isMyBoard = false;
}

enum GameState handleActiveGame(enum Event event) {
    Player *current_player;
    if (engineState.isPlayer1Turn) {
        current_player = &engineState.player1;
    } else {
        current_player = &engineState.player2;
    }

    switch (event) {
        case JOYSTICK_UP: case JOYSTICK_DOWN:
        case JOYSTICK_UPLEFT: case JOYSTICK_UPRIGHT:
        case JOYSTICK_DOWNLEFT: case JOYSTICK_DOWNRIGHT:
        case JOYSTICK_LEFT: case JOYSTICK_RIGHT:
            tryMoveCursor(event);
            return ACTIVE_GAME;

        case BUTTON1_PRESS:
            Sound_Start(select, SELECT_LEN);
            isMyBoard = !isMyBoard;
            if (isMyBoard) {
                current_player->drawMyBoard();
            } else {
                current_player->drawEnemyBoard(true);
            }
            return ACTIVE_GAME;
        
        case BUTTON0_PRESS:
            if (isMyBoard) return ACTIVE_GAME;
            if (!isValidMove()) return ACTIVE_GAME;
            if (registerHit()) {
                return END_SCREEN;
            }
            engineState.switchPlayer();
            
            if (engineState.isPlayer1Turn) {
                current_player = &engineState.player1;
            } else {
                current_player = &engineState.player2;
            }
            current_player->drawEnemyBoard(true);
            return ACTIVE_GAME;
    
        default:
            return ACTIVE_GAME;
    }
}
