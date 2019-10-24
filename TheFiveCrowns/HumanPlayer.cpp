/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/22/2019                                            *
 ***************************************************************
 */

#include "HumanPlayer.h"
#include <iostream>
using namespace std;

/* *********************************************************************
Function Name:HumanPlayer
Purpose: constructor
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
 Sets humanity to true.
Assistance Received: none
********************************************************************* */
HumanPlayer::HumanPlayer(){
    //cout << "I'm here. I'm human." << endl;
    this->setHumanity(true);
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
void HumanPlayer::sayIfHuman(){
    if(this->getHumanity()){
        cout <<"I'm a human!" << endl;
    }
    else{
        cout <<"I'm a computer!" << endl;
    }
}

/* *********************************************************************
Function Name:drawCard
Purpose: used to determine where to draw a card from
Parameters:
 Deck *deck: the deck passed in
Return Value: true or false
Local Variables:
 int userChoice: holds the user's choice for prompts
 
Algorithm:
 Display prompt and get input about where to draw from
 If draw pile, draw from the draw pile
 If discard pile, draw from discard pile
 If asking for advice, display advice based on examineOptions function
 Return
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name: getValidInput
Purpose: to confirm the user doesn't blow up my program with invalid input
Parameters:
 ints minNum and maxNum, for optional checks on integer input (default values passed if needed)
 Note: I had some issues with cin.ignore() and cin.clear() sometimes causing the user to have to press enter twice. I think it might be due to not flushing the input stream properly somewhere else in the program.
Return Value:
 integer of the user input choice
Local Variables:
 userInput: int holding the user choice
Algorithm:
 while the user input fails, or doesn't fit within min/max boundaries, prompt the user to re-enter valid input
Assistance Received: A lot of research was done online to cin.fail() and other ways to handle invalid input that criss-crossed chars/strings/key commands when an int is needed, but no site in particular is to blame for the odd way I solved this.
********************************************************************* */
int HumanPlayer::getValidInput(int minNum, int maxNum){
    int userInput;
    while(!(cin >> userInput) || userInput < minNum || userInput > maxNum){
        cin.clear();
        cin.ignore(500,'\n');
        cout << "Please select a valid option." << endl;
    }
    return userInput;
}

/* *********************************************************************
Function Name:discardCard
Purpose: place a chosen card into the discard pile
Parameters: Deck *deck
Return Value: none
Local Variables:
 int userChoice: holds user choice
Algorithm:
 Display prompt to discard card or ask for advice
 If asking for advice, give advice based on examineOptions function
 If discarding a card:
 Display hand
 Prompt for discard choice
 Have user press enter to continue
Assistance Received: none
********************************************************************* */
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
    cout << endl
    <<"(Press enter to continue)"
    << endl;
    cin.ignore();
    cin.get();
    return;
}

/* *********************************************************************
Function Name:playRound
Purpose: human's play round function
Parameters:
 Deck *deck: deck passed in
Return Value: none
Local Variables: none
Algorithm:
 Call draw card function
 Call discard card function
 Call request to go out function
 Return
Assistance Received: none
********************************************************************* */
void HumanPlayer::playRound(Deck *deck){
    // prompt player where to draw their card
    if(this->drawCard(deck)){
        return;
    }
    // prompt player where to discard their card
    this->discardCard(deck);
    // check hand to see if they're out.
    this->requestToGoOut(deck);
    return;
}

/* *********************************************************************
Function Name:requestToGoOut
Purpose: Display if a human can go out
Parameters:
 Deck*deck: deck object passed in
Return Value: true or false
Local Variables: none
Algorithm:
 Call deck->checkIfOut to see if the player's hand can go out
 Display result to screen
 Set out status to true or false.
 Return based on out function
Assistance Received: none
********************************************************************* */
bool HumanPlayer::requestToGoOut(Deck *deck){
    if(deck->checkIfOut(deck->getHumanDeck())){
        cout << "You can go out! Congratulations! (Press enter 1 or 2 times)" << endl;
        this->setOut(true);
        cin.ignore();
        cin.get();
        return true;
    }
    else{
        cout << "You can't go out with this hand." << endl <<endl;
    }
    return false;
}


/* *********************************************************************
Function Name:examineOptions
Purpose: for player to get advice
Parameters:
 Deck *deck: the deck being passed in
 char choice: holds the section advice will be given for
Return Value: integer based on advice result
Local Variables:
 cardChoice: holds the card index that needs to be displayed on function return
 tempDeck: vector of cards that will be a temporary deck
Algorithm:
 Check choice variable.
 If 'a' or 't': output default answers, for now. This will be expanded on as the game developes.
 If 'g' (selecting where to give card), return recommendation based on the string of cards returned as not part of a book or run (based on deck functions)
 This nees to be heavily updated: the advice is not very smart with the current set of algorithms.
Assistance Received: none
********************************************************************* */
int HumanPlayer::examineOptions(Deck *deck, char choice){
    int cardChoice=0;
    vector<Card*> tempDeck;
    tempDeck=deck->getHumanDeck();
    switch (choice) {
        case 'a':
            cout << "Here's some advice: input an actual choice." << endl;
            break;
        case 't':
            cout << "Take from whichever pile you want, dude." << endl;
            break;
        case 'g':
            cout << "We recommend you give away ";
            if(deck->tallyRemainingCardPoints(tempDeck)>0){
                cardChoice=deck->findCard(deck->getHumanDeck(),tempDeck[0]->getCardString());
                cout << deck->getHumanDeck()[cardChoice]->getCardString()
                << " because it isn't a part of a book or a run." << endl;
                return cardChoice;
            }
            else{
                cout << "nothing, because everything is part of a book or run."
                << endl
                << "Choose whatever your heart tells you." << endl;
                return 1;
            }
            break;
        case 'o':
            cout << "Going out will be checked automatically." << endl
            << "You don't need advice on this. Stop being scared." << endl;
        default:
            break;
    }
    
    return 1;
}

/* *********************************************************************
Function Name:confirmExit
Purpose: To ensure a player quits on purpose.
Parameters: none
Return Value: true or false
Local Variables:
 char quitStatus: the character input from the player, if they are quitting
Algorithm:
 Prompt user if they want to quit.
 toUpper the user char
 Match it against Y or N
 If Y, they quit
 If N, they get to continue playing
 Note: further input validation needs to be added to this.
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name:testOutPut
Purpose: debug function - testing slicing when manipulating player parent/humanPlayer child
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
void HumanPlayer::testOutPut(){
    cout << "Testing output to check for slicing. See this? Good!" << endl;
    return;
}
