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

Player::Player() {

}

// Cursor ====================================================

Cursor::Cursor() {

}

// Ship ====================================================

Ship::Ship(Sprite sprite, uint8_t ship_size) {

}

// Board ====================================================

Board::Board() {

}