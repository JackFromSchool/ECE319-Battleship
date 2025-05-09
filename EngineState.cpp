#include "EngineState.h"
#include "Events.h"
#include "images/images.h"
#include "images/ImageTools.h"
#include "images/FontPrint.h"
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "Globals.h"
#include "sounds/sounds.h"
#include "Sound.h"

// Engine ====================================================

// Initialize Defaults
Engine::Engine() {
    this->audio = true;
    this->playmode = SINGLE_BOARD;
    this->language = ENGLISH;
    this->gamestate = MENU;
    this->eventQueue = EventQueue();
    this->player1 = Player();
    this->player2 = Player();
    this->isPlayer1Turn = true;
}

// Blocks execution until an event is in the queue
enum Event Engine::pollQueue() {
    enum Event current = NOEVENT;
    while (!this->eventQueue.get(&current)) {}
    return current;
}

void Engine::switchPlayer() {
    ST7735_FillScreen(MENU_TEXT);
    isPlayer1Turn = !isPlayer1Turn;
    if (engineState.language == ENGLISH) {
        if (isPlayer1Turn) {
            printText("PLAYER 1 TURN", 12, 12, MENU_BG, MENU_TEXT);
        } else {
            printText("PLAYER 2 TURN", 12, 12, MENU_BG, MENU_TEXT);
        }
    } else {
        if (isPlayer1Turn) {
            printText("TURNO DEL JUGADOR 1", 12, 12, MENU_BG, MENU_TEXT);
        } else {
            printText("TURNO DEL JUGADOR 2", 12, 12, MENU_BG, MENU_TEXT);
        }
    }
    Sound_Start(tick, TICK_LEN);
    printText("5", 64, 73, MENU_BG, MENU_TEXT);
    Clock_Delay1ms(1000);
    Sound_Start(tick, TICK_LEN);
    printText("4", 64, 73, MENU_BG, MENU_TEXT);
    Clock_Delay1ms(1000);
    Sound_Start(tick, TICK_LEN);
    printText("3", 64, 73, MENU_BG, MENU_TEXT);
    Clock_Delay1ms(1000);
    Sound_Start(tick, TICK_LEN);
    printText("2", 64, 73, MENU_BG, MENU_TEXT);
    Clock_Delay1ms(1000);
    Sound_Start(tick, TICK_LEN);
    printText("1", 64, 73, MENU_BG, MENU_TEXT);
    Clock_Delay1ms(1000);
    Sound_Start(select, SELECT_LEN);
}

// Player ====================================================

Player::Player() : two_ship0(Sprite(two_space_battleship1, BOARDSPACEX(5), BOARDSPACEY(5), 11, 22), 2),
    two_ship1(Sprite(two_space_battleship2, BOARDSPACEX(5), BOARDSPACEY(5), 11, 22), 2),
    three_ship(Sprite(three_space_battleship, BOARDSPACEX(5), BOARDSPACEY(5), 11, 33), 3),
    four_ship(Sprite(four_space_battleship, BOARDSPACEX(5), BOARDSPACEY(5), 11, 44), 4),
    five_ship(Sprite(five_space_battleship, BOARDSPACEX(5), BOARDSPACEY(5), 11, 55), 5) {
    
    this->numShipsPlaced = 0;
    this->alive_ships = 5;
    this->sunk_ships = 0;
    this->score = 100;
    this->enemy = Board();
    this->mine = Board();
    this->cursor = Cursor();
}

void Player::drawMyBoard() {
    // Redraw Background
    ST7735_DrawBitmap(0, 160, battleship_board, 128, 160);

    if (this->two_ship0.isVisible) {
        uint16_t temp[this->two_ship0.sprite.size()];
        this->two_ship0.sprite.fill_background(battleship_board, temp);
        DRAWSPRITE(this->two_ship0.sprite, temp);
    }

    if (this->two_ship1.isVisible) {
        uint16_t temp[this->two_ship1.sprite.size()];
        this->two_ship1.sprite.fill_background(battleship_board, temp);
        DRAWSPRITE(this->two_ship1.sprite, temp);
    }

    if (this->three_ship.isVisible) {
        uint16_t temp[this->three_ship.sprite.size()];
        this->three_ship.sprite.fill_background(battleship_board, temp);
        DRAWSPRITE(this->three_ship.sprite, temp);
    }

    if (this->four_ship.isVisible) {
        uint16_t temp[this->four_ship.sprite.size()];
        this->four_ship.sprite.fill_background(battleship_board, temp);
        DRAWSPRITE(this->four_ship.sprite, temp);
    }

    if (this->five_ship.isVisible) {
        uint16_t temp[this->five_ship.sprite.size()];
        this->five_ship.sprite.fill_background(battleship_board, temp);
        DRAWSPRITE(this->five_ship.sprite, temp);
    }
    
    for (uint32_t row = 0; row < 10; row++) {
        for (uint32_t column = 0; column < 10; column++) {
            switch (this->mine.board[row][column]) {
                case FIVE_SHIP_HIT: case FOUR_SHIP_HIT:
                case THREE_SHIP_HIT: case TWO_SHIP0_HIT:
                case TWO_SHIP1_HIT: case HIT:
                    {
                        Sprite sp = Sprite(hit_marker, BOARDSPACEX(column), BOARDSPACEY(row), 11, 11);
                        uint16_t temp[sp.size()];
                        sp.fill_background(battleship_board, temp);
                        DRAWSPRITE(sp, temp);
                    }
                    break;
                case MISS:
                    {
                        Sprite sp = Sprite(miss_marker, BOARDSPACEX(column), BOARDSPACEY(row), 11, 11);
                        uint16_t temp[sp.size()];
                        sp.fill_background(battleship_board, temp);
                        DRAWSPRITE(sp, temp);
                    }
                    break;
                default:
                    break;
            }
        }
    }

    if (engineState.language == ENGLISH) {
        printText("YOUR SHIPS", 65, 141, BOARD_BG, BOARD_TEXT);
        printText("SUNK SHIPS", 65, 152, BOARD_BG, BOARD_TEXT);

        printText("ABILITY", 8, 141, BOARD_BG, BOARD_TEXT);
    } else {
        printText("TUS BARCOS", 65, 141, BOARD_BG, BOARD_TEXT);
        printText("BARCOS HUNDIDOS", 40, 152, BOARD_BG, BOARD_TEXT);

        printText("CAPACIDAD", 5, 141, BOARD_BG, BOARD_TEXT);
    }

    char your_ships[2];
    your_ships[1] = '\0';
    your_ships[0] = this->alive_ships + '0';

    char sunk_ships[2];
    sunk_ships[1] = '\0';
    sunk_ships[0] = this->sunk_ships + '0';

    printText(your_ships, 115, 141, BOARD_BG, BOARD_TEXT);
    printText(sunk_ships, 115, 152, BOARD_BG, BOARD_TEXT);
}

void Player::drawEnemyBoard(bool cursor) {
        ST7735_DrawBitmap(0, 160, battleship_board, 128, 160);

    for (uint32_t row = 0; row < 10; row++) {
        for (uint32_t column = 0; column < 10; column++) {
            switch (this->enemy.board[row][column]) {
                case FIVE_SHIP_HIT: case FOUR_SHIP_HIT:
                case THREE_SHIP_HIT: case TWO_SHIP0_HIT:
                case TWO_SHIP1_HIT: case HIT:
                    {
                        Sprite sp = Sprite(hit_marker, BOARDSPACEX(column), BOARDSPACEY(row), 11, 11);
                        uint16_t temp[sp.size()];
                        sp.fill_background(battleship_board, temp);
                        DRAWSPRITE(sp, temp);
                    }
                    break;
                case MISS:
                    {
                        Sprite sp = Sprite(miss_marker, BOARDSPACEX(column), BOARDSPACEY(row), 11, 11);
                        uint16_t temp[sp.size()];
                        sp.fill_background(battleship_board, temp);
                        DRAWSPRITE(sp, temp);
                    }
                    break;
                default:
                    break;
            }
        }

        if (cursor) {
            Sprite sp = Sprite(cursor_marker, BOARDSPACEX(this->cursor.x_pos), BOARDSPACEY(this->cursor.y_pos), 11, 11);
            uint16_t temp[sp.size()];
            sp.fill_background(battleship_board, temp);
            DRAWSPRITE(sp, temp);
        }


    }

    if (engineState.language == ENGLISH) {
        printText("YOUR SHIPS", 65, 141, BOARD_BG, BOARD_TEXT);
        printText("SUNK SHIPS", 65, 152, BOARD_BG, BOARD_TEXT);

        printText("ABILITY", 8, 141, BOARD_BG, BOARD_TEXT);
    } else {
        printText("TUS BARCOS", 65, 141, BOARD_BG, BOARD_TEXT);
        printText("BARCOS HUNDIDOS", 40, 152, BOARD_BG, BOARD_TEXT);

        printText("CAPACIDAD", 5, 141, BOARD_BG, BOARD_TEXT);
    }

    char your_ships[2];
    your_ships[1] = '\0';
    your_ships[0] = this->alive_ships + '0';

    char sunk_ships[2];
    sunk_ships[1] = '\0';
    sunk_ships[0] = this->sunk_ships + '0';

    printText(your_ships, 115, 141, BOARD_BG, BOARD_TEXT);
    printText(sunk_ships, 115, 152, BOARD_BG, BOARD_TEXT);
}

bool Player::hasLost() {
    return this->two_ship0.sunk &&
        this->two_ship1.sunk &&
        this->three_ship.sunk &&
        this->four_ship.sunk &&
        this->five_ship.sunk;
}

// Cursor ====================================================

Cursor::Cursor() {
    this->x_pos = 0;
    this->y_pos = 0;
}

// Ship ====================================================

Ship::Ship(Sprite sprite, uint8_t ship_size) : sprite(sprite) {
    this->ship_size = ship_size;
    this->board_pos_x = 5;
    this->board_pos_y = 5;
    this->num_hits = 0;
    this->rotated = false;
    this->sunk = false;
    this->isVisible = false;
}

void Ship::set_x(uint8_t new_x) {
    this->board_pos_x = new_x;
    this->sprite.set_x(BOARDSPACEX(new_x));
}

void Ship::set_y(uint8_t new_y) {
    this->board_pos_y = new_y;
    this->sprite.set_y(BOARDSPACEY(new_y));
}

bool Ship::hit() {
    this->num_hits++;
    if (this->num_hits == this->ship_size) {
        this->sunk = true;
        return true;
    }
    return false;
}

// Board ====================================================

Board::Board() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            this->board[i][j] = WATER;
        }
    }
}