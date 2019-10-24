/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/22/2019                                            *
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
    std::string getCardString();
    int getPointValue();
    bool getWildStatus();
    int getRoundNumber();
    bool getRunStatus();
    bool getBookStatus();
    void setRoundNumber(int newRoundNumber);
    void setFace(char newFace);
    void setSuite(char newSuite);
    void setCardString();
    void setPointValue(int newPoints);
    void setPointValue();
    void setWildStatus(bool newStatus);
    void setBookStatus(bool newStatus);
    void setRunStatus(bool newStatus);
    void checkForWild();
    
    
private:
    char face;
    char suite;
    int pointValue;
    int roundNumber=3;
    bool isWild=false;
    bool isJoker;
    bool isInBook=false;
    bool isInRun=false;
    std::string cardString;
    
};


#endif /* Card_h */
