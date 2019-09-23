/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/1/2019                                            *
 ***************************************************************
 */

#ifndef ROUND_H
#define ROUND_H

#include "Deck.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

class Round{
public:
    Round();
    Round(HumanPlayer *h, ComputerPlayer *c);
    Round(HumanPlayer *h, ComputerPlayer *c, int round);
    int getRoundNumber();
    Deck getDeck();
    int returnChoice();
    
    void setupPlayers(HumanPlayer *h, ComputerPlayer *c);
    
    void setRoundNumber(int newNumber);
    
    void giveComputerStatus(std::vector<Player*> ourPlayers);
    void giveHumanStatus(std::vector<Player*> ourPlayers);
    void giveRoundStatus();
    void displayPrompt();
    
    // for debugging only
    void roundTest();
    
private:
    Deck *deck;
    //HumanPlayer *human;
    //ComputerPlayer *computer;
    int roundNumber=1;
    std::vector<Player*> ourPlayers;
};


#endif /* Round_h */
