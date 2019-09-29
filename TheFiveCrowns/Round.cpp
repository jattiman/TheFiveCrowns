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

Round::~Round(){
    cout << "\t\tRound ended." << endl;
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
}

int Round::getRoundNumber(){
    return roundNumber;
}

int Round::getTurn(){
    return nextTurn;
}

int Round::getTotalPlayers(){
    return (int)this->ourPlayers.size();
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
            << "\tHand: ";
            this->deck->getHumanDeck();
            cout << endl;
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

int Round::returnChoice(Player *p){
    int userChoice=0;
    // if player is human, give human options
    if(p->getHumanity()){
        do{
            cout << "Please choose from the following:" << endl
            << "\t1. Save the game" << endl
            << "\t2. Make a move" << endl
            << "\t3. Ask for help (only before human player plays)" << endl
            << "\t4. Quit the game" << endl;
            cin >> userChoice;
        } while(userChoice < 1 || userChoice > 4);
    }
    else{
        cout << "The computer is choosing its next action..." << endl
            << "\t1. Save the game" << endl
            << "\t2. Make a move" << endl
            << "\t3. Quit the game" << endl;
        cout << "Computer chooses: 2 (hard coded)" << endl;
        userChoice=2;
    }
    switch (userChoice) {
        case 1:
            cout << "Saving game ..." << endl;
            break;
        case 2:
            cout << "Making move .. " << endl;
            p->playRound(this->deck);
            break;
        case 3:
            cout << "Here's some advice: " << endl;
            break;
        case 4:
            cout << "Thank you for playing. Exiting." << endl;
            //p->setOut(true);
            break;
        default:
            cout << "You shouldn't see this." << endl;
            break;
    }
    return 0;
}


void Round::progressRound(){
    int totalPlayers=this->getTotalPlayers();
    do{
        cout << "\tTurn is " << this->getTurn() << endl;
        this->giveRoundStatus();
        this->returnChoice(ourPlayers[this->getTurn() % totalPlayers]);
        this->setTurn();
        cout << "Deck is: " << endl;
        this->deck->printDecks();
        // adding in a dummy value here to test player rotation
    //}while(!(ourPlayers[this->getTurn() % totalPlayers+1]->getIfOut()));
    }while(this->getTurn()<6);
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
