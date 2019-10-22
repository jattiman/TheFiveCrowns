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
    int getHumanRoundPoints();
    int getComputerRoundPoints();
    
    void setRoundNumber(int newNumber);
    void incrementTurn();
    void incrementRound();
    void setTurn(int nextUp);
    void setHumanRoundPoints(int points);
    void setComputerRoundPoints(int points);

    void setupPlayers(HumanPlayer *h, ComputerPlayer *c);
    
    void giveComputerStatus(std::vector<Player*> ourPlayers);
    void giveHumanStatus(std::vector<Player*> ourPlayers);
    void givePlayerStatus(std::vector<Player*> ourPlayers);
    void getRoundStatus();
    int getValidInput(int minNum=0, int maxNum=500);
    int giveOptions(Player *p);
    
    
    int startRound();
    int endRound();
    int progressRound(Player *p);
    // save game function
    bool saveGame();
    
    // load game functions
    bool promptFileSelection();
    bool loadPlayerOrder(std::string nextPlayer);
    bool loadNums(std::string passedNums, char numChoice);
    bool loadCards(std::string passedHand, char deckChoice);
    bool loadFileStats(std::vector<std::string> passedHand);
    bool loadGame();
    void clearPoints();
    
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
    int humanRoundPoints=0;
    int computerRoundPoints=0;
};


#endif /* Round_h */
