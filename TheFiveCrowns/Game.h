/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/1/2019                                            *
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
    
    int getRoundNumber();
    void welcomeOptions();
    void welcome();
    void beginRound();
//    void beginRound(HumanPlayer *h, ComputerPlayer *c, int roundNumber);
    bool loadRound();
//    void beginRound(HumanPlayer *h, ComputerPlayer *c, Deck * savedDeck, int roundNumber);
    void incrementRound();
    void displayEndStats();
    void destroyStats();
    // create deck - call round to do this
    // provide round menu - call round to do this
    void testGame();
    
    
private:
    int roundNumber;
    Round *round;
    // may end up removing vectors...
    //std::vector<Player*> ourPlayers;
    HumanPlayer *h;
    ComputerPlayer *c;
    
    
};

#endif /* Game_h */
