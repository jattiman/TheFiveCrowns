/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/1/2019                                            *
 ***************************************************************
 */

#ifndef CARD_H
#define CARD_H
#include "CardSuites.cpp"
#include <string>

class Card{

public:
    Card();
    Card(char face, char suite, int theRound);
    Card(std::string cardString, int theRound);
    char getFace();
    char getSuite();
    int getPointValue();
    bool getWildStatus();
    int getRoundNumber();
    void setRoundNumber(int newRoundNumber);
    void setFace(char newFace);
    void setSuite(char newSuite);
    void setPointValue(int newPoints);
    void setPointValue();
    void setWildStatus(bool newStatus);
    void checkForWild();
    
private:
    char face;
    char suite;
    int pointValue;
    int roundNumber=3;
    bool isWild=false;
    bool isJoker;
    
    
};


#endif /* Card_h */
