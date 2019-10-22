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
//    cout << "Temp pile after count wilds is: ";
//    for (auto i: cardPile){
//        cout << i->getCardString() << " ";
//    }
//    cout << endl;
    return wildCount;
}

bool Deck::checkIfSameSuit(std::vector<Card *> cardPile){
    // if the card pile is empty, ignore and return
    if(!cardPile.empty()){
        // otherwise, confirm our suit
        char ourSuite=cardPile[0]->getSuite();
        // next, confirm all suites in the hand are the same
        for (auto i: cardPile){
            if(i->getSuite()!=ourSuite && !(i->getWildStatus())){
                return false;
            }
        }
    }
    return true;
}

bool Deck::checkSuitRun(std::vector<Card*> & cardPile, int & numWilds){
//    cout << "Before check suite run: ";
//    for (auto i: cardPile){
//        cout << i->getCardString() << " ";
//    }
//    cout << endl;
    // if there is no suite, ignore it and return
    if(cardPile.empty()){
        return true;
    }
    
    // if the amount of cards in the suite, plus wilds, isn't >=3, ignore and return false
    if(cardPile.size()+numWilds<3){
        return false;
    }
    
    // variable to calculate card distance between suite entries
    int cardDistance=0;
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
                cout << "Illegal card face detected! OH NO!!!" << endl;
                break;
        }
    }
    // iterate through vector and confirm that the values are within 1 of each other
    sort(cardFaces.begin(), cardFaces.end());
//    cout << "\n\t\t\tCard faces in order: ";
//    for (auto i: cardFaces){
//        cout << i << " ";
//    }
//    cout << endl;
    int wildsOut=0;
    for(int i=1;i<cardFaces.size();i++){
        // check each index in the vector for consecutive numbers
        cardDistance=cardFaces[i]-cardFaces[i-1];
        while(cardDistance>1 && numWilds>0){
            cardDistance-=1;
            numWilds-=1;
            wildsOut+=1;
        }
        // if the run can't be completed, even with wilds
        if(cardDistance!=1){
            // add back in the wilds and return false
            numWilds+=wildsOut;
//            cout << "\nReturning: this sub hand isn't a run. \n";
            return false;
        }
    }
    
//    cout << "after check suite run: ";
//    for (auto i: cardPile){
//        cout << i->getCardString() << " ";
//    }
//    cout << endl;
    return true;
}

bool Deck::checkIfRun(std::vector<Card*> & cardPile, int & numWilds){
    // create the swap deck
    vector<Card*> swapDeck;
    // hold if a run has been made with ALL cards
    bool areTheyInRun=true;
    // create sub decks for each suit
    vector<Card*> hearts;
    vector<Card*> tridents;
    vector<Card*> clubs;
    vector<Card*> spades;
    vector<Card*> diamonds;
//    cout << "Temp pile before check run is: ";
//    for (auto i: cardPile){
//        cout << i->getCardString() << " ";
//    }
//    cout << endl;
    
    // place cards in appopriate sub decks
    for (auto i: cardPile){
        switch (i->getSuite()) {
            case 'H':
                hearts.push_back(i);
                break;
            case 'T':
                tridents.push_back(i);
                break;
            case 'D':
                diamonds.push_back(i);
                break;
            case 'S':
                spades.push_back(i);
                break;
            case 'C':
                clubs.push_back(i);
                break;
            default:
                break;
        }
    }
    // check each pile to see if it's a run
    if(!(this->checkSuitRun(hearts, numWilds))){
        for(auto i: hearts){
            swapDeck.push_back(i);
        }
        areTheyInRun=false;
    }
    if(!(this->checkSuitRun(tridents, numWilds))){
        for(auto i: tridents){
            swapDeck.push_back(i);
        }
        areTheyInRun=false;
    }
    if(!(this->checkSuitRun(diamonds, numWilds))){
        for(auto i: diamonds){
            swapDeck.push_back(i);
        }
        areTheyInRun=false;
    }
    if(!(this->checkSuitRun(spades, numWilds))){
        for(auto i: spades){
            swapDeck.push_back(i);
        }
        areTheyInRun=false;
    }
    if(!(this->checkSuitRun(clubs, numWilds))){
        for(auto i: clubs){
            swapDeck.push_back(i);
        }
        areTheyInRun=false;
    }
    
    
    // if it's not, add it to the swapDeck to be checked in other functions
    
    
    // if it is, add it to the removal deck
    cardPile.clear();
    if(!swapDeck.empty()){
        swapDeck.swap(cardPile);
    }
    
//    cout << "Temp pile after check run is: ";
//    for (auto i: cardPile){
//        cout << i->getCardString() << " ";
//    }
//    cout << endl;
//    cout << "Swap pile after check run is: ";
//    for (auto i: swapDeck){
//        cout << i->getCardString() << " ";
//    }
//    cout << endl;
    // return if they're in a run
    return areTheyInRun;
}

bool Deck::checkIfBook(std::vector<Card*> & cardPile, int & numWilds){
    // create the swapDeck for uncounted cards
    vector<Card*> swapDeck;
    // hold if all values are in a book
    bool areInBook=true;
    // holds a count of all the times a specific face comes up
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
    
//    cout << "Temp pile before check book is: ";
//    for (auto i: cardPile){
//        cout << i->getCardString() << " ";
//    }
//    cout << endl;
    
    for(int arrayNav=0;arrayNav<11;arrayNav++){
        if(faceCount[arrayNav]>2){
            facesToBook.push_back(arrayNav+3);
        }
    }
//    cout << "\n\tHere's the array we're navigating: ";
//    for(int arrayNav=0;arrayNav<11;arrayNav++){
//        cout << faceCount[arrayNav] << " ";
//    }
//    cout << "\n\t These are the faces we're booking: " ;
//    for (auto i: facesToBook){
//        cout << i << " ";
//    }
//    cout << endl;
    
    for(auto i: cardPile){
        //cout << "Looking for " << i->getPointValue() << " card: ";
//        if(find(facesToBook.begin(),facesToBook.end(),i->getPointValue())!=facesToBook.end()){
//            swapDeck.push_back(i);
//            cout << "Found.\n";
//        }
//        else{
//            cout << "NOT FOUND.\n";
//            areInBook=false;
//        }
//
        if(!(find(facesToBook.begin(),facesToBook.end(),i->getPointValue())!=facesToBook.end())){
            //cout << "NOT FOUND.\n";
            swapDeck.push_back(i);
            areInBook=false;
        }
        //cout << "\n";
      
    }
    
    if(!swapDeck.empty()){
        swapDeck.swap(cardPile);
    }
    
    if(areInBook && !((cardPile.size()+numWilds)>2)){
        cout << "Just shy of a book." << endl;
        areInBook=false;
    }
    
//    cout << "Temp pile after check book is: ";
//    for (auto i: cardPile){
//        cout << i->getCardString() << " ";
//    }
//    cout << endl;
//    cout << "Swap pile after check book is: ";
//    for (auto i: swapDeck){
//        cout << i->getCardString() << " ";
//    }
//    cout << endl;
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
    
    // check if remaining cards are in a book
    if(this->checkIfBook(tempPile, numberOfWilds) || tempPile.empty()){
        return true;
    }
    
    // check if remaining cards all in run
    if(this->checkIfRun(tempPile, numberOfWilds) || tempPile.empty()){
        return true;
    }
    cout << "Remaining non-book/non-run cards: ";
    for (auto i: tempPile){
        cout << i->getCardString() << " ";
    }
    cout << endl;
    // if we still have leftover cards, we're out of luck
    return false;
}

/* *********************************************************************
Function Name: tallyRemainingCardPoints
Purpose: To tally the point values of cards in a deck that are not part of books or runs
Parameters:
 cardPile: the deck being passed in as a vector array of card pointers. In this case, the player or computer hand. This is passed by reference. The program would typically input a temporary vector of cards, which would be sorted/cut based on confirmed books and runs. Because it's passed by reference, the temporary vector can be used by the human or computer to output information or act on advice.
Return Value: an integer of the remaining points that would be incurred if the player did not go out.
Local Variables:
 totalPoints: int, holds the total point values
 tempPile: vector of card pointers to be manipulated by the function
 numberOfWilds: int, holds the number of wildcards detected
 Algorithm:
 Call function to check for wilds and trim them from the deck
 Confirm the deck isn't empty (all wilds). If it is, return 0 points and exit function.
 Call function to check if remaining deck is book. Trim books.
 Call function to check if remaining deck is run. Trim runs.
 Call function to check if book again. Trim.
 Call function to check if run again. Trim.
 Tally points for remaining rounds (iterate through temp vector).
 Return points.
Assistance Received: None
********************************************************************* */
int Deck::tallyRemainingCardPoints(std::vector<Card*> &cardPile){
    // holds total points received
    int totalPoints=0;
    // holds temp vector
    vector<Card*> tempPile=cardPile;
    // holds the number of wild cards
    int numberOfWilds;
    
    // get wild number and trim wilds
    numberOfWilds=this->countWilds(tempPile);
    
    // if entire deck was wild, we're out
    if(tempPile.empty() || numberOfWilds==cardPile.size()){
        return 0;
    }
    
    // check if remaining cards are in a book
    if(this->checkIfBook(tempPile, numberOfWilds) || tempPile.empty()){
        return 0;
    }
    
    // check if remaining cards all in run
    if(this->checkIfRun(tempPile, numberOfWilds) || tempPile.empty()){
        return 0;
    }
    
    // check if remaining cards are in a book
    if(this->checkIfBook(tempPile, numberOfWilds) || tempPile.empty()){
        return 0;
    }
    
    // check if remaining cards all in run
    if(this->checkIfRun(tempPile, numberOfWilds) || tempPile.empty()){
        return 0;
    }
    // if we still have leftover cards, tally their points
    totalPoints=countCardPoints(tempPile);
    tempPile.swap(cardPile);
    return totalPoints;
}

/* *********************************************************************
Function Name: deckToString
Purpose: To create a string variable representing all decks/card piles aside from the discard pile
Parameters:
 cardPile: the deck being passed in as a vector array of card pointers. Could be a player hand, the draw pile, discard pile, etc.
Return Value: The string representing the cards in the pile
Local Variables: deckString, a string to be appended with card items
Algorithm:
 iterate through the card pile,
 append the cards to the deck in normal order (face, suite, and a space),
 return the appended string
Assistance Received: None
********************************************************************* */
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

/* *********************************************************************
Function Name: discardPileString
Purpose: To create a string variable representing the discard pile, which is displayed differently than other cards.
Parameters:
 cardPile: the deck being passed in as a vector array of card pointers. Although this would always be the discard pile, we're still passing in the variable for potential future expansion of the game.
Return Value: The string representing the cards in the discard pile
Local Variables: deckString, a string to be appended with card items
Algorithm:
 iterate through the card pile,
 append the cards to the deck in reverse order (each card is put in backwards),
 reverse the string so that it displays correctly when printed out.
 return the string
Assistance Received: None
********************************************************************* */
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
