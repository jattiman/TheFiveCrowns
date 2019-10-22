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
    // default deck made, round set to 1
    // drawPile capacity reserved to 119 (round 1)
    this->drawPile.reserve(119);
    // make/fill deck
    this->makeDeck();
    
}

Deck::Deck(int roundInput){
    this->setRound(roundInput);
    // set drawPile size based on round number
    this->drawPile.reserve((58*2-((roundInput+2)*2)-1));
    this->makeDeck();

    
}

void Deck::makeDeck(){
    // populate the deck with cards

    // manual assignment start deck
    
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
    // // deck through string stream because why not?
    // vector<string> cardString(116);
    
    // this->testDeck();
    this->dealDeck();
    
    return;
}

void Deck::dealDeck(){
    // (round+2) cards * 2 players
    // deal to players
    for(int i=0;i<(this->getRound()+2);i++){
        this->transferCard(this->getMainPile(), this->getHumanDeck());
        this->transferCard(this->getMainPile(), this->getComputerDeck());
    }
    
    // 1 for discard pile
    this->transferCard(this->getMainPile(), this->getDiscardPile());
    
    // remaining goes to draw pile
    this->getDrawPile()=this->getMainPile();
    this->getMainPile().clear();
    
    // confirm cards present (debug)
//    cout << "Total cards present: " << this->getDrawPile().size() + this->getMainPile().size() + this->getHumanDeck().size() + this->getComputerDeck().size() + this->getDiscardPile().size() << endl;
    return;
}

void Deck::setRound(int roundInput){
    ourRound=roundInput;
    return;
}

void Deck::setPlayerHand(std::vector<std::string> playerHand){
    vector<Card*> tempHand;
    for(auto i: playerHand){
        tempHand.push_back(new Card(i,this->getRound()));
    }
    this->humanPile=tempHand;
    tempHand.clear();
    return;
}

//void Deck::setPlayerHand(std::vector<Card*> playerHand){
//    // make the human pile equivalent to the copy of the playerHand
//    // being passed in
//    this->humanPile=playerHand;
//    return;
//}

void Deck::setComputerHand(std::vector<std::string> computerHand){
    vector<Card*> tempHand;
    for(auto i: computerHand){
        tempHand.push_back(new Card(i,this->getRound()));
    }
    this->computerPile=tempHand;
    tempHand.clear();
    return;
}

//void Deck::setComputerHand(std::vector<Card*> computerHand){
//    // swap copy of the computer hand into the computer pile
//    this->computerPile=computerHand;
//    return;
//}

void Deck::setDrawPile(std::vector<std::string> drawHand){
    vector<Card*> tempHand;
    for(auto i: drawHand){
        tempHand.push_back(new Card(i,this->getRound()));
    }
    this->drawPile=tempHand;
    tempHand.clear();
    return;
}

void Deck::setDiscardPile(std::vector<std::string> discardHand){
    vector<Card*> tempHand;
    //ensure Discard pile is populated in the correct order
    for(std::vector<string>::reverse_iterator i=discardHand.rbegin(); i!=discardHand.rend();++i){
        tempHand.push_back(new Card(*i,this->getRound()));
    }
    this->discardPile=tempHand;
    tempHand.clear();
    return;
}


int Deck::getRound(){
    return ourRound;
}

std::vector<Card*> & Deck::getHumanDeck(){
    return this->humanPile;
}

std::vector<Card*> & Deck::getComputerDeck(){
    return this->computerPile;
}
std::vector<Card*> & Deck::getMainPile(){
    return this->mainDeck;
}
std::vector<Card*> & Deck::getDrawPile(){
    return this->drawPile;
}
std::vector<Card*> & Deck::getDiscardPile(){
    return this->discardPile;
}
void Deck::printDecks(){
    // print the draw pile
    cout << "Draw Pile: ";
    this->printTheDeck(drawPile);
    cout << endl;
    // print the discard pile
    cout << "Discard Pile: ";
    this->displayDiscardTop();
    cout << endl;
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
//        cout << this->discardPile[0]->getFace() << this->discardPile[0]->getSuite() << endl;
        cout << this->discardPile.back()->getFace() << this->discardPile.back()->getSuite() << endl;
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
    unsigned seed = (unsigned) std::chrono::system_clock::now().time_since_epoch().count();

    shuffle(this->mainDeck.begin(), this->mainDeck.end(), std::default_random_engine(seed));
    return;
}

void Deck::shuffleDeck(std::vector<Card*> & cardPile){
    unsigned seed = (unsigned) std::chrono::system_clock::now().time_since_epoch().count();

    shuffle(cardPile.begin(), cardPile.end(), std::default_random_engine(seed));
    return;
}

unsigned long Deck::getDeckSize(std::vector<Card*> cardPile){
    return cardPile.size();
}

void Deck::transferCard(std::vector<Card*> &startPile, std::vector<Card*> &endPile){
    
    endPile.push_back(startPile[0]);
    startPile.erase(startPile.begin());
    return;
}

bool Deck::transferCard(std::vector<Card*> &startPile, int startLocation, std::vector<Card*> &endPile){
    // confirm the starting card pile has cards
    if(startPile.empty()){
        return false;
    }
    // if cards are present, move the chosen card to the end pile
    else{
        //swap(startPile[startLocation],endPile[endLocation]);
        endPile.push_back(startPile[startLocation]);
        startPile.erase(startPile.begin()+startLocation);
        return true;
    }
}

//bool Deck::transferFromDiscard(std::vector<Card*> &startPile, std::vector<Card*> &endPile){
//    if(startPile.empty()){
//        return false;
//    }
//    else{
//        endPile.push_back(startPile.back());
//        startPile.pop_back();
//        return true;
//    }
//}
bool Deck::transferFromDiscard(std::vector<Card*> &endPile){
    if(this->getDiscardPile().empty()){
        return false;
    }
    else{
        endPile.push_back(this->getDiscardPile().back());
        this->getDiscardPile().pop_back();
        return true;
    }
}

bool Deck::transferFromDraw(std::vector<Card*> & endPile){
    if(this->getDrawPile().empty()){
        return false;
    }
    else{
        endPile.push_back(this->getDrawPile()[0]);
        this->getDrawPile().erase(this->getDrawPile().begin());
        return true;
    }
}

int Deck::countCardPoints(std::vector<Card*> & hand){
    int points=0;
    // iterate through vector
    // count points for non-set cards only
    for(auto &i: hand){
        if(!(i->getRunStatus() || i->getBookStatus())){
            points+=i->getPointValue();
        }
    }
    return points;
}

int Deck::findCard(std::vector<Card *> &hand, string userSearch){
    int cardIndex=-1;
    int handIndex=0;
    
    for (const auto & i: hand){
        if(i->getCardString()==userSearch){
            cardIndex=handIndex;
            break;
        }
        handIndex++;
    }
    return cardIndex;
}

//Card* Deck::removeTopCard(std::vector<Card *> &cardPile){
//    cout << "Removing " << cardPile[0]->getFace() << cardPile[0]->getSuite();
//    return cardPile[0];
//}

// come back to this after you hardcode the cards.
void Deck::stringToCardInputs(std::string cardInputString){
//    std::string text = "3H 4H 5H 6H 7H 8H 9H 10H";
//
//    std::istringstream iss(text);
//    this->cardInputs(std::istream_iterator<std::string>{iss},
//                                     std::istream_iterator<std::string>());
    return;
}

bool Deck::checkIfAllWild(std::vector<Card*> cardPile){
    bool areTheyWild=true;
    for(auto i: cardPile){
        if(!(i->getWildStatus())){
            areTheyWild=false;
            break;
        }
    }
    return areTheyWild;
}

int Deck::countWilds(std::vector<Card *> & cardPile){
    cout << "Temp pile before count wilds is: ";
    for (auto i: cardPile){
        cout << i->getCardString() << " ";
    }
    cout << endl;
    int wildCount=0;
    vector<Card*> swapDeck;
//    cout << "Temp pile before countWilds is: ";
//    for (auto i: cardPile){
//        cout << i->getCardString() << " ";
//    }
//    cout << endl;
    // iterate through the temp pile
    for(auto i: cardPile){
        // if wild card detected, increment wild count
        if(i->getWildStatus()){
            wildCount++;
        }
        // if not, push non-wild card to temp deck
        else{
            swapDeck.push_back(i);
        }
    }
    // swap the decks to update the temp pile
    if(!swapDeck.empty()){
        swapDeck.swap(cardPile);
    }
//    cout << "Temp pile after countWilds is: ";
//    for (auto i: cardPile){
//        cout << i->getCardString() << " ";
//    }
//    cout << endl;
    cout << "Temp pile after count wilds is: ";
    for (auto i: cardPile){
        cout << i->getCardString() << " ";
    }
    cout << endl;
    return wildCount;
}

bool Deck::checkIfSameSuit(std::vector<Card *> cardPile){
    char ourSuite=cardPile[0]->getSuite();
    // first, check to confirm all suites are the same
    for (auto i: cardPile){
        if(i->getSuite()!=ourSuite && !(i->getWildStatus())){
            return false;
        }
    }
    return true;
}

bool Deck::checkIfRun(std::vector<Card*> & cardPile, int & numWilds){
    
    cout << "Temp pile before check run is: ";
    for (auto i: cardPile){
        cout << i->getCardString() << " ";
    }
    cout << endl;
    
    bool areTheyInRun=true;
    int cardDistance=0;
    // first, check to confirm all suites are the same
    areTheyInRun=this->checkIfSameSuit(cardPile);
    // if all suites are the same, check to see if the faces are consecutive
    vector<int> cardFaces;
    cardFaces.reserve(cardPile.size());
    for(auto i: cardPile){
        switch (i->getFace()) {
            case '3':
                cardFaces.push_back(3);
                break;
            case '4':
                cardFaces.push_back(4);
                break;
            case '5':
                cardFaces.push_back(5);
                break;
            case '6':
                cardFaces.push_back(6);
                break;
            case '7':
                cardFaces.push_back(7);
                break;
            case '8':
                cardFaces.push_back(8);
                break;
            case '9':
                cardFaces.push_back(9);
                break;
            case 'X':
                cardFaces.push_back(10);
                break;
            case 'J':
                cardFaces.push_back(11);
                break;
            case 'Q':
                cardFaces.push_back(12);
                break;
            case 'K':
                cardFaces.push_back(13);
                break;
            default:
                break;
        }
    }
    // iterate through vector and confirm that the values are within 1 of each other
    sort(cardFaces.begin(), cardFaces.end());
//    cout << "\n\t\t\tCard faces in run: ";
//    for (auto i: cardFaces){
//        cout << i << " ";
//    }
//    cout << endl << endl;
    for(int i=1;i<cardFaces.size();i++){
        cardDistance=cardFaces[i]-cardFaces[i-1];
        while(cardDistance>1 && numWilds>0){
            cardDistance-=1;
            numWilds-=1;
        }
        if(cardDistance!=1){
            areTheyInRun=false;
        }
    }
    cout << "Temp pile after check run is: ";
    for (auto i: cardPile){
        cout << i->getCardString() << " ";
    }
    cout << endl;
    // return if they're in a run
    return areTheyInRun;
}

bool Deck::checkIfBook(std::vector<Card*> & cardPile, int & numWilds){
    vector<Card*> swapDeck;
    bool areInBook=true;
    char ourFace;
    int faceCount[11]={0,0,0,0,0,0,0,0,0,0,0};
    vector<int> facesToBook;
    
    for(auto i: cardPile){
        switch (i->getFace()) {
            case '3':
                faceCount[0]+=1;
                break;
            case '4':
                faceCount[1]+=1;
                break;
            case '5':
                faceCount[2]+=1;
                break;
            case '6':
                faceCount[3]+=1;
                break;
            case '7':
                faceCount[4]+=1;
                break;
            case '8':
                faceCount[5]+=1;
                break;
            case '9':
                faceCount[6]+=1;
                break;
            case 'X':
                faceCount[7]+=1;
                break;
            case 'J':
                faceCount[8]+=1;
                break;
            case 'Q':
                faceCount[9]+=1;
                break;
            case 'K':
                faceCount[10]+=1;
                break;
            default:
                break;
        }
    }
    
    cout << "Temp pile before check book is: ";
    for (auto i: cardPile){
        cout << i->getCardString() << " ";
    }
    cout << endl;
    
    for(int arrayNav=0;arrayNav<11;arrayNav++){
        if(faceCount[arrayNav]>3){
            facesToBook.push_back(arrayNav+3);
        }
    }
    cout << " These are the faces we're booking: " ;
    for (auto i: facesToBook){
        cout << i << " ";
    }
    cout << endl;
    
    ourFace=cardPile[0]->getFace();
    for(auto i: cardPile){        if(find(facesToBook.begin(),facesToBook.end(),i->getPointValue())!=facesToBook.end()){
            swapDeck.push_back(i);
            
        }
        else{
            areInBook=false;
        }
    }
    
    if(areInBook && !((cardPile.size()+numWilds)>2)){
        cout << "Just shy of a book." << endl;
        areInBook=false;
    }
    if(!swapDeck.empty()){
        swapDeck.swap(cardPile);
    }
    cout << "Temp pile after check book is: ";
    for (auto i: cardPile){
        cout << i->getCardString() << " ";
    }
    cout << endl;
    return areInBook;
}

bool Deck::checkIfOut(std::vector<Card*> cardPile){
    vector<Card*> tempPile=cardPile;
    // holds the number of wild cards
    int numberOfWilds;
    
    // get wild number and trim wilds
    numberOfWilds=this->countWilds(tempPile);
    
    // if entire deck was wild, we're out
    if(tempPile.empty() || numberOfWilds==cardPile.size()){
        return true;
    }
    
    // check if remaining cards are in a book
    if(this->checkIfBook(tempPile, numberOfWilds) || tempPile.empty()){
        return true;
    }
    
    // check if remaining cards all in run
    if(this->checkIfRun(tempPile, numberOfWilds) || tempPile.empty()){
        return true;
    }
    // if we still have leftover cards, we're out of luck
    return false;
}

string Deck::deckToString(std::vector<Card *> cardPile){
    // Turn the deck into a string
    // create string variable to hold the deck
    string deckString;
    // iterate through deck, and append cards to the string
    for(const auto &i: cardPile){
        deckString += i->getFace();
        deckString += i->getSuite();
        deckString += " ";
    }
    // return the string
    return deckString;
}

string Deck::discardPileString(std::vector<Card *> cardPile){
    string deckString;
    for(const auto &i: cardPile){
        // add cards in reverse order (we'll reverse the string later)
        deckString += " ";
        deckString += i->getSuite();
        deckString += i->getFace();
    }
    // reverse the string
    reverse(deckString.begin(),deckString.end());
    return deckString;
}

void Deck::testDeck(){
    
    
    return;
}
