#ifndef ENGINESTATE_H
#define ENGINESTATE_H

#include "Events.h"

/*
    General configuration state required for the Engine
*/

enum GameState {
    MENU,
    CHARACTER_SELECT,
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

        Engine();

        enum Event pollQueue();

};

#endif