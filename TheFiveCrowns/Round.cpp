/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/1/2019                                            *
 ***************************************************************
 */

#include "Round.h"
#include <iostream>

using namespace std;

Round::Round(){
    this->deck = new Deck();
}

Round::Round(HumanPlayer *h, ComputerPlayer *c){
    this->deck = new Deck();
    this->setupPlayers(h,c);
}

void Round::setupPlayers(HumanPlayer *h, ComputerPlayer *c){
    this->human=h;
    this->computer=c;
}

int Round::getRoundNumber(){
    return roundNumber;
}

Deck Round::getDeck(){
    return *deck;
}

// this function may ultimately be taken out
void Round::setupRound(){
    cout << "Round setting up ... " << endl;
    // create the deck
    //this->deck->makeDeck();
    //this->deck = new Deck();
    
    // pass to the player
    //roundTest();
    return;
}

void Round::setupRound(HumanPlayer *h, ComputerPlayer *c, int roundNumber){
    this->setupPlayers(h,c);
    this->setRoundNumber(roundNumber);
}

void Round::setRoundNumber(int newNumber){
    this->roundNumber=newNumber;
}

void Round::displayPrompt(){
    cout << "Round: " << this->getRoundNumber() << endl
        << endl
        << "Computer:" << endl
        << "\tScore: " << endl
        << "\tHand: " << endl
        << endl
        << "Human:" << endl
        << "\tScore: " << endl
        << "\tHand: " << endl
        << endl;
    this->deck->printDecks();
    cout << endl
    << "Next player: " << endl;
    this->roundTest();
    return;
}

void Round::roundTest(){
    cout << "\tRound Test" << endl;
    // Confirm we can print the deck
    //cout << "Printing the deck." << endl;
    //this->deck->printDecks();
    
    // Confirm that we can print a PLAYER deck
    // NOTE: I'll need to redo this. We don't want to mirror the deck
    //      for each player. Instead, we want to put ownership in the cards
    //      themselves, so they can pull up the player info.
//    cout << "Printing human player deck." << endl;
//    this->human->setDeck(this->deck);
//    this->human->showHand();
    return;
}
