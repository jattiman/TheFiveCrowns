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
