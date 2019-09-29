/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/1/2019                                            *
 ***************************************************************
 */
#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"

class HumanPlayer: public Player {
public:
    HumanPlayer();
    void sayIfHuman();
    void playRound(Deck *deck);
    bool requestToGoOut();

    
private:
    //bool isHuman;
};



#endif /* HumanPlayer_h */
