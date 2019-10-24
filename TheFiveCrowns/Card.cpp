/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/22/2019                                            *
 ***************************************************************
 */

#include "Card.h"
#include <iostream>

using namespace std;

/* *********************************************************************
Function Name:Card
Purpose: none. This shouldn't ever be used
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
 Does nothing. For debugging.
Assistance Received: None.
********************************************************************* */
Card::Card(){
    //cout << "We made a card! WOW!" << endl;
}

/* *********************************************************************
Function Name:Card
Purpose: create and assign card values based on chars and round input
Parameters:
 char face: character for card face
 char suite: character for the card suit
 int theRound: holds round number
Return Value:
 none
Local Variables:
 none
Algorithm:
 set the following for each card, based on input: suit, face
 set the round number
 based on round number, set the wild status of the card through checkForWild function
 set the card string (to make this more versatile - input could be 2 chars or a string)
Assistance Received: none
********************************************************************* */
Card::Card(char face, char suite, int theRound){
    this->setSuite(suite);
    this->setFace(face);
    this->setRoundNumber(theRound);
    this->checkForWild();
    this->setCardString();
}

/* *********************************************************************
Function Name:Card
Purpose: create and assign card values based on string and round input
Parameters:
 string cardString: holds the string representing the card
 int theRound: holds round number
Return Value:
 none
Local Variables:
 none
Algorithm:
 set the following for each card, based on input: suit, face
 set the round number
 based on round number, set the wild status of the card through checkForWild function
 set the card string (to make this more versatile - input could be 2 chars or a string). Even though this is input with the user string, we ensure that the cardString is valid based on the chars representing face and suit
Assistance Received: none
********************************************************************* */
Card::Card(string cardString, int theRound){
    // need to add error checking to this
    this->setSuite(cardString[1]);
    this->setFace(cardString[0]);
    this->setRoundNumber(theRound);
    this->checkForWild();
    this->setCardString();
}

/* *********************************************************************
Function Name:getFace
Purpose: returns face of the card
Parameters: none
Return Value: char face (card face character)
Local Variables:
 none
Algorithm:
 None. Returns the face. It's a getter, for encapsulation.
Assistance Received: none
********************************************************************* */
char Card::getFace(){
    return face;
}

/* *********************************************************************
Function Name:getSuite
Purpose: returns suit of the card
Parameters: none
Return Value: char suite (card suit character)
Local Variables:
 none
Algorithm:
 None. Returns the suit. It's a getter, for encapsulation.
Assistance Received: none
********************************************************************* */
char Card::getSuite(){
    return suite;
}

/* *********************************************************************
Function Name:getCardString
Purpose: returns string representing the card
Parameters: none
Return Value: string cardString (represents card in string format)
Local Variables:
 none
Algorithm:
 None. Returns the card string. It's a getter, for encapsulation.
Assistance Received: none
********************************************************************* */
string Card::getCardString(){
    return cardString;
}

/* *********************************************************************
Function Name:getPointValue
Purpose: get the cards point value
Parameters: none
Return Value: int for point value
Local Variables: none
Algorithm:
 Returns the card's point value. It's a getter, for encapsulation
Assistance Received: none
********************************************************************* */
int Card::getPointValue(){
    return pointValue;
}

/* *********************************************************************
Function Name:getWildStatus
Purpose: gets the card wild status
Parameters: none
Return Value: bool isWild (represents wild status)
Local Variables: none
Algorithm:
 Returns wild status. It's a getter, for encapsulation.
Assistance Received:
********************************************************************* */
bool Card::getWildStatus(){
    return isWild;
}

/* *********************************************************************
Function Name:getRoundNumber
Purpose: returns the current round number for the card (helps with wild status)
Parameters: none
Return Value: int roundNumber
Local Variables: none
Algorithm:
 Returns the integer for the round number. Getter for encapsulation.
Assistance Received: None.
********************************************************************* */
int Card::getRoundNumber(){
    return roundNumber;
}

/* *********************************************************************
Function Name:getRunStatus
Purpose: returns if the card is in a run.
 Note: this was not ultimately used, but will be needed for future expansion of the game.
Parameters: none
Return Value: bool representing if the card is in a run
Local Variables: none
Algorithm:
 Returns status for whether card is in a run
Assistance Received: none
********************************************************************* */
bool Card::getRunStatus(){
    return isInRun;
}

/* *********************************************************************
Function Name:getBookStatus
Purpose: returns if the card is in a book.
 Note: this was not ultimately used, but will be needed for future expansion of the game.
Parameters: none
Return Value: bool representing if the card is in a book
Local Variables: none
Algorithm:
 Returns status for whether card is in a book. Getter for encapsulation.
Assistance Received: none
********************************************************************* */
bool Card::getBookStatus(){
    return isInBook;
}

/* *********************************************************************
Function Name:setRoundNumber
Purpose: sets the round number for the card
Parameters:
 int newRoundNumber: round number integer
Return Value: none
Local Variables: none
Algorithm:
 Sets the round number for the card to whatever is defined by the game. Needed for wild status determination.
Assistance Received: none
********************************************************************* */
void Card::setRoundNumber(int newRoundNumber){
    this->roundNumber=newRoundNumber;
    return;
}

/* *********************************************************************
Function Name:setFace
Purpose: set the card face
Parameters:
 char newFace: character holding face of card
Return Value:
 none
Local Variables:
 none
Algorithm:
 set the face of the card
 based on the face, calls function to set the point value
Assistance Received: none
********************************************************************* */
void Card::setFace(char newFace){
    this->face=newFace;
    this->setPointValue();
    return;
}

/* *********************************************************************
Function Name:setSuite
Purpose: sets the suit of the card
Parameters: char newSuite: the new suit variable to be assigned
Return Value: none
Local Variables: none
Algorithm:
 sets the suit of the card based on input
Assistance Received: none
********************************************************************* */
void Card::setSuite(char newSuite){
    this->suite=newSuite;
    return;
}

/* *********************************************************************
Function Name:setCardString
Purpose: sets the card's string value representation
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
 append the card face char to the card string (originally empty)
 append the card suit char to the card string
 return
Assistance Received:
********************************************************************* */
void Card::setCardString(){
    this->cardString+=this->getFace();
    this->cardString+=this->getSuite();
    return;
}

/* *********************************************************************
Function Name:setPointValue
Purpose: set the card's point value
Parameters:
 int newPoints: the new points for the card
Return Value: none
Local Variables: none
Algorithm: sets the point value of the card based on new points input. Useful for future expansion of the game.
Assistance Received: none
********************************************************************* */
void Card::setPointValue(int newPoints){
    //cout << "Setting point value to " << newPoints << endl;
    this->pointValue=newPoints;
    return;
}

/* *********************************************************************
Function Name:setPointValue
Purpose: determines the point value of the card based on card face/wild status
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
 Get the card's face
 Assign point value based on face, except for 'J' faces
 If 'J' face: determine if it's a joker by checking suite, and assign points accordingly. Then, set wild status to true.
 If unidentified card comes through (issue), set points to 0. This would be used for future error checking.
Assistance Received: None
********************************************************************* */
void Card::setPointValue(){
    switch (this->getFace()) {
        case '3':
            this->setPointValue(3);
            break;
        case '4':
            this->setPointValue(4);
            break;
        case '5':
            this->setPointValue(5);
            break;
        case '6':
            this->setPointValue(6);
            break;
        case '7':
            this->setPointValue(7);
            break;
        case '8':
            this->setPointValue(8);
            break;
        case '9':
            this->setPointValue(9);
            break;
        case 'X':
            this->setPointValue(10);
            break;
        case 'J':
            if(this->getSuite()=='1' || this->getSuite()=='2' || this->getSuite()=='3' || this->getSuite()=='4'){
                this->setPointValue(50);
                this->setWildStatus(true);
            }
            else{
                this->setPointValue(11);
            }
            break;
        case 'Q':
            this->setPointValue(12);
            break;
        case 'K':
            this->setPointValue(13);
            break;
        default:
            cout << "Point Value ut-oh!";
            this->setPointValue(0);
            break;
    }
}

/* *********************************************************************
Function Name:setWildStatus
Purpose: sets the wild status of the card
Parameters: bool newStatus: the new wild status
Return Value: none
Local Variables: none
Algorithm:
 Sets the wild status based on the input given
Assistance Received: none
********************************************************************* */
void Card::setWildStatus(bool newStatus){
    this->isWild=newStatus;
    return;
}

/* *********************************************************************
Function Name:setBookStatus
Purpose: sets if the card is in a book.
 Note: this wasn't used, ultimately, but is needed for future expansion of the card.
Parameters:
 bool newStatus: whether it's in a book or not
Return Value: none
Local Variables: none
Algorithm:
 Set the status for whether or not the card is in a book
Assistance Received: none
********************************************************************* */
void Card::setBookStatus(bool newStatus){
    this->isInBook=newStatus;
    return;
}

/* *********************************************************************
Function Name:setRunStatus
Purpose: set whether the card is in a run based on input
Parameters:
 bool newStatus: holds if card is in run
Return Value: none
Local Variables: none
Algorithm:
 Sets the status for whether or not the card is in a run.
Assistance Received: none.
********************************************************************* */
void Card::setRunStatus(bool newStatus){
    this->isInRun=newStatus;
    return;
}

/* *********************************************************************
Function Name:checkForWild
Purpose: to assign points based on wild status, based on round
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
 If the current point value of the card is 50, it's a joker. Leave it alone.
 Otherwise, if the CURRENT point value of the card equals the roundNumber+2, you know it's a wild card. Set wild status to true, and set the point value to 20.
Assistance Received: none
********************************************************************* */
void Card::checkForWild(){
    // if card is Joker, wild status will have already
    // been set to true. Change nothing and return.
    if(this->getPointValue()==50){
        return;
    }
    // if card Face is the same as the round, set wild
    // status to true, points to 20, and return
    if(this->getPointValue()==(this->roundNumber+2)){
        this->setWildStatus(true);
        this->setPointValue(20);
        return;
    }

    return;
}
