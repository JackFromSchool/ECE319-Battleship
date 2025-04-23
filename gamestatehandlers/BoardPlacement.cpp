#include "BoardPlacement.h"
#include "EngineState.h"
#include "Events.h"
#include "Globals.h"
#include <cstddef>

bool isOutOfBounds(Player * player)
{
    Ship * temp;
    switch(player->numShipsPlaced)
    {
        case 0:
            temp = &(player->two_ship0);
            break;
        case 1:
            temp = &(player->two_ship1);
            break;
        case 2:
            temp = &(player->three_ship);
            break;
        case 3:
            temp = &(player->four_ship);
            break;
        case 4:
            temp = &(player->five_ship);
            break;
    }

    if(temp->rotated)
    {
        if((temp->board_pos_x + (temp->ship_size - 1) + 1) > 9 || (temp->board_pos_x  - 1) < 0 || (temp->board_pos_y + 1) > 9 || (temp->board_pos_y - 1) < 0)
        {
            return false;
        }
    }
    else {
        if((temp->board_pos_x + 1) > 9 || (temp->board_pos_x - 1) < 0 || (temp->board_pos_y + 1) > 9 || (temp->board_pos_y - (temp->ship_size - 1) - 1) < 0)
        {
            return false;
        }
    }
    return true;
}

void initBoardPlacement() {
    engineState.isPlayer1Turn = true;
    engineState.player1.drawMyBoard();
}

enum GameState handleBoardPlacement(enum Event event) 
{
    Player * tempPlayer;
    if(event == BUTTON0_PRESS || event == BUTTON0_UNPRESS || event == BUTTON1_PRESS || event == BUTTON1_UNPRESS || event == BUTTON2_PRESS || event == BUTTON2_UNPRESS)
    {
        return BOARD_PLACEMENT;
    }
    if(engineState.player1.numShipsPlaced == 5 && engineState.player2.numShipsPlaced == 5)
    {
        return ACTIVE_GAME;
    }
    if((engineState.isPlayer1Turn && isOutOfBounds(&engineState.player1)) || (!engineState.isPlayer1Turn && isOutOfBounds(&engineState.player2)))
    {
        return BOARD_PLACEMENT;
    }

    if(engineState.isPlayer1Turn)
    {
        tempPlayer = &engineState.player1;
    }
    else {
        tempPlayer = &engineState.player2;
    }
    
    switch(event)
    {
        case JOYSTICK_DOWN:
            //Get the object for Player 1, move the head of the ship in the specified direction
            switch(tempPlayer->numShipsPlaced)
            {
                case 0:
                    tempPlayer->two_ship0.set_y(engineState.player1.two_ship0.board_pos_y - 1);
                    break;
                case 1:
                    tempPlayer->two_ship1.set_y(engineState.player1.two_ship1.board_pos_y - 1);
                    break;
                case 2:
                    tempPlayer->three_ship.set_y(engineState.player1.three_ship.board_pos_y - 1);
                    break;
                case 3:
                    tempPlayer->four_ship.set_y(engineState.player1.four_ship.board_pos_y - 1);
                    break;
                case 4:
                    tempPlayer->five_ship.set_y(engineState.player1.five_ship.board_pos_y - 1);
                    break;
            }
            break;
        case JOYSTICK_UP:
            //Get the object for Player 1, move the head of the ship in the specified direction
            switch(tempPlayer->numShipsPlaced)
            {
                case 0:
                    tempPlayer->two_ship0.set_y(engineState.player1.two_ship0.board_pos_y + 1);
                    break;
                case 1:
                    tempPlayer->two_ship1.set_y(engineState.player1.two_ship1.board_pos_y + 1);
                    break;
                case 2:
                    tempPlayer->three_ship.set_y(engineState.player1.three_ship.board_pos_y + 1);
                    break;
                case 3:
                    tempPlayer->four_ship.set_y(engineState.player1.four_ship.board_pos_y + 1);
                    break;
                case 4:
                    tempPlayer->five_ship.set_y(engineState.player1.five_ship.board_pos_y + 1);
                    break;
            }
            break;
        case JOYSTICK_LEFT:
            //Get the object for Player 1, move the head of the ship in the specified direction
            switch(tempPlayer->numShipsPlaced)
            {
                case 0:
                    tempPlayer->two_ship0.set_x(engineState.player1.two_ship0.board_pos_x - 1);
                    break;
                case 1:
                    tempPlayer->two_ship1.set_x(engineState.player1.two_ship1.board_pos_x - 1);
                    break;
                case 2:
                    tempPlayer->three_ship.set_x(engineState.player1.three_ship.board_pos_x - 1);
                    break;
                case 3:
                    tempPlayer->four_ship.set_x(engineState.player1.four_ship.board_pos_x - 1);
                    break;
                case 4:
                    tempPlayer->five_ship.set_x(engineState.player1.five_ship.board_pos_x - 1);
                    break;
            }
            break;
        case JOYSTICK_RIGHT:
            //Get the object for Player 1, move the head of the ship in the specified direction
            switch(tempPlayer->numShipsPlaced)
            {
                case 0:
                    tempPlayer->two_ship0.set_x(engineState.player1.two_ship0.board_pos_x + 1);
                    break;
                case 1:
                    tempPlayer->two_ship1.set_x(engineState.player1.two_ship1.board_pos_x + 1);
                    break;
                case 2:
                    tempPlayer->three_ship.set_x(engineState.player1.three_ship.board_pos_x + 1);
                    break;
                case 3:
                    tempPlayer->four_ship.set_x(engineState.player1.four_ship.board_pos_x + 1);
                    break;
                case 4:
                    tempPlayer->five_ship.set_x(engineState.player1.five_ship.board_pos_x + 1);
                    break;
            }
            break;
        case BUTTON3_PRESS:
        {
            switch(tempPlayer->numShipsPlaced)
            {
                case 0:
                    tempPlayer->two_ship0.isPlaced = true;
                    break;
                case 1:
                    tempPlayer->two_ship1.isPlaced = true;
                    break;
                case 2:
                    tempPlayer->three_ship.isPlaced = true;
                    break;
                case 3:
                    tempPlayer->four_ship.isPlaced = true;
                    break;
                case 4:
                    tempPlayer->five_ship.isPlaced = true;
                    break;
            }
            tempPlayer->numShipsPlaced++;
            break;
        }
    }
    tempPlayer->drawMyBoard();
    return BOARD_PLACEMENT;
}

//update the board's placement and continuously refresh the board