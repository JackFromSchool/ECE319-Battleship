#include "EngineState.h"
#include "Events.h"

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