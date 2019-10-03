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
        // transfer the card appropriately
        if(userChoice==1){
            //deck->transferCard(deck->getDrawPile(), deck->getHumanDeck());
            if(!deck->transferFromDraw(deck->getHumanDeck())){
                cout << "The draw pile is empty. Try again." << endl;
                userChoice=0;
            }
        }
        else{
            // need to check to ensure piles aren't empty
            if(!(deck->transferFromDiscard(deck->getHumanDeck()))){
                cout << "The discard pile is empty. Try again." << endl;
                userChoice=0;
            }
        }
    } while(userChoice < 1 || userChoice > 2);
    userChoice=0;
    do{
        cout << "Pick a card to discard." << endl;
        deck->printTheDeck(deck->getHumanDeck());
        cin>>userChoice;
        cout << "choice: " << userChoice << endl << "deck size: " << deck->getHumanDeck().size() << endl;
        
    }while(userChoice < 0 || userChoice > deck->getHumanDeck().size());
    // translate user choice to vector position
    userChoice--;
    // transfer appropriate card to discard pile
    cout << "You picked the following card to discard: " << deck->getHumanDeck()[userChoice]->getFace() << deck->getHumanDeck()[userChoice]->getSuite() << endl;
    
    deck->transferCard(deck->getHumanDeck(), userChoice, deck->getDiscardPile());
    cout << "New player hand: ";
    deck->printTheDeck(deck->getHumanDeck());
    cin.ignore();
    cin.get();
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

