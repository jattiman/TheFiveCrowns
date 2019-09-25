/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/1/2019                                            *
 ***************************************************************
 */

#ifndef ComputerPlayer_h
#define ComputerPlayer_h

#include "Player.h"

class ComputerPlayer: public Player{
public:
    ComputerPlayer();
    void sayIfHuman();
    void playRound();
    
private:
    //bool isHuman;
};

#endif /* ComputerPlayer_h */
