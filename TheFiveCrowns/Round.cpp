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
    // set default round number
    this->setRoundNumber(1);
    // create the deck with the default round number
    this->deck = new Deck(this->getRoundNumber());
}

Round::~Round(){
    // debug print once round destroyed
    cout << "\t\tRound ended." << endl;
}

Round::Round(HumanPlayer *h, ComputerPlayer *c){
    // set round number to 1 if none specified
    this->setRoundNumber(1);
    // create the deck with this round number
    this->deck = new Deck(this->getRoundNumber());
    // create player objects
    this->setupPlayers(h,c);
    //this->progressRound();
}

Round::Round(HumanPlayer *h, ComputerPlayer *c, int round){
    // set round number to round specified
    this->setRoundNumber(round);
    // create deck with that round
    this->deck = new Deck(this->getRoundNumber());
    // set up player objects
    this->setupPlayers(h,c);
    //this->progressRound();
}

Round::Round(HumanPlayer *h, ComputerPlayer *c, Deck *roundDeck, int round){
    // set round number to round specified
    this->setRoundNumber(round);
    // move deck to the round
    this->deck = roundDeck;
    // set up player objects
    this->setupPlayers(h,c);
}


void Round::setupPlayers(HumanPlayer *h, ComputerPlayer *c){
    // push back players to vector, for future shuffling
    this->ourPlayers.push_back(h);
    this->ourPlayers.push_back(c);
}

int Round::getRoundNumber(){
    // return round number
    return roundNumber;
}

int Round::getTurn(){
    // return whose round it is next
    return nextTurn;
}

int Round::getTotalPlayers(){
    // calculate the total number of players in the round
    return (int)this->ourPlayers.size();
}

Deck Round::getDeck(){
    // return the round's deck
    return *deck;
}

void Round::setRoundNumber(int newNumber){
    // sets the round number
    this->roundNumber=newNumber;
    return;
}
void Round::setTurn(){
    // increments the turn to progress the round
    this->nextTurn++;
    return;
}
void Round::setTurn(int nextUp){
    // sets the turn to decide who goes next
    this->nextTurn=nextUp;
    return;
}

void Round::giveComputerStatus(std::vector<Player*> players){
    // iterate through the player vector
    for(auto &i: players){
        // if computer, print computer info
        if(!(i->getHumanity())){
            cout << "Computer:" << endl
            << "\tScore: " << players[1]->getPoints() << endl
            << "\tHand: " << endl;
            this->deck->getComputerDeck();
            cout << endl;
        }
    }
    return;
    
}
void Round::giveHumanStatus(std::vector<Player*> players){
    // iterate through the vector
    for(auto &i: players){
        // if human, print human player info
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

void Round::givePlayerStatus(std::vector<Player*> players){
    // iterate through the vector of players
    for(auto &i: players){
        // if human, print human player info
        if(i->getHumanity()){
            cout << "Human:" << endl
            << "\tScore: " << i->getPoints() << endl
            << "\tHand: ";
            this->deck->getHumanDeck();
            this->deck->printTheDeck(this->deck->getHumanDeck());
            cout << endl;
        }
        // if computer, print computer player info
        else{
            cout << "Computer:" << endl
            << "\tScore: " << i->getPoints() << endl
            << "\tHand: ";
            this->deck->printTheDeck(this->deck->getComputerDeck());
            cout << endl;
        }
    }
    return;
    
}

void Round::getRoundStatus(){
    // display the round number
    cout << "Round: " << this->getRoundNumber() << endl
        << endl;
    // display the player stats for the round
    this->givePlayerStatus(this->ourPlayers);
    // print the draw and discard piles
    this->deck->printDecks();
    cout << endl;
    return;
}

int Round::giveOptions(Player *p){
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
    
    return userChoice;
}



void Round::startRound(){
    
//    int answer = 0;
    int totalPlayers=this->getTotalPlayers();
    int ourTurn=this->getTurn();
    
    do{
        this->getRoundStatus();
        // begin the round progression, one player at a time
        progressRound(this->ourPlayers[ourTurn%totalPlayers]);
        ourTurn++;
        
        // while the NEXT player is still not out, keep going
        // this will cause the game to loop through all players once after
        // the first player goes out
    }while(!(this->ourPlayers[ourTurn%totalPlayers]->getIfOut()));
    cout << "Round is over. Would you like to progress?" << endl;
    return;
}

void Round::progressRound(Player *p){
    switch (giveOptions(p)) {
        case 1:
            p->saveGame();
            break;
        case 2:
            p->playRound(this->deck);
            break;
        case 3:
            p->examineOptions();
            break;
        case 4:
            p->setOut(true);
            break;
        default:
            cout << "You shouldn't see this." << endl;
            break;
    }
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
