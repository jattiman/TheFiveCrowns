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
    int getValidInput(int minNum, int maxNum);
    bool drawCard(Deck *deck);
    void discardCard(Deck *deck);
    void playRound(Deck *deck);
    bool requestToGoOut(Deck *deck);
//    void saveGame();
    int examineOptions(Deck *deck, char choice='a');
    bool confirmExit();
    void testOutPut();
    
private:

};



#endif /* HumanPlayer_h */
