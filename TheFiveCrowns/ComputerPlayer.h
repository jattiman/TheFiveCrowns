/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/22/2019                                            *
 ***************************************************************
 */

#ifndef ComputerPlayer_h
#define ComputerPlayer_h

#include "Player.h"

class ComputerPlayer: public Player{
public:
    ComputerPlayer();
    void sayIfHuman();
    bool drawCard(Deck *deck);
    void discardCard(Deck *deck);
    void playRound(Deck *deck);
    bool requestToGoOut(Deck *deck);
    int examineOptions(Deck *deck, char choice='a');
    bool confirmExit();
    
private:
    
};

#endif /* ComputerPlayer_h */
