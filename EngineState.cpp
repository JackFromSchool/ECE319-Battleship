#include "EngineState.h"
#include "Events.h"


// Engine ====================================================

// Initialize Defaults
Engine::Engine() {
    this->audio = true;
    this->playmode = SINGLE_BOARD;
    this->language = ENGLISH;
    this->eventQueue = EventQueue();
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

    this->enemy = Board();
    this->mine = Board();
    this->cursor = Cursor();
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
}

// Board ====================================================

Board::Board() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            this->board[i][j] = WATER;
        }
    }
}