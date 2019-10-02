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
    cout << "What do you want to do?" << endl;
    do{
        cout << "Where would you like to draw from?" << endl
        << "\t1. The draw pile" << endl
        << "\t2. The discard pile" << endl;
        cin >> userChoice;
    } while(userChoice < 1 || userChoice > 2);
    if(userChoice==1){
        deck->transferCard(deck->getDrawPile(), deck->getHumanDeck());
    }
    else{
        deck->transferFromDiscard(deck->getHumanDeck());
    }
    
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

