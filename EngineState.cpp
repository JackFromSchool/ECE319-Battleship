#include "EngineState.h"
#include "Events.h"
#include "images/images.h"
#include "images/ImageTools.h"
#include "../inc/ST7735.h"

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

// Player ====================================================

Player::Player() : two_ship0(Sprite(two_space_battleship1, BOARDSPACEX(5), BOARDSPACEY(5), 11, 22), 2),
    two_ship1(Sprite(two_space_battleship2, BOARDSPACEX(5), BOARDSPACEY(5), 11, 22), 2),
    three_ship(Sprite(three_space_battleship, BOARDSPACEX(5), BOARDSPACEY(5), 11, 33), 3),
    four_ship(Sprite(four_space_battleship, BOARDSPACEX(5), BOARDSPACEY(5), 11, 44), 4),
    five_ship(Sprite(five_space_battleship, BOARDSPACEX(5), BOARDSPACEY(5), 11, 55), 5) {
    
    this->numShipsPlaced = 0;
    this->enemy = Board();
    this->mine = Board();
    this->cursor = Cursor();
}

void Player::drawMyBoard() {
    // Redraw Background
    ST7735_DrawBitmap(0, 160, battleship_board, 128, 160);

    if (this->two_ship0.isPlaced) {
        uint16_t temp[this->two_ship0.sprite.size()];
        this->two_ship0.sprite.fill_background(battleship_board, temp);
        DRAWSPRITE(this->two_ship0.sprite, temp);
    }

    if (this->two_ship1.isPlaced) {
        uint16_t temp[this->two_ship1.sprite.size()];
        this->two_ship1.sprite.fill_background(battleship_board, temp);
        DRAWSPRITE(this->two_ship1.sprite, temp);
    }

    if (this->three_ship.isPlaced) {
        uint16_t temp[this->three_ship.sprite.size()];
        this->three_ship.sprite.fill_background(battleship_board, temp);
        DRAWSPRITE(this->three_ship.sprite, temp);
    }

    if (this->four_ship.isPlaced) {
        uint16_t temp[this->four_ship.sprite.size()];
        this->four_ship.sprite.fill_background(battleship_board, temp);
        DRAWSPRITE(this->four_ship.sprite, temp);
    }

    if (this->five_ship.isPlaced) {
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

}

void Player::drawEnemyBoard() {
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

        {
            Sprite sp = Sprite(cursor_marker, BOARDSPACEX(this->cursor.x_pos), BOARDSPACEY(this->cursor.y_pos), 11, 11);
            uint16_t temp[sp.size()];
            sp.fill_background(battleship_board, temp);
            DRAWSPRITE(sp, temp);
        }
    }
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
    this->isPlaced = false;
}

void Ship::set_x(uint8_t new_x) {
    this->board_pos_x = new_x;
    this->sprite.set_x(new_x);
}

void Ship::set_y(uint8_t new_y) {
    this->board_pos_y = new_y;
    this->sprite.set_y(new_y);
}

// Board ====================================================

Board::Board() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            this->board[i][j] = WATER;
        }
    }
}