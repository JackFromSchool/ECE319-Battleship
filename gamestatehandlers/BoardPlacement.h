#ifndef BOARDPLACEMENT_H
#define BOARDPLACEMENT_H
#include "EngineState.h"
#include "Events.h"

void initBoardPlacement();
enum GameState handleBoardPlacement(enum Event event);

#endif