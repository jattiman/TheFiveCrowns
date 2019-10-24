/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/22/2019                                            *
 ***************************************************************
 */

#ifndef GAME_H
#define GAME_H

#include "Round.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <vector>

class Game{

public:
    Game();
    void setRoundNumber(int newRound);
    void setNextUp(int nextPlayer);
    int getRoundNumber();
    int getNextUp();
    void welcomeOptions();
    int getValidInput(int minNum=0, int maxNum=500);
    void coinToss();
    void welcome();
    void beginRound();
    bool loadRound();
    void incrementRound();
    void displayEndStats();
    void destroyStats();
    void testGame();
    
    
private:
    int roundNumber=0;
    int nextUp=0;
    Round *round;
    HumanPlayer *h;
    ComputerPlayer *c;
    
};

#endif /* Game_h */
