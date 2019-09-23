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
    this->deck = new Deck(this->getRoundNumber());
}

Round::Round(HumanPlayer *h, ComputerPlayer *c){
    this->deck = new Deck(this->getRoundNumber());
    this->setupPlayers(h,c);
    this->displayPrompt();
}

Round::Round(HumanPlayer *h, ComputerPlayer *c, int round){
    this->setRoundNumber(round);
    this->deck = new Deck(this->getRoundNumber());
    this->setupPlayers(h,c);
    this->displayPrompt();
}


void Round::setupPlayers(HumanPlayer *h, ComputerPlayer *c){
//    this->human=h;
//    this->computer=c;
    // trying the vector approach ...
    this->ourPlayers.push_back(h);
    this->ourPlayers.push_back(c);
//    this->ourPlayers.push_back(this->human);
//    this->ourPlayers.push_back(this->computer);
//    cout << "Is 0 human?: " << ourPlayers[0]->getHumanity() << endl;
//    cout << "Is 1 human?: " << ourPlayers[1]->getHumanity() << endl;
}

int Round::getRoundNumber(){
    return roundNumber;
}

Deck Round::getDeck(){
    return *deck;
}

void Round::setRoundNumber(int newNumber){
    this->roundNumber=newNumber;
}

void Round::giveComputerStatus(std::vector<Player*> players){
    for(auto &i: players){
        if(!(i->getHumanity())){
            cout << "Computer:" << endl
            << "\tScore: " << players[1]->getPoints() << endl
            << "\tHand: " << endl
            << endl;
        }
    }
    return;
    
}
void Round::giveHumanStatus(std::vector<Player*> players){
    for(auto &i: players){
        if(i->getHumanity()){
            cout << "Human:" << endl
            << "\tScore: " << players[1]->getPoints() << endl
            << "\tHand: " << endl
            << endl;
        }
    }
    return;
    
}

void Round::giveRoundStatus(){
    cout << "Round: " << this->getRoundNumber() << endl
        << endl;
    this->giveComputerStatus(this->ourPlayers);
    this->giveHumanStatus(this->ourPlayers);
    this->deck->printDecks();
    cout << endl
    << "Next player: " << endl;
    //this->roundTest();
    return;
}

int Round::returnChoice(){
    cout << "Please choose from the following:";
    /*

     Save the game
     Make a move
     Ask for help (only before human player plays)
     Quit the game
     
     */
    return 0;
}

void Round::displayPrompt(){
    this->giveRoundStatus();
    
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
