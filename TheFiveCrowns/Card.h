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
    Card(char face, char suite);
    Card(std::string cardString);
    char getFace();
    char getSuite();
    int getPointValue();
    bool getWildStatus();
    int getRoundNumber();
    void setRoundNumber(int newRoundNumber);
    void setFace(char newFace);
    void setSuite(char newSuite);
    void setPointValue();
    void setPointValue(int newPoints);
    void setWildStatus(bool newStatus);
    void checkForWild();
    
private:
    char face;
    char suite;
    int pointValue;
    int roundNumber;
    bool isWild;
    bool isJoker;
    
    
};


#endif /* Card_h */
