/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/1/2019                                            *
 ***************************************************************
 */

#include "HumanPlayer.h"
#include <iostream>
using namespace std;

HumanPlayer::HumanPlayer(){
    //cout << "I'm here. I'm human." << endl;
    this->setHumanity(true);
}

void HumanPlayer::sayIfHuman(){
    if(this->getHumanity()){
        cout <<"I'm a human!" << endl;
    }
    else{
        cout <<"I'm a computer!" << endl;
    }
}

void HumanPlayer::playRound(Deck *deck){
    int userChoice=0;
    // give player option to draw card
    // move this to a new function -------
    do{
        cout << "Where would you like to draw from?" << endl
        << "\t1. The draw pile" << endl
        << "\t2. The discard pile" << endl;
        cin >> userChoice;
    } while(userChoice < 1 || userChoice > 2);
    // transfer the card appropriately
    if(userChoice==1){
        deck->transferCard(deck->getDrawPile(), deck->getHumanDeck());
    }
    else{
        // need to check to ensure piles aren't empty
        deck->transferFromDiscard(deck->getHumanDeck());
    }
    // if player has wild card, ask them if they want to rename any
    // this->reviewWilds(), maybe?
    // ask player which card they would like to discard
    // this->choose discard
    return;
}

bool HumanPlayer::requestToGoOut(){
    return false;
}

void HumanPlayer::saveGame(){
    cout << "Saving game ... " << endl;
    return;
}

void HumanPlayer::examineOptions(){
    cout << "Here's some advice: " << endl;
}

