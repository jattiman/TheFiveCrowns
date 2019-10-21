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
void ComputerPlayer::playRound(Deck *deck){
    cout << "Computer playing round." << endl;
    return;
}

bool ComputerPlayer::requestToGoOut(){
    return false;
}

//void ComputerPlayer::saveGame(){
//    cout << "Saving game ... " << endl;
//    return;
//}

int ComputerPlayer::examineOptions(Deck *deck, char choice){
    cout << "Computers don't need advice (place holder)" << endl;
    return 1;
}

//bool ComputerPlayer::checkIfOut(std::vector<Card*> handToCheck){
//    return false;
//}

bool ComputerPlayer::confirmExit(){
    return true;
}
