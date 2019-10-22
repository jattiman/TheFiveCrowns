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

bool HumanPlayer::drawCard(Deck *deck){
    // variable to store user choice
    int userChoice=0;
    // give player option to draw card
    do{
        cout << "Where would you like to draw from?" << endl
        << "\t1. The draw pile" << endl
        << "\t2. The discard pile" << endl
        << "\t3. Ask for advice" << endl
        << "\t4. Nowhere. I want to go out!" << endl;
        // validate input and transfer the card appropriately
        userChoice=this->getValidInput(1,4);
        cout << endl;
        // transfer from the draw pile
        if(userChoice==1){
            // If there's an issue (shouldn't be)
            if(!deck->transferFromDraw(deck->getHumanDeck())){
                // notify user and reset their choice
                cout << "The draw pile is empty. Try again." << endl;
                userChoice=0;
            }
        }
        // transfer from the discard pile
        else if(userChoice==2){
            // if there's an issue (shouldn't be)
            if(!(deck->transferFromDiscard(deck->getHumanDeck()))){
                // notify the user and reset their choice
                cout << "The discard pile is empty. Try again." << endl;
                userChoice=0;
            }
        }
        // if they want advice, instead
        else if(userChoice==3){
            // get advice, based on where to transfer
            cout << "Here's some advice." << endl;
            this->examineOptions(deck,'t');
        }
        // if they think they can go out
        else if(userChoice==4){
            if(this->requestToGoOut(deck)){
                return true;
            }
        }
        else{
            cout << "Please choose again." << endl;
        }
    } while(userChoice < 1 || userChoice > 2);
    return false;
}

int HumanPlayer::getValidInput(int minNum, int maxNum){
    int userInput;
    while(!(cin >> userInput) || userInput < minNum || userInput > maxNum){
        cin.clear();
        cin.ignore(500,'\n');
        cout << "Please select a valid option." << endl;
    }
    return userInput;
}

void HumanPlayer::discardCard(Deck *deck){
    // store user choice
    int userChoice=0;
    // prompt player
    do{
        cout << "What would you like to do now?" << endl
        << "\t1. Discard a card" << endl
        << "\t2. Ask for advice" << endl;
        userChoice=this->getValidInput(1,2);
        // if no advice needed
        if(userChoice==1){
            // skip to discard action
        }
        // if advice requested
        else if(userChoice==2){
            // give advice on which pile to give their card
            this->examineOptions(deck,'g');
            userChoice=0;
        }
        // extra input validation
        else{
            cout << "Please enter a valid option." << endl;
        }
    }while(userChoice < 1 || userChoice > 2);
    // reset user choice for next question
    userChoice=0;
    
    do{
        // prompt user to choose a card to discard
        cout << "Enter the card you want to discard:" << endl;
        // display their deck
        deck->printTheDeck(deck->getHumanDeck());
        // validate input against funny business
        userChoice=this->getValidInput(1, (int)(deck->getHumanDeck().size()));
        
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
    // prompt player where to draw their card
    if(this->drawCard(deck)){
        return;
    }
    // prompt player where to discard their card
    this->discardCard(deck);
    // check hand to see if they're out.
    if(deck->checkIfOut(deck->getHumanDeck())){
        cout << "You're going out!" << endl;
        this->setOut(true);
    }
    return;
}

bool HumanPlayer::requestToGoOut(Deck *deck){
    if(deck->checkIfOut(deck->getHumanDeck())){
        cout << "You can go out" << endl;
        this->setOut(true);
        return true;
    }
    else{
        cout << "You can't go out." << endl;
    }
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

bool HumanPlayer::confirmExit(){
    char quitStatus;
    do{
        cout << "Are you sure you want to quit? Progress will be lost. (Y/N)"
        << endl;
        cin >> quitStatus;
        quitStatus=toupper(quitStatus);
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
