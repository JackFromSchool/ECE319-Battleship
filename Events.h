#ifndef EVENTS_H
#define EVENTS_H

/*
    Defines High-Level Event Abstractions
    No Exported Globals
    Associated Events.cpp
*/

/*
    Defines all possible input events.
*/
enum Event {
    /*
    * Buttons                            
    *                                    
    *   ┌──┐   ┌──┐                      
    *   │0 │   │1 │    Pressed Event on  
    *   │  │   │  │    rising edge.      
    *   └──┘   └──┘                      
    *                                    
    *     ┌──┐   ┌──┐                    
    *     │2 │   │3 │  Unpressed Event on
    *     │  │   │  │  falling edge.     
    *     └──┘   └──┘                    
    */
    BUTTON0_PRESS, BUTTON0_UNPRESS,
    BUTTON1_PRESS, BUTTON1_UNPRESS,
    BUTTON2_PRESS, BUTTON2_UNPRESS,
    BUTTON3_PRESS, BUTTON3_UNPRESS,
    STARTINGPRESS

    /*
    * Joystick                   
    *                            
    *                            
    *     UPLEFT   UP   UPRIGHT  
    *       │       │     │      
    *       └────┐  │ ┌───┘      
    *  LEFT──────RETURN─────RIGHT
    *       ┌────┘  │ └───┐      
    *       │       │     │      
    *   DOWNLEFT  DOWN  DOWNRIGHT
    */
    JOYSTICK_LEFT, JOYSTICK_RIGHT,
    JOYSTICK_UP, JOYSTICK_DOWN,
    JOYSTICK_UPLEFT, JOYSTICK_UPRIGHT,
    JOYSTICK_DOWNLEFT, JOYSTICK_DOWNRIGHT,
    JOYSTICK_RETURN,

    /*
    * SlidePot                                 
    *                                          
    *           0   1   2   3   4   5   6      
    *           │   │   │   │   │   │   │      
    *        ┌──┼───┼───┼───┼───┼───┼───┼──┐   
    *        │┌─▼─┬─▼─┬─▼─┬─▼─┬─▼─┬─▼─┬─▼─┐│   
    *  Bottom││   │   │ │ │   │   │   │   ││Top
    *        │└───┴───┴─┼─┴───┴───┴───┴───┘│   
    *        └──────────┼──────────────────┘   
    *                   │                      
    *                   │                      
    *             Slide Pot Lever              
    *             Would be SLIDEPOT2           
    */
    SLIDEPOT0,
    SLIDEPOT1,
    SLIDEPOT2,
    SLIDEPOT3,
    SLIDEPOT4,
    SLIDEPOT5,
    SLIDEPOT6,

    // Event to be sent if queue is polled and is empty
    NOEVENT
};

// Queue Max Size
#define QUEUE_SIZE 100

/* 
    Event Queue for processing events
*/
class EventQueue {
    private:
        enum Event Buf[QUEUE_SIZE];
        int GetI;
        int PutI;
        enum Event lastElement;
    public:
        EventQueue();
        bool put(enum Event event);
        bool get(enum Event * event);
        bool full();
        bool empty();
};

#endif