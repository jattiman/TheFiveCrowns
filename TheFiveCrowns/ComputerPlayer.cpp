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

bool ComputerPlayer::drawCard(Deck *deck){
    return false;
}

void ComputerPlayer::discardCard(Deck *deck){
    return;
}

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received:
********************************************************************* */
void ComputerPlayer::playRound(Deck *deck){
    // for holding future card choices
    int chosenCard=0;
    
    // announce that the computer has started round
    cout << "The computer is playing its round." << endl;
    
    // if round has just started, check if out
    if(deck->getDiscardPile().size()<3){
        cout << "Checking computer hand..." << endl;
        if(deck->checkIfOut(deck->getComputerDeck())){
            cout << "Computer is going out!" << endl << endl;
            this->setOut(true);
            return;
        }
    }
    
    // if not out, determine where to draw from
    if(this->examineOptions(deck,'t')==1){
        deck->transferFromDiscard(deck->getComputerDeck());
    }
    else{
        deck->transferFromDraw(deck->getComputerDeck());
    }
    int size=(int)deck->getComputerDeck().size()-1;
    cout << "Computer acquired: " << deck->getComputerDeck()[size]->getCardString()
    << endl;
    
    // choose card to discard
    chosenCard=this->examineOptions(deck,'g');
    //cout << "Discarding: " << deck->getComputerDeck()[chosenCard]->getFace() << deck->getComputerDeck()[chosenCard]->getSuite() << endl;
    
    // transfer appropriate card to discard pile
    deck->transferCard(deck->getComputerDeck(), chosenCard, deck->getDiscardPile());
    
    // display hand
    cout << "New computer hand: ";
    deck->printTheDeck(deck->getComputerDeck());
    cout << endl;
    
    // determine if computer is out with new hand
    cout << "Checking new computer hand..." << endl;
    if(deck->checkIfOut(deck->getComputerDeck())){
        cout << "Computer is going out!" << endl << endl;
        this->setOut(true);
    }
    return;
}

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received:
********************************************************************* */
bool ComputerPlayer::requestToGoOut(Deck *deck){
    return false;
}

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received:
********************************************************************* */
int ComputerPlayer::examineOptions(Deck *deck, char choice){
    int cardChoice=0;
    vector<Card*> tempDeck;
    tempDeck=deck->getComputerDeck();

    switch (choice) {
        case 'a':
            // generic advice - shouldn't ever be used, but hey...
            cout << "Computers don't need advice, so here's some for you:"
            <<"\tPrepare for us to take over, human." << endl;
            break;
        case 't':
            //cout << "Checking which pile to take from ... " << endl;
            cout << "Computer is taking from the discard pile, because it likes what it sees."
            << endl;
            return 1;
        case 'g':
            cout << "Computer is discarding ";
            if(deck->tallyRemainingCardPoints(tempDeck)>0){
                cardChoice=deck->findCard(deck->getComputerDeck(),tempDeck[0]->getCardString());
                cout << deck->getComputerDeck()[cardChoice]->getCardString()
                << " because it doesn't think it's good for books or runs." << endl;
                return cardChoice;
            }
            else{
                cout << deck->getComputerDeck()[0]->getCardString()
                << " because it feels like it doesn't have any other choice." << endl;
                return 0;
            }
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
