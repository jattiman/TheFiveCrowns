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
    this->setRoundNumber(1);
    this->deck = new Deck(this->getRoundNumber());
}

Round::Round(HumanPlayer *h, ComputerPlayer *c){
    this->setRoundNumber(1);
    this->deck = new Deck(this->getRoundNumber());
    this->setupPlayers(h,c);
    //this->progressRound();
}

Round::Round(HumanPlayer *h, ComputerPlayer *c, int round){
    this->setRoundNumber(round);
    this->deck = new Deck(this->getRoundNumber());
    this->setupPlayers(h,c);
    //this->progressRound();
}


void Round::setupPlayers(HumanPlayer *h, ComputerPlayer *c){
    this->ourPlayers.push_back(h);
    this->ourPlayers.push_back(c);
//    cout << "Is 0 human?: " << ourPlayers[0]->getHumanity() << endl;
//    cout << "Is 1 human?: " << ourPlayers[1]->getHumanity() << endl;
}

int Round::getRoundNumber(){
    return roundNumber;
}

int Round::getTurn(){
    return nextTurn;
}

int Round::getTotalPlayers(){
    return this->ourPlayers.size();
}

Deck Round::getDeck(){
    return *deck;
}

void Round::setRoundNumber(int newNumber){
    this->roundNumber=newNumber;
}
void Round::setTurn(){
    this->nextTurn++;
    return;
}
void Round::setTurn(int nextUp){
    this->nextTurn=nextUp;
    return;
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
    int userChoice=0;
    do{
        cout << "Please choose from the following:" << endl
        << "\t1. Save the game" << endl
        << "\t2. Make a move" << endl
        << "\t3. Ask for help (only before human player plays)" << endl
        << "\t4. Quit the game" << endl;
        cin >> userChoice;
    } while(userChoice < 1 || userChoice > 4);
    
    switch (userChoice) {
        case 1:
            cout << "Saving game ..." << endl;
            break;
        case 2:
            cout << "Making move .. " << endl;
            break;
        case 3:
            cout << "Here's some advice: " << endl;
            break;
        case 4:
            cout << "Thank you for playing. Exiting without saving." << endl;
            break;
        default:
            cout << "You shouldn't see this." << endl;
            break;
    }
    return 0;
}

int Round::returnChoice(Player *p){
    int userChoice=0;
    if(p->getHumanity()){
        do{
            cout << "Please choose from the following:" << endl
            << "\t1. Save the game" << endl
            << "\t2. Make a move" << endl
            << "\t3. Ask for help (only before human player plays)" << endl
            << "\t4. Quit the game" << endl;
            cin >> userChoice;
        } while(userChoice < 1 || userChoice > 4);
        
        switch (userChoice) {
            case 1:
                cout << "Saving game ..." << endl;
                break;
            case 2:
                cout << "Making move .. " << endl;
                break;
            case 3:
                cout << "Here's some advice: " << endl;
                break;
            case 4:
                cout << "Thank you for playing. Exiting without saving." << endl;
                break;
            default:
                cout << "You shouldn't see this." << endl;
                break;
        }
    }
    else{
        cout << "The computer is choosing its next action..." << endl;
    }
    return 0;
}


void Round::progressRound(){
    do{
    //this->giveRoundStatus();
    this->returnChoice(ourPlayers[this->getTurn()% this->getTotalPlayers()]);
    this->setTurn();
    // adding in a dummy value here to test player rotation
    }while(this->getTurn()<7);
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
