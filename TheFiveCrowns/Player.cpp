/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/1/2019                                            *
 ***************************************************************
 */
#include "Player.h"
// iostream and namespace are for debugging output
#include <iostream>
using namespace std;

Player::Player(){
    
}
Player::Player(int num){
    setPlayerNumber(num);
}
int Player::getPoints(){
    return this->playerPoints;
}
bool Player::getTurn(){
    return this->isTurn;
}
//Deck* Player::getDeck(){
//    return deck;
//}
int Player::getPlayerNumber(){
    return this->playerNumber;
}

bool Player::getHumanity(){
    return this->isHuman;
}

bool Player::getIfOut(){
    return this->isOut;
}

void Player::setHumanity(bool isPlayerHuman){
    this->isHuman=isPlayerHuman;
    return;
}

void Player::setTotalPoints(int totalPoints){
    this->playerPoints=totalPoints;
    return;
}

void Player::addPoints(int newPoints){
    this->playerPoints+=newPoints;
    return;
}
void Player::setTurn(bool isNext){
    this->isTurn=isNext;
    return;
}
//void Player::setDeck(Deck *playerDeck){
//    this->deck=playerDeck;
//    return;
//}
void Player::setPlayerNumber(int num){
    this->playerNumber=num;
    return;
}
void Player::setOut(bool areYouOut){
    this->isOut=areYouOut;
}

void Player::deletePoints(){
    this->playerPoints=0;
}

//void Player::showHand(){
//    // will update this later after deck class has multiple print statements
//    // will also need to add logic to ensure the deck will not
//    // try to print when the player hasn't been dealt a deck yet.
//    cout << "\tShowing hand: " << endl;
//    this->deck->printDecks();
//    cout << "\tHand should be above " << endl;
//}
