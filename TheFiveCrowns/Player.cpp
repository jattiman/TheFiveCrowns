/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/22/2019                                            *
 ***************************************************************
 */
#include "Player.h"
// iostream and namespace are for debugging output
#include <iostream>
using namespace std;

/* *********************************************************************
Function Name:Player
Purpose: constructor. Empty.
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
Player::Player(){
    
}

/* *********************************************************************
Function Name:Player
Purpose: constructor. Sets player number (for future iterations of the game)
Parameters:
 int num: sets player number (future evolution of game)
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none
********************************************************************* */
Player::Player(int num){
    setPlayerNumber(num);
}

/* *********************************************************************
Function Name:getPoints
Purpose: return player points
Parameters: none
Return Value: int holding player points
Local Variables: none
Algorithm:
 Getter that returns player points.
Assistance Received: none
********************************************************************* */
int Player::getPoints(){
    return this->playerPoints;
}

/* *********************************************************************
Function Name:getTurn
Purpose: return player turn
Parameters: none
Return Value: bool saying if it's the player turn
Local Variables: none
Algorithm:
 Getter that returns if player is up
Assistance Received: none
********************************************************************* */
bool Player::getTurn(){
    return this->isTurn;
}

/* *********************************************************************
Function Name:getPlayerNumber
Purpose: returns player number
Parameters: none
Return Value: int containing player number
Local Variables: none
Algorithm:
 Return player number. This is a getter.
Assistance Received: none
********************************************************************* */
int Player::getPlayerNumber(){
    return this->playerNumber;
}

/* *********************************************************************
Function Name: getHumanity
Purpose: return if the player is a human or computer
Parameters: none
Return Value: bool reflecting if human
Local Variables: none
Algorithm:
 Return if the player is a human or not.
Assistance Received: none
********************************************************************* */
bool Player::getHumanity(){
    return this->isHuman;
}

/* *********************************************************************
Function Name:getIfOut
Purpose: return if the player is out
Parameters: none
Return Value: bool showing if the player is out
Local Variables: none
Algorithm:
 Returns the bool reflecting player out status.
Assistance Received: none
********************************************************************* */
bool Player::getIfOut(){
    return this->isOut;
}

/* *********************************************************************
Function Name:setHumanity
Purpose: sets player humanity
Parameters:
 bool isPlayerHuman: holds if player is human
Return Value: none
Local Variables: none
Algorithm:
 Sets player humanity variable.
Assistance Received: none
********************************************************************* */
void Player::setHumanity(bool isPlayerHuman){
    this->isHuman=isPlayerHuman;
    return;
}

/* *********************************************************************
Function Name:setTotalPoints
Purpose: set the player's TOTAL points value
Parameters:
 int totalPoints: the new total points for the player
Return Value: none
Local Variables: none
Algorithm:
 Set player total points based on input.
Assistance Received: none
********************************************************************* */
void Player::setTotalPoints(int totalPoints){
    this->playerPoints=totalPoints;
    return;
}

/* *********************************************************************
Function Name:addPoints
Purpose: Adds to current player points (based on new round points, typically).
Parameters: None
Return Value: none
Local Variables: none
Algorithm:
 Add input points to current points.
Assistance Received: None.
********************************************************************* */
void Player::addPoints(int newPoints){
    this->playerPoints+=newPoints;
    return;
}

/* *********************************************************************
Function Name: setTurn
Purpose: sets if the player is next
Parameters:
 bool isNext: true or false based on if the player is up next.
Return Value: none
Local Variables: none
Algorithm:
 Sets isTurn based on input variable.
Assistance Received: none
********************************************************************* */
void Player::setTurn(bool isNext){
    this->isTurn=isNext;
    return;
}

/* *********************************************************************
Function Name:setPlayerNumber
Purpose: set the player number (future version of the game)
Parameters:
 int num: holds new player number
Return Value: none
Local Variables: none
Algorithm:
 Sets the player number. This will be used to uniquely identify the player in future versions of the game, with more players.
Assistance Received:
********************************************************************* */
void Player::setPlayerNumber(int num){
    this->playerNumber=num;
    return;
}

/* *********************************************************************
Function Name:setOut
Purpose: sets of the player is out or not
Parameters:
 bool areYouOut: new out status for player
Return Value: none
Local Variables: none
Algorithm:
 Sets new out status based on input.
Assistance Received: none
********************************************************************* */
void Player::setOut(bool areYouOut){
    this->isOut=areYouOut;
}

/* *********************************************************************
Function Name:deletePoints
Purpose: delete ALL of the player's points
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
 Set player total points to 0.
Assistance Received: none
********************************************************************* */
void Player::deletePoints(){
    this->playerPoints=0;
}

