#ifndef ENGINESTATE_H
#define ENGINESTATE_H

#include "Events.h"
#include "images/ImageTools.h"
#include "images/images.h"

/*
    General configuration state required for the Engine
*/

enum GameState {
    MENU,
    CHARACTER_SELECT,
    BOARD_PLACEMENT,
    ACTIVE_GAME,
    END_SCREEN,
    REPLAY
};

enum PlayMode {
    SINGLE_BOARD,
    DUAL_BOARD
};

enum Language {
    ENGLISH,
    SPANISH
};

/*
    Game State Stuff
*/

enum BoardSpace {
    WATER = 0,
    MISS,
    HIT,
    TWO_SHIP0, TWO_SHIP0_HIT,
    TWO_SHIP1, TWO_SHIP1_HIT,
    THREE_SHIP, THREE_SHIP_HIT,
    FOUR_SHIP, FOUR_SHIP_HIT,
    FIVE_SHIP, FIVE_SHIP_HIT,
};

class Board {
    public:
        enum BoardSpace board[10][10];
        Board();
        void drawHitMiss();

};

class Ship {
    public:
        Sprite sprite;
        uint8_t board_pos_x;
        uint8_t board_pos_y;
        bool rotated;
        uint8_t ship_size;
        uint8_t num_hits;
        bool sunk;
        bool isPlaced;
        Ship(Sprite sprite, uint8_t ship_size);
        void set_x(uint8_t new_x);
        void set_y(uint8_t new_y);
};

class Cursor {
    public:
        uint8_t x_pos;
        uint8_t y_pos;
        Cursor();
};

class Player {
    public:
        Board enemy;
        Board mine;
        uint8_t numShipsPlaced;
        Cursor cursor;
        Ship two_ship0;
        Ship two_ship1;
        Ship three_ship;
        Ship four_ship;
        Ship five_ship;
        Player();
        void drawMyBoard();
        void drawEnemyBoard();
};

/*
    Class to Store Engine State
*/

class Engine {
    private:
        
    public:
        EventQueue eventQueue;
        enum GameState gamestate;
        enum PlayMode playmode;
        enum Language language;
        bool audio;

        Player player1;
        Player player2;
        bool isPlayer1Turn;

        Engine();

        enum Event pollQueue();

};



#endif