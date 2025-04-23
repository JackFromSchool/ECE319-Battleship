#include "BoardPlacement.h"
#include "EngineState.h"
#include "Events.h"
#include "Globals.h"
#include "images/images.h"
#include <cstddef>

void updateBoard(Player * player)
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(i == player->two_ship0.board_pos_x && j == player->two_ship0.board_pos_y)
            {
                player->mine.board[i][j] = TWO_SHIP0;
                if(player->two_ship0.rotated)
                {
                    player->mine.board[i][j + 1] = TWO_SHIP0;
                }
                else {
                    player->mine.board[i - 1][j] = TWO_SHIP0;
                }
            }
            else if (i == player->two_ship1.board_pos_x && j == player->two_ship1.board_pos_y){
                player->mine.board[i][j] = TWO_SHIP1;
                if(player->two_ship1.rotated)
                {
                    player->mine.board[i][j + 1] = TWO_SHIP1;
                }
                else {
                    player->mine.board[i - 1][j] = TWO_SHIP1;
                }
            }
            else if (i == player->three_ship.board_pos_x && j == player->three_ship.board_pos_y){
                player->mine.board[i][j] = THREE_SHIP;
                if(player->three_ship.rotated)
                {
                    player->mine.board[i][j + 1] = THREE_SHIP;
                    player->mine.board[i][j + 2] = THREE_SHIP;
                }
                else {
                    player->mine.board[i - 1][j] = THREE_SHIP;
                    player->mine.board[j - 2][j] = THREE_SHIP;
                }
            }
            else if (i == player->four_ship.board_pos_x && j == player->four_ship.board_pos_y){
                player->mine.board[i][j] = FOUR_SHIP;
                if(player->four_ship.rotated)
                {
                    player->mine.board[i][j + 1] = FOUR_SHIP;
                    player->mine.board[i][j + 2] = FOUR_SHIP;
                    player->mine.board[i][j + 3] = FOUR_SHIP;
                }
                else {
                    player->mine.board[i - 1][j] = FOUR_SHIP;
                    player->mine.board[i - 2][j] = FOUR_SHIP;
                    player->mine.board[i - 3][j] = FOUR_SHIP;
                }
            }
            else if (i == player->five_ship.board_pos_x && j == player->five_ship.board_pos_y){
                player->mine.board[i][j] = FIVE_SHIP;
                if(player->five_ship.rotated)
                {
                    player->mine.board[i][j + 1] = FIVE_SHIP;
                    player->mine.board[i][j + 2] = FIVE_SHIP;
                    player->mine.board[i][j + 3] = FIVE_SHIP;
                    player->mine.board[i][j + 4] = FIVE_SHIP;
                }
                else {
                    player->mine.board[i - 1][j] = FIVE_SHIP;
                    player->mine.board[i - 2][j] = FIVE_SHIP;
                    player->mine.board[i - 3][j] = FIVE_SHIP;
                    player->mine.board[i - 4][j] = FIVE_SHIP;
                }
            }
            else {
                player->mine.board[i][j] = WATER;
            }
        }
    }
}

void initBoardPlacement() {
    engineState.isPlayer1Turn = true;
    engineState.player1.drawMyBoard();
}

enum GameState handleBoardPlacement(enum Event event) 
{
    Player * tempPlayer;
    Ship * currShip;
    if(event == BUTTON0_PRESS || event == BUTTON0_UNPRESS || event == BUTTON2_PRESS || event == BUTTON2_UNPRESS)
    {
        return BOARD_PLACEMENT;
    }
    if(engineState.player1.numShipsPlaced == 5 && engineState.player2.numShipsPlaced == 5)
    {
        updateBoard(&engineState.player1);
        updateBoard(&engineState.player2);
        return ACTIVE_GAME;
    }
    if(engineState.isPlayer1Turn)
    {
        tempPlayer = &engineState.player1;
    }
    else {
        tempPlayer = &engineState.player2;
    }

    switch(tempPlayer->numShipsPlaced)
    {
        case 0:
            currShip = &(tempPlayer->two_ship0);
            break;
        case 1:
            currShip = &(tempPlayer->two_ship1);
            break;
        case 2:
            currShip = &(tempPlayer->three_ship);
            break;
        case 3:
            currShip = &(tempPlayer->four_ship);
            break;
        case 4:
            currShip = &(tempPlayer->five_ship);
            break;
    }
    
    switch(event)
    {
        case JOYSTICK_DOWN:
            //Get the object for Player 1, move the head of the ship in the specified direction
            currShip->isVisible = true;
            if(currShip->board_pos_y + 1 <= 9)
            {
                currShip->set_y(currShip->board_pos_y + 1);
            }
            break;
        case JOYSTICK_UP:
            //Get the object for Player 1, move the head of the ship in the specified direction
            currShip->isVisible = true;
            if(currShip->board_pos_y - 1 >= 0 && currShip->rotated)
            {
                currShip->set_y(currShip->board_pos_y - 1);
            }
            else if(currShip->board_pos_y - currShip->ship_size >= 0)
            {
                currShip->set_y(currShip->board_pos_y - 1);
            }
            break;
        case JOYSTICK_LEFT:
            //Get the object for Player 1, move the head of the ship in the specified direction
            currShip->isVisible = true;
            if(currShip->board_pos_x - 1 >= 0)
            {
                currShip->set_x(currShip->board_pos_x - 1);
            }
            break;
        case JOYSTICK_RIGHT:
            //Get the object for Player 1, move the head of the ship in the specified direction
            currShip->isVisible = true;
            if((currShip->board_pos_x + currShip->ship_size - 1) <= 9 && currShip->rotated)
            {
                currShip->set_x(currShip->board_pos_x + 1);
            }
            else if(currShip->board_pos_x + 1 <= 9) {
                currShip->set_x(currShip->board_pos_x + 1);
            }
            break;
        case BUTTON3_PRESS:
            tempPlayer->numShipsPlaced++;
            break;
        case BUTTON1_PRESS:
            switch(tempPlayer->numShipsPlaced)
            {
                case 0:
                    tempPlayer->two_ship0.isVisible = true;
                    if(tempPlayer->two_ship0.rotated)
                    {
                        tempPlayer->two_ship0.sprite = Sprite(two_space_battleship1, BOARDSPACEX(tempPlayer->two_ship0.board_pos_x), BOARDSPACEY(tempPlayer->two_ship0.board_pos_y), 11, 22);
                        tempPlayer->two_ship0.rotated = false;
                    } else {
                        tempPlayer->two_ship0.sprite = Sprite(two_space_battleship190, BOARDSPACEX(tempPlayer->two_ship0.board_pos_x), BOARDSPACEY(tempPlayer->two_ship0.board_pos_y), 22, 11);
                        tempPlayer->two_ship0.rotated = true;
                    }
                    break;
                case 1:
                    tempPlayer->two_ship1.isVisible = true;
                    if(tempPlayer->two_ship1.rotated)
                    {
                        tempPlayer->two_ship1.sprite = Sprite(two_space_battleship2, BOARDSPACEX(tempPlayer->two_ship1.board_pos_x), BOARDSPACEY(tempPlayer->two_ship1.board_pos_y), 11, 22);
                        tempPlayer->two_ship1.rotated = false;
                    } else {
                        tempPlayer->two_ship1.sprite = Sprite(two_space_battleship290, BOARDSPACEX(tempPlayer->two_ship1.board_pos_x), BOARDSPACEY(tempPlayer->two_ship1.board_pos_y), 22, 11);
                        tempPlayer->two_ship1.rotated = true;
                    }
                    break;
                case 2:
                    tempPlayer->three_ship.isVisible = true;
                    if(tempPlayer->three_ship.rotated)
                    {
                        tempPlayer->three_ship.sprite = Sprite(three_space_battleship, BOARDSPACEX(tempPlayer->three_ship.board_pos_x), BOARDSPACEY(tempPlayer->three_ship.board_pos_y), 11, 33);
                        tempPlayer->three_ship.rotated = false;
                    } else {
                        tempPlayer->three_ship.sprite = Sprite(three_space_battleship90, BOARDSPACEX(tempPlayer->three_ship.board_pos_x), BOARDSPACEY(tempPlayer->three_ship.board_pos_y), 33, 11);
                        tempPlayer->three_ship.rotated = true;
                    }
                    break;
                case 3:
                    tempPlayer->four_ship.isVisible = true;
                    if(tempPlayer->four_ship.rotated)
                    {
                        tempPlayer->four_ship.sprite = Sprite(four_space_battleship, BOARDSPACEX(tempPlayer->four_ship.board_pos_x), BOARDSPACEY(tempPlayer->four_ship.board_pos_y), 11, 44);
                        tempPlayer->four_ship.rotated = false;
                    } else {
                        tempPlayer->four_ship.sprite = Sprite(four_space_battleship90, BOARDSPACEX(tempPlayer->four_ship.board_pos_x), BOARDSPACEY(tempPlayer->four_ship.board_pos_y), 44, 11);
                        tempPlayer->four_ship.rotated = true;
                    }
                    break;
                case 4:
                    tempPlayer->five_ship.isVisible = true;
                    if(tempPlayer->five_ship.rotated)
                    {
                        tempPlayer->five_ship.sprite = Sprite(five_space_battleship, BOARDSPACEX(tempPlayer->five_ship.board_pos_x), BOARDSPACEY(tempPlayer->five_ship.board_pos_y), 11, 55);
                        tempPlayer->five_ship.rotated = false;
                    } else {
                        tempPlayer->five_ship.sprite = Sprite(five_space_battleship90, BOARDSPACEX(tempPlayer->five_ship.board_pos_x), BOARDSPACEY(tempPlayer->five_ship.board_pos_y), 55, 11);
                        tempPlayer->five_ship.rotated = true;
                    }
                    break;
            }
            break;
            
    }
    tempPlayer->drawMyBoard();
    return BOARD_PLACEMENT;
}

//update the board's placement and continuously refresh the board