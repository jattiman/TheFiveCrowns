/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/1/2019                                            *
 ***************************************************************
 */

#include "Card.h"
#include <iostream>

using namespace std;

Card::Card(){
    //cout << "We made a card! WOW!" << endl;
}

Card::Card(char face, char suite, int theRound){
    this->setSuite(suite);
    this->setFace(face);
    this->setRoundNumber(theRound);
    this->checkForWild();
}

Card::Card(string cardString, int theRound){
    // need to add error checking to this
    this->setSuite(cardString[1]);
    this->setFace(cardString[0]);
    this->setRoundNumber(theRound);
    this->checkForWild();
}

char Card::getFace(){
    return face;
}

char Card::getSuite(){
    return suite;
}
int Card::getPointValue(){
    return pointValue;
}
bool Card::getWildStatus(){
    return isWild;
}
int Card::getRoundNumber(){
    return roundNumber;
}
bool Card::getRunStatus(){
    return isInRun;
}
bool Card::getBookStatus(){
    return isInBook;
}
void Card::setRoundNumber(int newRoundNumber){
    this->roundNumber=newRoundNumber;
    return;
}
void Card::setFace(char newFace){
    this->face=newFace;
    this->setPointValue();
    return;
}
void Card::setSuite(char newSuite){
    this->suite=newSuite;
    return;
}
void Card::setPointValue(int newPoints){
    //cout << "Setting point value to " << newPoints << endl;
    this->pointValue=newPoints;
    return;
}
void Card::setPointValue(){
    switch (this->getFace()) {
        case '3':
            this->setPointValue(3);
            break;
        case '4':
            this->setPointValue(4);
            break;
        case '5':
            this->setPointValue(5);
            break;
        case '6':
            this->setPointValue(6);
            break;
        case '7':
            this->setPointValue(7);
            break;
        case '8':
            this->setPointValue(8);
            break;
        case '9':
            this->setPointValue(9);
            break;
        case 'X':
            this->setPointValue(10);
            break;
        case 'J':
            if(this->getSuite()=='1' || this->getSuite()=='2' || this->getSuite()=='3' || this->getSuite()=='4'){
                this->setPointValue(50);
                this->setWildStatus(true);
            }
            else{
                this->setPointValue(11);
            }
            break;
        case 'Q':
            this->setPointValue(12);
            break;
        case 'K':
            this->setPointValue(13);
            break;
        default:
            cout << "Point Value ut-oh!";
            this->setPointValue(0);
            break;
    }
}

void Card::setWildStatus(bool newStatus){
    this->isWild=newStatus;
    return;
}

void Card::setBookStatus(bool newStatus){
    this->isInBook=newStatus;
    return;
}

void Card::setRunStatus(bool newStatus){
    this->isInRun=newStatus;
    return;
}

//working on this function now. Need to change
// so that Jokers and Jacks aren't confused.
void Card::checkForWild(){
    // if card is Joker, wild status will have already
    // been set to true. Change nothing and return.
    if(this->getPointValue()==50){
        return;
    }
    // if card Face is the same as the round, set wild
    // status to true, points to 20, and return
    if(this->getPointValue()==(this->roundNumber+2)){
//        cout << "Setting wild to true due to round!";
        this->setWildStatus(true);
        this->setPointValue(20);
        return;
    }
//    else{
//        cout << "You shouldn't be here. Round is " << this->getRoundNumber() << " and card points is " << this->getPointValue()<<"!" << endl;
//    }
    return;
}
