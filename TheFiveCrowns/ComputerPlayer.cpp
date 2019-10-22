/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/1/2019                                            *
 ***************************************************************
 */

#include "ComputerPlayer.h"
#include <iostream>
using namespace std;

ComputerPlayer::ComputerPlayer(){
    //cout << "I am here. I am computer." << endl;
    this->setHumanity(false);
}

void ComputerPlayer::sayIfHuman(){
    if(this->getHumanity()){
        cout <<"I'm a human!" << endl;
    }
    else{
        cout <<"I'm a computer!" << endl;
    }
}

void ComputerPlayer::drawCard(Deck *deck){
    return;
}
void ComputerPlayer::discardCard(Deck *deck){
    return;
}

void ComputerPlayer::playRound(Deck *deck){
    int chosenCard=0;
    cout << "Computer playing round." << endl;
    // determine where to draw from
    if(this->examineOptions(deck,'t')==1){
        deck->transferFromDiscard(deck->getComputerDeck());
    }
    else{
        deck->transferFromDraw(deck->getComputerDeck());
    }
    // choose card to discard
    chosenCard=this->examineOptions(deck,'g');
    cout << "Discarding: " << deck->getComputerDeck()[chosenCard]->getFace() << deck->getComputerDeck()[chosenCard]->getSuite() << endl;
    
    // transfer appropriate card to discard pile
    deck->transferCard(deck->getComputerDeck(), chosenCard, deck->getDiscardPile());
    
    // display hand
    cout << "New computer hand: ";
    deck->printTheDeck(deck->getComputerDeck());
    cout << endl;
    // determine if computer is out
    if(deck->checkIfOut(deck->getComputerDeck())){
        cout << "You're going out!" << endl;
        this->setOut(true);
    }
    return;
}

int ComputerPlayer::examineOptions(Deck *deck, char choice){
    switch (choice) {
        case 'a':
            // generic advice - shouldn't ever be used, but hey...
            cout << "Computers don't need advice, so here's some for you:"
            <<"\tPrepare for us to take over, human." << endl;
            break;
        case 't':
            //cout << "Checking which pile to take from ... " << endl;
            return 1;
        case 'g':
            //cout << "Checking which card to give away ... " << endl;
            return 1;
        case 'o':
            //cout << "Checking how close you are to going out ..." << endl;
        default:
            break;
    }
    
    return 1;
}

//bool ComputerPlayer::checkIfOut(std::vector<Card*> handToCheck){
//    return false;
//}

bool ComputerPlayer::confirmExit(){
    return true;
}
