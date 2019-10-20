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
        << "\t2. The discard pile" << endl
        << "\t3. Ask for advice" << endl;
        cin >> userChoice;
        // transfer the card appropriately
        if(userChoice==1){
            //deck->transferCard(deck->getDrawPile(), deck->getHumanDeck());
            if(!deck->transferFromDraw(deck->getHumanDeck())){
                cout << "The draw pile is empty. Try again." << endl;
                userChoice=0;
            }
        }
        else if(userChoice==2){
            // need to check to ensure piles aren't empty
            if(!(deck->transferFromDiscard(deck->getHumanDeck()))){
                cout << "The discard pile is empty. Try again." << endl;
                userChoice=0;
            }
        }
        else if(userChoice==3){
            cout << "Here's some advice." << endl;
        }
        else{
            cout << "Please enter a valid option." << endl;
        }
    } while(userChoice < 1 || userChoice > 2);
    userChoice=0;
    do{
        // need to prompt differently for advice/discarding
        cout << "Enter the card you want to discard, or press 'A' for advice" << endl;
        deck->printTheDeck(deck->getHumanDeck());
        cin>>userChoice;
//        cout << "choice: " << userChoice << endl << "deck size: " << deck->getHumanDeck().size() << endl;
        
    }while(userChoice < 0 || userChoice > deck->getHumanDeck().size());
    // translate user choice to vector position
    userChoice--;
    // transfer appropriate card to discard pile
    cout << "Discarding: " << deck->getHumanDeck()[userChoice]->getFace() << deck->getHumanDeck()[userChoice]->getSuite() << endl;
    
    deck->transferCard(deck->getHumanDeck(), userChoice, deck->getDiscardPile());
//    cout << "New player hand: ";
//    deck->printTheDeck(deck->getHumanDeck());
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

bool HumanPlayer::checkIfOut(std::vector<Card*> handToCheck){
    return false;
}

bool HumanPlayer::confirmExit(){
    char quitStatus;
    do{
        cout << "Are you sure you want to quit? Progress will be lost. (Y/N)"
        << endl;
        cin >> quitStatus;
        quitStatus=toupper(quitStatus);
        cout << "\t\tQuit status is: " << quitStatus << endl;
    }while(quitStatus != 'Y' && quitStatus !='N');
    if(quitStatus=='Y'){
        return true;
    }
    else{
        return false;
    }
}
