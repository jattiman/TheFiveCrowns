/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/1/2019                                            *
 ***************************************************************
 */

/* *********************************************************************
 Function Name:
 Purpose:
 Parameters:
 Return Value:
 Local Variables:
 Algorithm:
 Assistance Received:
 ********************************************************************* */

#include "Deck.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
// include for shuffle, since random_shuffle was removed in C++17
#include <random>
#include <chrono>

using namespace std;

Deck::Deck(){
    // make/fill deck
    this->makeDeck();
    
}

Deck::Deck(int roundInput){
    this->setRound(roundInput);
    this->makeDeck();
    
}

void Deck::makeDeck(){
    // populate the deck with cards
    // bonus: based on round number, make those cards wild cards
    // to do: logic to populate the deck itself.
    // array deck version (probably harder than vector) ...
//    for(int i=0; i<58; i++){
//        this->cards[i]=new Card();
//    }
    
    // vector deck. I guess it's all good either way though ...
    // manual assignment start deck
//    mainDeck.insert(mainDeck.end(), {new Card("3H"),
//        new Card("4H"),
//        new Card("5H")});
    // for loop assignment start deck
//    for(int j=0;j<3;j++){
//        mainDeck.push_back(new Card("JH"));
//    }
    
    //push on Jokers
    mainDeck.push_back(new Card("J1",this->getRound()));
    mainDeck.push_back(new Card("J2",this->getRound()));
    mainDeck.push_back(new Card("J3",this->getRound()));
    mainDeck.push_back(new Card("J1",this->getRound()));
    mainDeck.push_back(new Card("J2",this->getRound()));
    mainDeck.push_back(new Card("J3",this->getRound()));
    
    //push back cards using pre-made strings
    string cardFaces="3456789XJQK";
    string cardSuites="SCDHT";
    
    //for loop to add cards based on string values
    for(int deck=0;deck<2;deck++){
        for(int suites = 0; suites<cardSuites.size(); suites++){
            for(int faces = 0; faces<cardFaces.size(); faces++){
                mainDeck.push_back(new Card(cardFaces[faces],cardSuites[suites],this->getRound()));
            }
        }
    }
    
    this->shuffleDeck();
    //deck through string stream because why not?
    vector<string> cardString(116);
    
    
    return;
}

void Deck::setRound(int roundInput){
    ourRound=roundInput;
    return;
}

int Deck::getRound(){
    return ourRound;
}

void Deck::printDecks(){
    cout << "Main Deck: ";          // debug
    this->printTheDeck(mainDeck);   // debug
    cout << "Draw Pile: ";
    this->printTheDeck(drawPile);
    cout << "Discard Pile: ";
    //this->printTheDeck(discardPile);
    this->displayDiscardTop();
    //this->testDeck();     // debug
}

void Deck::printTheDeck(std::vector<Card*> cardPile){
    for(auto &i: cardPile){
        cout << i->getFace() << i->getSuite() << " ";
    }
    cout << endl;
    return;
}

void Deck::displayDiscardTop(){
    //this->discardPile.push_back(new Card("J1", this->getRound()));
    if(this->discardPile.size()>0){
        cout << this->discardPile[0]->getFace() << this->discardPile[0]->getSuite() << endl;
    }
    else{
        cout << "Empty" << endl;
    }
    return;
}

/* *********************************************************************
Function Name: shuffleDeck()
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received: After random_shuffle was removed from C++17 (my IDE updated to inform me of this a few weeks after this was set up), I opted to use shuffle. C++ reference assisted with this, at the following URL: http://www.cplusplus.com/reference/algorithm/shuffle/ . I additionally used this URL for a coding example, which I mirrored in terms of the local variable name "seed": https://www.geeksforgeeks.org/shuffle-vs-random_shuffle-c/
********************************************************************* */
void Deck::shuffleDeck(){
    // random_shuffle was removed from C++17.
    //random_shuffle(mainDeck.begin(),mainDeck.end());
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle(this->mainDeck.begin(), this->mainDeck.end(), std::default_random_engine(seed));
    return;
}

void Deck::shuffleDeck(std::vector<Card*> & cardPile){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle(cardPile.begin(), cardPile.end(), std::default_random_engine(seed));
    return;
}

unsigned long Deck::getDeckSize(std::vector<Card*> cardPile){
    return cardPile.size();
}

// come back to this after you hardcode the cards.
void Deck::stringToCardInputs(std::string cardInputString){
//    std::string text = "3H 4H 5H 6H 7H 8H 9H 10H";
//
//    std::istringstream iss(text);
//    this->cardInputs(std::istream_iterator<std::string>{iss},
//                                     std::istream_iterator<std::string>());
    return;
}


void Deck::testDeck(){
    cout << "\tDesk test" << endl;
    //this->printTheDeck(mainDeck);
//    cout << this->getDeckSize(mainDeck) << endl;
//    cout << "Testing card functions in deck. Joker wild first." << endl;
//    cout << "Card 0 face: " << mainDeck[0]->getFace() << endl;
//    cout << "Card 0 wild?: " << mainDeck[0]->getWildStatus() << endl;
//    cout << "Changing to Joker: " << endl;
//    mainDeck[0]->setFace('J');
//    cout << "Card 0 face: " << mainDeck[0]->getFace() << endl;
//    mainDeck[0]->checkForWild(1);
//    cout << "Card 0 wild?: " << mainDeck[0]->getWildStatus() << endl;
    for(auto &i: this->mainDeck){
        cout << "\t" << i->getFace() << i->getSuite() << ": "<< i->getPointValue() << " point(s). " << "Wild?: " << i->getWildStatus() << endl;
    }
    cout << endl;
    
    return;
}
