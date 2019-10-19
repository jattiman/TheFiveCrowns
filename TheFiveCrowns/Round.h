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
    ~Round();
    Round(HumanPlayer *h, ComputerPlayer *c);
    Round(HumanPlayer *h, ComputerPlayer *c, int round, int whosTurn = 0);
    Round(std::vector<Player*> thePlayers);
    int getRoundNumber();
    int getTurn();
    int getTotalPlayers();
    Deck getDeck();
    
    void setRoundNumber(int newNumber);
    void setTurn();
    void setTurn(int nextUp);

    void setupPlayers(HumanPlayer *h, ComputerPlayer *c);
    
    void giveComputerStatus(std::vector<Player*> ourPlayers);
    void giveHumanStatus(std::vector<Player*> ourPlayers);
    void givePlayerStatus(std::vector<Player*> ourPlayers);
    void getRoundStatus();
    int giveOptions(Player *p);
    
    
    void startRound();
    void progressRound(Player *p);
    bool saveGame();
    bool promptFileSelection();
    bool loadFileStats(std::vector<std::string> passedHand);
    bool loadGame();
    
    // for debugging only
    void roundTest();
    
private:
    Deck *deck;
    //HumanPlayer *human;
    //ComputerPlayer *computer;
    int roundNumber;
    int nextTurn;
    int totalPlayers;
    std::vector<Player*> ourPlayers;
};


#endif /* Round_h */
