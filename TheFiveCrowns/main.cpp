/*
***************************************************************
* Name:  John Atti                                            *
* Project:  5Crowns C++ Project 1                             *
* Class:  CMPS 366 01 - Organization of Programming Languages *
* Date:  10/1/2019                                            *
***************************************************************
 */
#include "Game.h"
#include <iostream>
using namespace std;

/* *********************************************************************
 Function Name: main
 Purpose: Starts the game
 Parameters: None used
 Return Value: None (0)
 Local Variables:
    ourGame (Game object): calls the Game
 Algorithm: None used.
 Assistance Received: None.
 ********************************************************************* */

int main(int argc, const char * argv[]) {
    
    Game ourGame;
    ourGame.welcome();

    //cout << "Back in main, now." << endl;   // debug
    return 0;
}
