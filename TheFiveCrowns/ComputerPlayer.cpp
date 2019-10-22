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
    cout << "Computer playing round." << endl;
    // determine where to draw from
    
    // determine where to discard to
    
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
            cout << "Checking which pile to take from ... " << endl;
            break;
        case 'g':
            cout << "Checking which card to give away ... " << endl;
            break;
        case 'o':
            cout << "Checking how close you are to going out ..." << endl;
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
