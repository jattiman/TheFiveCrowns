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

void HumanPlayer::drawCard(Deck *deck){
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
            // transfer a card from the draw pile
            if(!deck->transferFromDraw(deck->getHumanDeck())){
                cout << "The draw pile is empty. Try again." << endl;
                userChoice=0;
            }
        }
        else if(userChoice==2){
            // transfer from the discard pile
            if(!(deck->transferFromDiscard(deck->getHumanDeck()))){
                cout << "The discard pile is empty. Try again." << endl;
                userChoice=0;
            }
        }
        else if(userChoice==3){
            // get advice, based on player stage
            cout << "Here's some advice." << endl;
            this->examineOptions(deck,'t');
        }
        else{
            cout << "Please enter a valid option." << endl;
        }
    } while(userChoice < 1 || userChoice > 2);
    return;
}

void HumanPlayer::discardCard(Deck *deck){
    int userChoice=0;
    do{
        cout << "What would you like to do now?" << endl
        << "\t1. Discard a card" << endl
        << "\t2. Ask for advice" << endl;
        cin >> userChoice;
        if(userChoice==1){
            // skip to discard action
        }
        else if(userChoice==2){
            this->examineOptions(deck,'g');
            userChoice=0;
        }
        else{
            cout << "Please enter a valid option." << endl;
        }
    }while(userChoice < 1 || userChoice > 2);
    // reset user choice for next question
    userChoice=0;
    
    do{
        cout << "Enter the card you want to discard:" << endl;
        deck->printTheDeck(deck->getHumanDeck());
        cin>>userChoice;
    }while(userChoice < 1 || userChoice > (deck->getHumanDeck().size()));
    
    // translate user choice to vector position
    userChoice--;
    
    // display card being discarded
    cout << "Discarding: " << deck->getHumanDeck()[userChoice]->getFace() << deck->getHumanDeck()[userChoice]->getSuite() << endl;
    
    // transfer appropriate card to discard pile
    deck->transferCard(deck->getHumanDeck(), userChoice, deck->getDiscardPile());
    
    // display the new player hand
    cout << "New hand: ";
    deck->printTheDeck(deck->getHumanDeck());
    cin.ignore();
    cin.get();
    return;
}

void HumanPlayer::playRound(Deck *deck){
    this->drawCard(deck);
    
    this->discardCard(deck);
    cout << "\t\t\tReturned from discard." << endl;
    return;
}

bool HumanPlayer::requestToGoOut(){
    return false;
}

//void HumanPlayer::saveGame(){
//    cout << "Saving game ... " << endl;
//    return;
//}

int HumanPlayer::examineOptions(Deck *deck, char choice){
    switch (choice) {
        case 'a':
            cout << "Here's some advice: input an actual choice." << endl;
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
        //cout << "\t\tQuit status is: " << quitStatus << endl;
    }while(quitStatus != 'Y' && quitStatus !='N');
    if(quitStatus=='Y'){
        return true;
    }
    else{
        return false;
    }
}

void HumanPlayer::testOutPut(){
    cout << "Testing output to check for slicing. See this? Good!" << endl;
    return;
}
