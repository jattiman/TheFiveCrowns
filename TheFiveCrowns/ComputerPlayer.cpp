/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/22/2019                                            *
 ***************************************************************
 */

#include "ComputerPlayer.h"
#include <iostream>
using namespace std;

/* *********************************************************************
Function Name:ComputerPlayer
Purpose: default constructor
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
 Sets humanity to false
Assistance Received: none
********************************************************************* */
ComputerPlayer::ComputerPlayer(){
    //cout << "I am here. I am computer." << endl;
    this->setHumanity(false);
}

/* *********************************************************************
Function Name:sayIfHuman
Purpose: will output to screen if it's human.
 Note: this ultimately wasn't used, and is mainly for debugging.
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
 If human, say human. If computer, output that you're a computer.
Assistance Received: none.
********************************************************************* */
void ComputerPlayer::sayIfHuman(){
    if(this->getHumanity()){
        cout <<"I'm a human!" << endl;
    }
    else{
        cout <<"I'm a computer!" << endl;
    }
}

/* *********************************************************************
Function Name:drawCard
Purpose: none
Parameters: Deck *deck: a copy of the deck
Return Value: true or false
Local Variables: none
Algorithm:
 This function was removed once I decided to make the deck management all occur within the deck class. This function is being held in place in case it's needed in the future.
Assistance Received: none
********************************************************************* */
bool ComputerPlayer::drawCard(Deck *deck){
    return false;
}

/* *********************************************************************
Function Name:discardCard
Purpose: none
Parameters: Deck *deck: a copy of the deck
Return Value: true or false
Local Variables: none
Algorithm:
 This function was removed once I decided to make the deck management all occur within the deck class. This function is being held in place in case it's needed in the future.
Assistance Received: none
********************************************************************* */
void ComputerPlayer::discardCard(Deck *deck){
    return;
}

/* *********************************************************************
Function Name:playRound
Purpose: to have the computer play the round
Parameters: Deck *deck: the deck passed in
Return Value: none
Local Variables:
 int chosenCard: the card the player chooses (index value)
 
Algorithm:
 Display that the computer is playing its round.
 Check computer hand to see if it can go out.
 If the computer can't go out:
 Determine where to draw from (based on examineOptions function result)
 Draw the card.
 Announce what was drawn.
 Choose a card to discard (based on examineOptions function result)
 Announce new hand.
 Check if computer is able to go out.
 
Assistance Received: none
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
Function Name:requestToGoOut
Purpose: none
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none. This function was discontinued, but being held onto for future implementation/program evolution.
Assistance Received: none
********************************************************************* */
bool ComputerPlayer::requestToGoOut(Deck *deck){
    return false;
}

/* *********************************************************************
Function Name:examineOptions
Purpose: To help the computer determine how it will move. Needs to be greatly updated, as the computer is currently not the brightest.
Parameters:
 Deck *deck, the deck being manipulated
 char choice, the choice used to indicate what needs to be examine
Return Value: integer representing choice decision
Local Variables:
 int cardChoice: the card being chosen by the computer, when needed
 vector<Card*> tempDeck: the temp deck of the vector, which can be destroyed/manipulated as needed
Algorithm:
 Copy the deck into a temp deck
 Based on choice input, help the computer determine what it will do
 If 'a' (generic input) output that no advice is needed. This is a check.
 If 't' (which pile to Take from) choose the discard pile by default. This will be expanded on later.
 If 'g' (which pile to Give to), use the temp deck to determine what cards aren't useful, and pick from these cards
 Right now, this determined the card choice based on the deck find feature, after discovering the card in the deck
Assistance Received: none
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

/* *********************************************************************
Function Name:confirmExit
Purpose: none
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none. This function was discontinued, but being held onto for future implementation/program evolution.
Assistance Received: none
********************************************************************* */
bool ComputerPlayer::confirmExit(){
    return true;
}
