/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/1/2019                                            *
 ***************************************************************
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Deck.h"
/*
***************************************************************
 Important note:
 
 I'm using this class to confirm the
 general player functions work.
 Once I'm done with this, I'll be adding in the logic
 and virtual functions needed to truly flesh out
 the HumanPlayer and ComputerPlayer classes.
***************************************************************
*/
class Player{
public:
    Player();
    Player(int num);
    int getPoints();
    bool getTurn();
    //Deck* getDeck();
    int getPlayerNumber();
    bool getHumanity();
    bool getIfOut();
    
    void setHumanity(bool isPlayerHuman);
    void setPoints(int newPoints);
    void setTurn(bool isNext);
    //void setDeck(Deck *playerDeck);
    void setPlayerNumber(int num);
    void setOut(bool areYouOut);
    
    // checks if player can go out
    virtual bool requestToGoOut()=0;
    virtual bool checkIfOut(std::vector<Card*> handToCheck)=0;
    //void showHand();
    virtual void sayIfHuman()=0;
    virtual void playRound(Deck *deck)=0;
    virtual void saveGame()=0;
    virtual void examineOptions()=0;
    virtual bool confirmExit()=0;
    
private:
    int playerNumber=0;
    int playerPoints=0;
    bool isTurn=false;
    bool isHuman;
    bool isOut=false;
    //Deck *deck;
    std::vector<Card*> playerCards;
    
};

#endif /* Player_h */
