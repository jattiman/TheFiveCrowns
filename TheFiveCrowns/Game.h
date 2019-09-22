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
    // need to create vector of players without slicing
    // this is unfinished, but not used yet
    // so the program still works.
    //void addPlayers(std::vector<Player*> &ourPlayers, Player *p);
    
    void incrementRoundNumber();
    void welcome();
    void beginRound();
    void beginRound(HumanPlayer *h, ComputerPlayer *c, int roundNumber);
    // create deck - call round to do this
    // provide round menu - call round to do this
    void testGame();
    
    
private:
    int roundNumber=1;
    Round *round;
    // may end up removing vectors...
    //std::vector<Player*> ourPlayers;
    HumanPlayer *h;
    ComputerPlayer *c;
    
    
};

#endif /* Game_h */
