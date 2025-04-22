#include "BoardPlacement.h"
#include "Events.h"

void initBoardPlacement() {
    engineState.isPlayer1Turn = true;
    engineState.player1.drawMyBoard();
}

enum GameState handleBoardPlacement(enum Event event) {
    if(event == BUTTON0_PRESS || event == BUTTON0_UNPRESS || event == BUTTON1_PRESS || event == BUTTON1_UNPRESS || event == BUTTON2_PRESS || event == BUTTON2_UNPRESS)
    {
        return;
    }
    if(engineState.isPlayer1Turn)
    {
        switch(event)
        {
            case(JOYSTICK_DOWN)
                //Get the object for Player 1, move the head of the ship in the specified direction
                switch(engineState.player1.numShipsPlaced);
                {
                    case 0:
                        engineState.player1.two_ship0.board_pos_y--;
                        break;
                    case 1:
                        engineState.player1.two_ship1.board_pos_y--;
                        break;
                    case 2:
                        engineState.player1.three_ship.board_pos_y--;
                        break;
                    case 3:
                        engineState.player1.four_ship.board_pos_y--;
                        break;
                    case 4:
                        engineState.player1.five_ship.board_pos_y--;
                        break;
                }
            case(JOYSTICK_UP)
                //Get the object for Player 1, move the head of the ship in the specified direction
                switch(engineState.player1.numShipsPlaced)
                {
                    case 0:
                        engineState.player1.two_ship0.board_pos_y++;
                        break;
                    case 1:
                        engineState.player1.two_ship1.board_pos_y++;
                        break;
                    case 2:
                        engineState.player1.three_ship.board_pos_y++;
                        break;
                    case 3:
                        engineState.player1.four_ship.board_pos_y++;
                        break;
                    case 4:
                        engineState.player1.five_ship.board_pos_y++;
                        break;
                }
            case(JOYSTICK_LEFT)
                //Get the object for Player 1, move the head of the ship in the specified direction
                switch(engineState.player1.numShipsPlaced)
                {
                    case 0:
                        engineState.player1.two_ship0.board_pos_x--;
                        break;
                    case 1:
                        engineState.player1.two_ship1.board_pos_x--;
                        break;
                    case 2:
                        engineState.player1.three_ship.board_pos_x--;
                        break;
                    case 3:
                        engineState.player1.four_ship.board_pos_x--;
                        break;
                    case 4:
                        engineState.player1.five_ship.board_pos_x--;
                        break;
                }
            case(JOYSTICK_RIGHT)
                //Get the object for Player 1, move the head of the ship in the specified direction
                switch(engineState.player1.numShipsPlaced)
                {
                    case 0:
                        engineState.player1.two_ship0.board_pos_x++;
                        break;
                    case 1:
                        engineState.player1.two_ship1.board_pos_x++;
                        break;
                    case 2:
                        engineState.player1.three_ship.board_pos_x++;
                        break;
                    case 3:
                        engineState.player1.four_ship.board_pos_x++;
                        break;
                    case 4:
                        engineState.player1.five_ship.board_pos_x++;
                        break;
                }
            case(BUTTON3_PRESS)
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
            }
        }
        engineState.player1.drawMyBoard();
    }
    else 
    {
        switch(event)
        {
            case(JOYSTICK_DOWN)
                //Get the object for Player 1, move the head of the ship in the specified direction
                switch(engineState.player2.numShipsPlaced)
                {
                    case 0:
                        engineState.player2.two_ship0.board_pos_y--;
                        break;
                    case 1:
                        engineState.player2.two_ship1.board_pos_y--;
                        break;
                    case 2:
                        engineState.player2.three_ship.board_pos_y--;
                        break;
                    case 3:
                        engineState.player2.four_ship.board_pos_y--;
                        break;
                    case 4:
                        engineState.player2.five_ship.board_pos_y--;
                        break;
                }
            case(JOYSTICK_UP)
                //Get the object for Player 1, move the head of the ship in the specified direction
                switch(engineState.player2.numShipsPlaced)
                {
                    case 0:
                        engineState.player2.two_ship0.board_pos_y++;
                        break;
                    case 1:
                        engineState.player2.two_ship1.board_pos_y++;
                        break;
                    case 2:
                        engineState.player2.three_ship.board_pos_y++;
                        break;
                    case 3:
                        engineState.player2.four_ship.board_pos_y++;
                        break;
                    case 4:
                        engineState.player2.five_ship.board_pos_y++;
                        break;
                }
            case(JOYSTICK_LEFT)
                //Get the object for Player 1, move the head of the ship in the specified direction
                switch(engineState.player2.numShipsPlaced)
                {
                    case 0:
                        engineState.player2.two_ship0.board_pos_x--;
                        break;
                    case 1:
                        engineState.player2.two_ship1.board_pos_x--;
                        break;
                    case 2:
                        engineState.player2.three_ship.board_pos_x--;
                        break;
                    case 3:
                        engineState.player2.four_ship.board_pos_x--;
                        break;
                    case 4:
                        engineState.player2.five_ship.board_pos_x--;
                        break;
                }
            case(JOYSTICK_RIGHT)
                //Get the object for Player 1, move the head of the ship in the specified direction
                switch(engineState.player2.numShipsPlaced)
                {
                    case 0:
                        engineState.player2.two_ship0.board_pos_x++;
                        break;
                    case 1:
                        engineState.player2.two_ship1.board_pos_x++;
                        break;
                    case 2:
                        engineState.player2.three_ship.board_pos_x++;
                        break;
                    case 3:
                        engineState.player2.four_ship.board_pos_x++;
                        break;
                    case 4:
                        engineState.player2.five_ship.board_pos_x++;
                        break;
                }
            case(BUTTON3_PRESS)
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
            }
        }
        engineState.player2.drawMyBoard();
    }
}

//update the board's placement and continuously refresh the board