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
    Deck* getDeck();
    int getPlayerNumber();
    bool getHumanity();
    
    void setHumanity(bool isPlayerHuman);
    void setPoints(int newPoints);
    void setTurn(bool isNext);
    void setDeck(Deck *playerDeck);
    void setPlayerNumber(int num);
    
    void showHand();
    virtual void sayIfHuman()=0;
    
private:
    int playerNumber=0;
    int playerPoints=0;
    bool isTurn=false;
    bool isHuman;
    Deck *deck;
    
};

#endif /* Player_h */
