/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/22/2019                                            *
 ***************************************************************
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Deck.h"

class Player{
public:
    Player();
    Player(int num);
    int getPoints();
    bool getTurn();
    int getPlayerNumber();
    bool getHumanity();
    bool getIfOut();
    
    void setHumanity(bool isPlayerHuman);
    void setTotalPoints(int totalPoints);
    void addPoints(int newPoints);
    void setTurn(bool isNext);
    void setPlayerNumber(int num);
    void setOut(bool areYouOut);
    void deletePoints();
    
    // virtual functions
    virtual bool requestToGoOut(Deck *deck)=0;
    virtual void sayIfHuman()=0;
    virtual bool drawCard(Deck *deck)=0;
    virtual void discardCard(Deck *deck)=0;
    virtual void playRound(Deck *deck)=0;
    virtual int examineOptions(Deck *deck, char choice='a')=0;
    virtual bool confirmExit()=0;
    
private:
    int playerNumber=0;
    int playerPoints=0;
    bool isTurn=false;
    bool isHuman;
    bool isOut=false;
    std::vector<Card*> playerCards;
    
};

#endif /* Player_h */
