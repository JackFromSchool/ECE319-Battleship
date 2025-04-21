#ifndef ACTIVEGAME_H
#define ACTIVEGAME_H
#include "EngineState.h"
#include "Events.h"

void initActiveGame();
enum GameState handleActiveGame(enum Event event);

#endif