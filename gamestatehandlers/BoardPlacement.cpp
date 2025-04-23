#include "BoardPlacement.h"
#include "EngineState.h"
#include "Events.h"
#include "Globals.h"
#include <cstddef>

void initBoardPlacement() {
    engineState.isPlayer1Turn = true;
    engineState.player1.drawMyBoard();
}

enum GameState handleBoardPlacement(enum Event event) {
    if(event == BUTTON0_PRESS || event == BUTTON0_UNPRESS || event == BUTTON1_PRESS || event == BUTTON1_UNPRESS || event == BUTTON2_PRESS || event == BUTTON2_UNPRESS)
    {
        return BOARD_PLACEMENT;
    }
    if(engineState.player1.numShipsPlaced == 5)
    {
        return ACTIVE_GAME;
    }
    if(engineState.isPlayer1Turn)
    {
        switch(event)
        {
            case JOYSTICK_DOWN:
                //Get the object for Player 1, move the head of the ship in the specified direction
                switch(engineState.player1.numShipsPlaced);
                {
                    case 0:
                        engineState.player1.two_ship0.set_y(engineState.player1.two_ship0.board_pos_y - 1);
                        break;
                    case 1:
                        engineState.player1.two_ship1.set_y(engineState.player1.two_ship1.board_pos_y - 1);
                        break;
                    case 2:
                        engineState.player1.three_ship.set_y(engineState.player1.three_ship.board_pos_y - 1);
                        break;
                    case 3:
                        engineState.player1.four_ship.set_y(engineState.player1.four_ship.board_pos_y - 1);
                        break;
                    case 4:
                        engineState.player1.five_ship.set_y(engineState.player1.five_ship.board_pos_y - 1);
                        break;
                }
                break;
            case JOYSTICK_UP:
                //Get the object for Player 1, move the head of the ship in the specified direction
                switch(engineState.player1.numShipsPlaced)
                {
                    case 0:
                        engineState.player1.two_ship0.set_y(engineState.player1.two_ship0.board_pos_y + 1);
                        break;
                    case 1:
                        engineState.player1.two_ship1.set_y(engineState.player1.two_ship1.board_pos_y + 1);
                        break;
                    case 2:
                        engineState.player1.three_ship.set_y(engineState.player1.three_ship.board_pos_y + 1);
                        break;
                    case 3:
                        engineState.player1.four_ship.set_y(engineState.player1.four_ship.board_pos_y + 1);
                        break;
                    case 4:
                        engineState.player1.five_ship.set_y(engineState.player1.five_ship.board_pos_y + 1);
                        break;
                }
                break;
            case JOYSTICK_LEFT:
                //Get the object for Player 1, move the head of the ship in the specified direction
                switch(engineState.player1.numShipsPlaced)
                {
                    case 0:
                        engineState.player1.two_ship0.set_x(engineState.player1.two_ship0.board_pos_x - 1);
                        break;
                    case 1:
                        engineState.player1.two_ship1.set_x(engineState.player1.two_ship1.board_pos_x - 1);
                        break;
                    case 2:
                        engineState.player1.three_ship.set_x(engineState.player1.three_ship.board_pos_x - 1);
                        break;
                    case 3:
                        engineState.player1.four_ship.set_x(engineState.player1.four_ship.board_pos_x - 1);
                        break;
                    case 4:
                        engineState.player1.five_ship.set_x(engineState.player1.five_ship.board_pos_x - 1);
                        break;
                }
                break;
            case JOYSTICK_RIGHT:
                //Get the object for Player 1, move the head of the ship in the specified direction
                switch(engineState.player1.numShipsPlaced)
                {
                    case 0:
                        engineState.player1.two_ship0.set_x(engineState.player1.two_ship0.board_pos_x + 1);
                        break;
                    case 1:
                        engineState.player1.two_ship1.set_x(engineState.player1.two_ship1.board_pos_x + 1);
                        break;
                    case 2:
                        engineState.player1.three_ship.set_x(engineState.player1.three_ship.board_pos_x + 1);
                        break;
                    case 3:
                        engineState.player1.four_ship.set_x(engineState.player1.four_ship.board_pos_x + 1);
                        break;
                    case 4:
                        engineState.player1.five_ship.set_x(engineState.player1.five_ship.board_pos_x + 1);
                        break;
                }
                break;
            case BUTTON3_PRESS:
            {
                switch(engineState.player1.numShipsPlaced)
                {
                    case 0:
                        engineState.player1.two_ship0.isPlaced = true;
                        break;
                    case 1:
                        engineState.player1.two_ship1.isPlaced = true;
                        break;
                    case 2:
                        engineState.player1.three_ship.isPlaced = true;
                        break;
                    case 3:
                        engineState.player1.four_ship.isPlaced = true;
                        break;
                    case 4:
                        engineState.player1.five_ship.isPlaced = true;
                        break;
                }
                engineState.player1.numShipsPlaced++;
                break;
            }
        }
        engineState.player1.drawMyBoard();
    }
    else 
    {
        switch(event)
        {
            case JOYSTICK_DOWN:
                //Get the object for Player 1, move the head of the ship in the specified direction
                switch(engineState.player2.numShipsPlaced);
                {
                    case 0:
                        engineState.player2.two_ship0.set_y(engineState.player2.two_ship0.board_pos_y - 1);
                        break;
                    case 1:
                        engineState.player2.two_ship1.set_y(engineState.player2.two_ship1.board_pos_y - 1);
                        break;
                    case 2:
                        engineState.player2.three_ship.set_y(engineState.player2.three_ship.board_pos_y - 1);
                        break;
                    case 3:
                        engineState.player2.four_ship.set_y(engineState.player2.four_ship.board_pos_y - 1);
                        break;
                    case 4:
                        engineState.player2.five_ship.set_y(engineState.player2.five_ship.board_pos_y - 1);
                        break;
                }
                break;
            case JOYSTICK_UP:
                //Get the object for Player 1, move the head of the ship in the specified direction
                switch(engineState.player2.numShipsPlaced)
                {
                    case 0:
                        engineState.player2.two_ship0.set_y(engineState.player2.two_ship0.board_pos_y + 1);
                        break;
                    case 1:
                        engineState.player2.two_ship1.set_y(engineState.player2.two_ship1.board_pos_y + 1);
                        break;
                    case 2:
                        engineState.player2.three_ship.set_y(engineState.player2.three_ship.board_pos_y + 1);
                        break;
                    case 3:
                        engineState.player2.four_ship.set_y(engineState.player2.four_ship.board_pos_y + 1);
                        break;
                    case 4:
                        engineState.player2.five_ship.set_y(engineState.player2.five_ship.board_pos_y + 1);
                        break;
                }
                break;
            case JOYSTICK_LEFT:
                //Get the object for Player 1, move the head of the ship in the specified direction
                switch(engineState.player2.numShipsPlaced)
                {
                    case 0:
                        engineState.player2.two_ship0.set_x(engineState.player2.two_ship0.board_pos_x - 1);
                        break;
                    case 1:
                        engineState.player2.two_ship1.set_x(engineState.player2.two_ship1.board_pos_x - 1);
                        break;
                    case 2:
                        engineState.player2.three_ship.set_x(engineState.player2.three_ship.board_pos_x - 1);
                        break;
                    case 3:
                        engineState.player2.four_ship.set_x(engineState.player2.four_ship.board_pos_x - 1);
                        break;
                    case 4:
                        engineState.player2.five_ship.set_x(engineState.player2.five_ship.board_pos_x - 1);
                        break;
                }
                break;
            case JOYSTICK_RIGHT:
                //Get the object for Player 1, move the head of the ship in the specified direction
                switch(engineState.player2.numShipsPlaced)
                {
                    case 0:
                        engineState.player2.two_ship0.set_x(engineState.player2.two_ship0.board_pos_x + 1);
                        break;
                    case 1:
                        engineState.player2.two_ship1.set_x(engineState.player2.two_ship1.board_pos_x + 1);
                        break;
                    case 2:
                        engineState.player2.three_ship.set_x(engineState.player2.three_ship.board_pos_x + 1);
                        break;
                    case 3:
                        engineState.player2.four_ship.set_x(engineState.player2.four_ship.board_pos_x + 1);
                        break;
                    case 4:
                        engineState.player2.five_ship.set_x(engineState.player2.five_ship.board_pos_x + 1);
                        break;
                }
                break;
            case BUTTON3_PRESS:
            {
                switch(engineState.player2.numShipsPlaced)
                {
                    case 0:
                        engineState.player2.two_ship0.isPlaced = true;
                        break;
                    case 1:
                        engineState.player2.two_ship1.isPlaced = true;
                        break;
                    case 2:
                        engineState.player2.three_ship.isPlaced = true;
                        break;
                    case 3:
                        engineState.player2.four_ship.isPlaced = true;
                        break;
                    case 4:
                        engineState.player2.five_ship.isPlaced = true;
                        break;
                }
                engineState.player2.numShipsPlaced++;
                break;
            }
        }
        engineState.player2.drawMyBoard();
    }
    return BOARD_PLACEMENT;
}

//update the board's placement and continuously refresh the board