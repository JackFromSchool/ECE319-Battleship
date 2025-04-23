#include "BoardPlacement.h"
#include "EngineState.h"
#include "Events.h"
#include "Globals.h"
#include "images/images.h"
#include <cstddef>
#include "sounds/sounds.h"
#include "Sound.h"

bool isCollision(Player * player, Ship * ship)
{
    if (ship->rotated) {
        for (int i = 0; i < ship->ship_size; i++) {
            if (player->mine.board[ship->board_pos_y][ship->board_pos_x + i] == TWO_SHIP0 || 
            player->mine.board[ship->board_pos_y][ship->board_pos_x + i] == TWO_SHIP1 || 
            player->mine.board[ship->board_pos_y][ship->board_pos_x + i] == THREE_SHIP || 
            player->mine.board[ship->board_pos_y][ship->board_pos_x + i] == FOUR_SHIP || 
            player->mine.board[ship->board_pos_y][ship->board_pos_x + i] == FIVE_SHIP )
                return true;
        }
    } else {
        for (int i = 0; i < ship->ship_size; i++) {
                if (player->mine.board[ship->board_pos_y - i][ship->board_pos_x] == TWO_SHIP0 || 
                player->mine.board[ship->board_pos_y - i][ship->board_pos_x] == TWO_SHIP1 || 
                player->mine.board[ship->board_pos_y - i][ship->board_pos_x] == THREE_SHIP || 
                player->mine.board[ship->board_pos_y - i][ship->board_pos_x] == FOUR_SHIP || 
                player->mine.board[ship->board_pos_y - i][ship->board_pos_x] == FIVE_SHIP )
                    return true;
             }
        }
    return false;
}

void updateBoard(Player * player)
{
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 10; x++)
        {
            if(x == player->two_ship0.board_pos_x && y == player->two_ship0.board_pos_y)
            {
                player->mine.board[y][x] = TWO_SHIP0;
                if(player->two_ship0.rotated)
                {
                    player->mine.board[y][x + 1] = TWO_SHIP0;
                }
                else {
                    player->mine.board[y - 1][x] = TWO_SHIP0;
                }
            }
            else if (x == player->two_ship1.board_pos_x && y == player->two_ship1.board_pos_y){
                player->mine.board[y][x] = TWO_SHIP1;
                if(player->two_ship1.rotated)
                {
                    player->mine.board[y][x + 1] = TWO_SHIP1;
                }
                else {
                    player->mine.board[y - 1][x] = TWO_SHIP1;
                }
            }
            else if (x == player->three_ship.board_pos_x && y == player->three_ship.board_pos_y){
                player->mine.board[y][x] = THREE_SHIP;
                if(player->three_ship.rotated)
                {
                    player->mine.board[y][x + 1] = THREE_SHIP;
                    player->mine.board[y][x + 2] = THREE_SHIP;
                }
                else {
                    player->mine.board[y - 1][x] = THREE_SHIP;
                    player->mine.board[y - 2][x] = THREE_SHIP;
                }
            }
            else if (x == player->four_ship.board_pos_x && y == player->four_ship.board_pos_y){
                player->mine.board[y][x] = FOUR_SHIP;
                if(player->four_ship.rotated)
                {
                    player->mine.board[y][x + 1] = FOUR_SHIP;
                    player->mine.board[y][x + 2] = FOUR_SHIP;
                    player->mine.board[y][x + 3] = FOUR_SHIP;
                }
                else {
                    player->mine.board[y - 1][x] = FOUR_SHIP;
                    player->mine.board[y - 2][x] = FOUR_SHIP;
                    player->mine.board[y - 3][x] = FOUR_SHIP;
                }
            }
            else if (x == player->five_ship.board_pos_x && y == player->five_ship.board_pos_y){
                player->mine.board[y][x] = FIVE_SHIP;
                if(player->five_ship.rotated)
                {
                    player->mine.board[y][x + 1] = FIVE_SHIP;
                    player->mine.board[y][x + 2] = FIVE_SHIP;
                    player->mine.board[y][x + 3] = FIVE_SHIP;
                    player->mine.board[y][x + 4] = FIVE_SHIP;
                }
                else {
                    player->mine.board[y - 1][x] = FIVE_SHIP;
                    player->mine.board[y - 2][x] = FIVE_SHIP;
                    player->mine.board[y - 3][x] = FIVE_SHIP;
                    player->mine.board[y - 4][x] = FIVE_SHIP;
                }
            }
            else {
                player->mine.board[y][x] = WATER;
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
    if(engineState.player1.numShipsPlaced == 5 && engineState.isPlayer1Turn)
    {
        engineState.switchPlayer();
    }
    if(engineState.player2.numShipsPlaced == 5 && !(engineState.isPlayer1Turn))
    {
        engineState.switchPlayer();
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
            Sound_Start(tick, TICK_LEN);
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
            Sound_Start(tick, TICK_LEN);
            break;
        case JOYSTICK_LEFT:
            //Get the object for Player 1, move the head of the ship in the specified direction
            currShip->isVisible = true;
            if(currShip->board_pos_x - 1 >= 0)
            {
                currShip->set_x(currShip->board_pos_x - 1);
            }
            Sound_Start(tick, TICK_LEN);
            break;
        case JOYSTICK_RIGHT:
            //Get the object for Player 1, move the head of the ship in the specified direction
            currShip->isVisible = true;
            if((currShip->board_pos_x + currShip->ship_size) <= 9 && currShip->rotated)
            {
                currShip->set_x(currShip->board_pos_x + 1);
            }
            else if(currShip->board_pos_x + 1 <= 9 && !currShip->rotated) {
                currShip->set_x(currShip->board_pos_x + 1);
            }
            Sound_Start(tick, TICK_LEN);
            break;
        case BUTTON3_PRESS:
            if(!(isCollision(tempPlayer, currShip)))
            {
                tempPlayer->numShipsPlaced++;
                updateBoard(tempPlayer);
            }
            break;
        case BUTTON1_PRESS:
            switch(tempPlayer->numShipsPlaced)
            {
                case 0:
                    tempPlayer->two_ship0.isVisible = true;
                    if(tempPlayer->two_ship0.rotated && (tempPlayer->two_ship0.board_pos_y > 0))
                    {
                        tempPlayer->two_ship0.sprite = Sprite(two_space_battleship1, BOARDSPACEX(tempPlayer->two_ship0.board_pos_x), BOARDSPACEY(tempPlayer->two_ship0.board_pos_y), 11, 22);
                        tempPlayer->two_ship0.rotated = false;
                    } else if (!tempPlayer->two_ship0.rotated && tempPlayer->two_ship0.board_pos_x + 1 < 10) {
                        tempPlayer->two_ship0.sprite = Sprite(two_space_battleship190, BOARDSPACEX(tempPlayer->two_ship0.board_pos_x), BOARDSPACEY(tempPlayer->two_ship0.board_pos_y), 22, 11);
                        tempPlayer->two_ship0.rotated = true;
                    }
                    break;
                case 1:
                    tempPlayer->two_ship1.isVisible = true;
                    if(tempPlayer->two_ship1.rotated  && (tempPlayer->two_ship1.board_pos_y > 0))
                    {
                        tempPlayer->two_ship1.sprite = Sprite(two_space_battleship2, BOARDSPACEX(tempPlayer->two_ship1.board_pos_x), BOARDSPACEY(tempPlayer->two_ship1.board_pos_y), 11, 22);
                        tempPlayer->two_ship1.rotated = false;
                    } else if (!tempPlayer->two_ship1.rotated && tempPlayer->two_ship1.board_pos_x + 1 < 10) {
                        tempPlayer->two_ship1.sprite = Sprite(two_space_battleship290, BOARDSPACEX(tempPlayer->two_ship1.board_pos_x), BOARDSPACEY(tempPlayer->two_ship1.board_pos_y), 22, 11);
                        tempPlayer->two_ship1.rotated = true;
                    }
                    break;
                case 2:
                    tempPlayer->three_ship.isVisible = true;
                    if(tempPlayer->three_ship.rotated && (tempPlayer->three_ship.board_pos_y - 1 > 0))
                    {
                        tempPlayer->three_ship.sprite = Sprite(three_space_battleship, BOARDSPACEX(tempPlayer->three_ship.board_pos_x), BOARDSPACEY(tempPlayer->three_ship.board_pos_y), 11, 33);
                        tempPlayer->three_ship.rotated = false;
                    } else if (!tempPlayer->three_ship.rotated && (tempPlayer->three_ship.board_pos_x + 2 < 10)) {
                        tempPlayer->three_ship.sprite = Sprite(three_space_battleship90, BOARDSPACEX(tempPlayer->three_ship.board_pos_x), BOARDSPACEY(tempPlayer->three_ship.board_pos_y), 33, 11);
                        tempPlayer->three_ship.rotated = true;
                    }
                    break;
                case 3:
                    tempPlayer->four_ship.isVisible = true;
                    if(tempPlayer->four_ship.rotated && (tempPlayer->four_ship.board_pos_y - 2 > 0))
                    {
                        tempPlayer->four_ship.sprite = Sprite(four_space_battleship, BOARDSPACEX(tempPlayer->four_ship.board_pos_x), BOARDSPACEY(tempPlayer->four_ship.board_pos_y), 11, 44);
                        tempPlayer->four_ship.rotated = false;
                    } else if (!tempPlayer->four_ship.rotated && (tempPlayer->four_ship.board_pos_x + 3 < 10)){
                        tempPlayer->four_ship.sprite = Sprite(four_space_battleship90, BOARDSPACEX(tempPlayer->four_ship.board_pos_x), BOARDSPACEY(tempPlayer->four_ship.board_pos_y), 44, 11);
                        tempPlayer->four_ship.rotated = true;
                    }
                    break;
                case 4:
                    tempPlayer->five_ship.isVisible = true;
                    if(tempPlayer->five_ship.rotated && (tempPlayer->five_ship.board_pos_y - 3 > 0))
                    {
                        tempPlayer->five_ship.sprite = Sprite(five_space_battleship, BOARDSPACEX(tempPlayer->five_ship.board_pos_x), BOARDSPACEY(tempPlayer->five_ship.board_pos_y), 11, 55);
                        tempPlayer->five_ship.rotated = false;
                    } else if (!tempPlayer->five_ship.rotated && (tempPlayer->five_ship.board_pos_x + 4 < 10)){
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