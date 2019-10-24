/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/1/2019                                            *
 ***************************************************************
 */

#include "Deck.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
// include for shuffle, since random_shuffle was removed in C++17
#include <random>
#include <chrono>

using namespace std;

/* *********************************************************************
Function Name: Deck (constructor function)
Purpose: construct the deck.
 Note: should have included optional parameters to avoid having to make a default constructor and a constructor with additional inputs
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
 reserve the draw pile size based on max draw pile
 Make the deck
Assistance Received: none
********************************************************************* */
Deck::Deck(){
    // default deck made, round set to 1
    // drawPile capacity reserved to 119 (round 1)
    this->drawPile.reserve(119);
    // make/fill deck
    this->makeDeck();
    
}

/* *********************************************************************
Function Name: Deck (constructor function)
Purpose: construct the deck with round input in mind
Parameters: roundInput
Return Value: none
Local Variables: none
Algorithm:
 set round based on round input
 reserve the draw pile size based on the round input
 make the deck
Assistance Received: none
********************************************************************* */
Deck::Deck(int roundInput){
    this->setRound(roundInput);
    // set drawPile size based on round number
    this->drawPile.reserve((58*2-((roundInput+2)*2)-1));
    this->makeDeck();

    
}

/* *********************************************************************
Function Name:makeDeck
Purpose: to create the big deck based on 2 smaller decks (which are also created in this function). Note: the "smaller decks" are not deck objects.
Parameters: none
Return Value: none
Local Variables:
 string cardFaces: holds characters representing the card faces
 string cardSuites: holds characters representing the suits of the cards
 int deck: needed for counting the number of decks
 int suites: needed for counting the number of suits
 int faces: needed for counting the number of faces
Algorithm:
 Create jokers to push back to the master deck from each deck (3 of each)
 Based on 2 counts of a deck, use card strings and card suit strings to push new cards back onto the main deck, with the class' round number in mind
 Call shuffle deck
 Call deal deck to deal the deck to players
 Return
Assistance Received: none
********************************************************************* */
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
    
    // shuffle the deck
    this->shuffleDeck();
    
    // deal the deck out
    this->dealDeck();
    
    return;
}

/* *********************************************************************
Function Name:dealDeck
Purpose: to deal the shuffled deck to the players
Parameters: None
Return Value: None
Local Variables: None
Algorithm:
 Deal the proper number of cards to players, based on the round number (round number +2) (transferCard function used for this)
 Deal one card to the discard pile (transferCard function called)
 Place the remaining cards in the draw pile (make draw pile equal to the big pile being dealt)
 Return
Assistance Received: none.
********************************************************************* */
void Deck::dealDeck(){
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
    
    return;
}

void Deck::setRound(int roundInput){
    ourRound=roundInput;
    return;
}

/* *********************************************************************
Function Name: setPlayerHand
Purpose: to set the player hand based on a string
Parameters:
 vector<string> playerHand
Return Value: none.
Local Variables:
 vector<Card*> tempHand: holds a temp hand of cards
Algorithm:
 Iterate through the string vector (playerHand)
 For each entry in the string, push the string of the card back into the temp hand
 Make the human pile (player hand) equal to the temp hand
 Clear the temp hand
 Return
Assistance Received: none
********************************************************************* */
void Deck::setPlayerHand(std::vector<std::string> playerHand){
    vector<Card*> tempHand;
    for(auto i: playerHand){
        tempHand.push_back(new Card(i,this->getRound()));
    }
    this->humanPile=tempHand;
    tempHand.clear();
    return;
}

/* *********************************************************************
Function Name: setComputerHand
Purpose: to set the computer hand based on a string
Parameters:
 vector<string> computerHand
Return Value: none.
Local Variables:
 vector<Card*> tempHand: holds a temp hand of cards
Algorithm:
 Iterate through the string vector (computerHand)
 For each entry in the string, push the string of the card back into the temp hand
 Make the computer hand equal to the temp hand
 Clear the temp hand
 Return
Assistance Received: none
********************************************************************* */
void Deck::setComputerHand(std::vector<std::string> computerHand){
    vector<Card*> tempHand;
    for(auto i: computerHand){
        tempHand.push_back(new Card(i,this->getRound()));
    }
    this->computerPile=tempHand;
    tempHand.clear();
    return;
}


/* *********************************************************************
Function Name:setDrawPile
Purpose: to set the draw pile up based on a string
Parameters:
 vector<string> drawHand
Return Value: none. void.
Local Variables:
 vector<Card*> tempHand: holds a temp hand of cards
Algorithm:
 Iterate through the string vector (drawHand)
 For each entry in the string, push the string of the card back into the temp hand
 Make the draw pile equal to the temp hand
 Clear the temp hand
 Return
Assistance Received: None
********************************************************************* */
void Deck::setDrawPile(std::vector<std::string> drawHand){
    vector<Card*> tempHand;
    for(auto i: drawHand){
        tempHand.push_back(new Card(i,this->getRound()));
    }
    this->drawPile=tempHand;
    tempHand.clear();
    return;
}

/* *********************************************************************
Function Name:setDiscardPile
Purpose: to set the discard pile from a string
Parameters:
 vector<string> discardHand: a string that holds the discard values
Return Value: void - none
Local Variables:
 vector<Card*>tempHand: holds a temporary hand pile
Algorithm:
 create temporary hand (empty)
 Iterate in reverse through a given string using the reverse_iterator function (library)
 For each item in the string, create a card to push back into the temp hand based on the round
    (The round number is important in determining the card wild status/points).
 Make the discard pile equal to the temp hand
 Clear the temp hand
Assistance Received: None
********************************************************************* */
void Deck::setDiscardPile(std::vector<std::string> discardHand){
    vector<Card*> tempHand;
    //ensure Discard pile is populated in the correct order
    for(std::vector<string>::reverse_iterator i=discardHand.rbegin(); i!=discardHand.rend();++i){
        tempHand.push_back(new Card(*i,this->getRound()));
    }
    // make the discard pile the tempHand
    this->discardPile=tempHand;
    // clear the temp hand
    tempHand.clear();
    return;
}
int Deck::getRound(){
    return ourRound;
}

// the following few functions are getters that I do not think need a header
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

/* *********************************************************************
Function Name: printDecks
Purpose: to print the decks that need to be displayed during each round
Parameters: none
Return Value: none, just prints to screen
Local Variables: none
Algorithm:
 Inform user the draw pile is about to be printed
 call printTheDeck on the draw pile
 Inform user the discard pile is about to be printed
 call printTheDeck on the discard pile
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name:printTheDeck
Purpose: to print a specific deck in order
Parameters:
 vector<Card*> cardPile: the deck hand you want to print
Return Value: none
Local Variables: none (I assume auto iterators can be ignored for this section)
Algorithm:
 Iterate through a vector of cards
 For each entry, print the face and suit of the card
Fun fact: I just realize now that I called the card suit getters and setters it "getSuite" instead of "getSuit". I like it. I'm keeping it.
Assistance Received: None
********************************************************************* */
void Deck::printTheDeck(std::vector<Card*> cardPile){
    for(auto &i: cardPile){
        cout << i->getFace() << i->getSuite() << " ";
    }
    cout << endl;
    return;
}

/* *********************************************************************
Function Name:displayDiscardTop
Purpose: to display the top of the discard pile
Parameters: none
Return Value: none - just prints a value, nothing returned
Local Variables: None
Algorithm:
 Confirm discard pile isn't empty
 If it's not empty, print the back of it to the screen.
 If it is empty, print that it's empty.
Assistance Received: None
********************************************************************* */
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
Purpose: to shuffle a hand/deck
Parameters:
Return Value: none
Local Variables:
 unsigned seed: needed to randomize the shuffle, utilizing the system clock
Algorithm:
 Create a random "seed" variable based on the system clock when run
 Use the shuffle function to shuffle the deck based on this random variable, reliant on the machine's system time and the chrono header
Assistance Received: After random_shuffle was removed from C++17 (my IDE updated to inform me of this a few weeks after this was set up - what joy to discover), I opted to use shuffle. C++ reference assisted with this, at the following URL: http://www.cplusplus.com/reference/algorithm/shuffle/ . I additionally used this URL for a coding example, which I mirrored in terms of the local variable name "seed": https://www.geeksforgeeks.org/shuffle-vs-random_shuffle-c/
********************************************************************* */
void Deck::shuffleDeck(){
    unsigned seed = (unsigned) std::chrono::system_clock::now().time_since_epoch().count();

    shuffle(this->mainDeck.begin(), this->mainDeck.end(), std::default_random_engine(seed));
    return;
}

/* *********************************************************************
Function Name:shuffleDeck
Purpose: to shuffle a hand/deck
Parameters:
 vector<Card*> & cardPile: deck pile being shuffled, passed by reference
Return Value: none
Local Variables:
 unsigned seed: needed to randomize the shuffle, utilizing the system clock
Algorithm:
 Create a random "seed" variable based on the system clock when run
 Use the shuffle function to shuffle the deck based on this random variable
Assistance Received: A lot of googling for this one. See the above shuffleDeck() function for more info
********************************************************************* */
void Deck::shuffleDeck(std::vector<Card*> & cardPile){
    unsigned seed = (unsigned) std::chrono::system_clock::now().time_since_epoch().count();

    shuffle(cardPile.begin(), cardPile.end(), std::default_random_engine(seed));
    return;
}

/* *********************************************************************
Function Name: getDeckSize
Purpose: to return the size of the deck, for error checking and file load/save
 Note: after I found out that the data given to us for the demo would always be valid, I decided to step back from validation checks. This function would have played a large part in those checks.
Parameters:
 vector<Card*> cardPile: creates copy of the card Pile that will be counted
Return Value: unsigned long of the size of the deck
Local Variables:
 None
Algorithm: simply returns the pile size
Assistance Received:
********************************************************************* */
unsigned long Deck::getDeckSize(std::vector<Card*> cardPile){
    return cardPile.size();
}

/* *********************************************************************
Function Name:transferCard
Purpose: to transfer a card from the front of a start pile to an end pile of cards
 Note: this was eventually abandoned in favor of more robust functions
Parameters:
 vector<Card*> &startPile, vector of cards holding the starting hand pile
 vector<Card*> &endPile, vector of cards holding the ending hand pile
Return Value:
 void/none
Local Variables: none
Algorithm:
 Adds the first item from the start pile to the end pile
 Erases the item from the front of the start pile
Assistance Received:
********************************************************************* */
void Deck::transferCard(std::vector<Card*> &startPile, std::vector<Card*> &endPile){
    
    endPile.push_back(startPile[0]);
    startPile.erase(startPile.begin());
    return;
}

/* *********************************************************************
Function Name:transferCard
Purpose: to transfer a card from one pile to another specific pile
Parameters:
 vector<Card*> &startPile, vector of cards passed by reference that holds the start pile
 int startLocation, integer holding the location that you want to move from the start pile
 vector<Card*> &endPile, vector of cards passed by reference holding the card destination
Return Value: true or false
Local Variables:
 None
Algorithm:
 Confirm that the start pile is not empty
 If it's not, take a card from it based on a chosen location
 Move that card to the end pile (push back)
 Erase that card from the start pile
Assistance Received: None
********************************************************************* */
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


/* *********************************************************************
Function Name: transferFromDiscard
Purpose: to transfer cards from the discard pile, which is handled uniquely
Parameters:
 vector<Card*> &endPile
Return Value: true or false
Local Variables:
 None
Algorithm:
 If the discard pile is empty, return false (it shouldn't be)
 Otherwise, push the card from the BACK of the discard pile to the end pile (human/computer hand)
 Note: the discard pile is displayed backwards to make manipulating it a bit easier, so pushing and popping from the back of the pile is possible, and makes it less resource-intensive (erasing from the front, if I recall correctly, causes the entire vector to be repopulated).
Assistance Received: none
********************************************************************* */
bool Deck::transferFromDiscard(std::vector<Card*> &endPile){
    // if the discard pile is empty, return false (shouldn't happen)
    if(this->getDiscardPile().empty()){
        return false;
    }
    // otherwise
    else{
        // push back the last entry in the discard pile to the chosen hand
        endPile.push_back(this->getDiscardPile().back());
        // delete the last entry in the discard pile
        this->getDiscardPile().pop_back();
        return true;
    }
}

/* *********************************************************************
Function Name:transferFromDraw
Purpose: to transfer cards from the draw pile, since the draw pile has a specific interaction format
Parameters:
 vector<Card*> & endPile: the end pile passed in by reference
Return Value: true or false
Local Variables:
 None
Algorithm:
 If the draw pile is empty, return false
 If the draw pile has cards, push the front card onto the end pile (human or computer), and erase the first entry in the draw pile (which was just moved)
Assistance Received: None
********************************************************************* */
bool Deck::transferFromDraw(std::vector<Card*> & endPile){
    // if the draw pile is empty, return false (shouldn't happen)
    if(this->getDrawPile().empty()){
        return false;
    }
    // otherwise
    else{
        // push back the card into the end pile from the front of the draw pile
        endPile.push_back(this->getDrawPile()[0]);
        // erase the front of the draw pile
        this->getDrawPile().erase(this->getDrawPile().begin());
        return true;
    }
}

/* *********************************************************************
Function Name:countCardPoints
Purpose: to count the point value of a given hand
Parameters:
 vector<Card*> & hand: the hand/deck being passed in
Return Value: integer representing the point value of th ehand
Local Variables:
 int points: holds the point tally
Algorithm:
 Iterate through the hand
 If the card is not in a book or run, add its point value to points
    Note: When handed in, I had not yet finished updating cards with their book/run status. This will be made more robust in the future. For now, all non-book/run cards are passed into this function, and all cards are therefore tallied for points.
Assistance Received: None.
********************************************************************* */
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

/* *********************************************************************
Function Name:findCard
Purpose: Finds a card in a hand, and returns the index of the card
Parameters:
 vector<Card *> &hand: the hand, passed in by reference
 string userSearch: the card being looked for, based on the string of the card
Return Value: integer reflecting the card index
Local Variables:
 int cardIndex: the cardIndex of the vector. Returns -1 by default if nothing is found.
    Note: this portion of the functionality is for future use, in case I implement user searches for a card. It would need further error checking to be implemented if it was based solely on user input. Right now, it's only called by confirmed cards in the deck.
 int handIndex: integer holding the current location in the vector
Algorithm:
 Iterate through a hand
 Increment handIndex for each card passed by
 If a card is found matching the user search, make cardIndex=handIndex, and break (finds first instance only)
 If a card isn't found, return -1 (won't happen - only confirmed cards are put into this function right now)
Assistance Received: None
********************************************************************* */
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

/* *********************************************************************
Function Name:stringToCardInputs
Purpose: to take a string and turn it into cards
    Note: this function was abandoned, but I'm keeping it here since I intend on making this more robust in the future and re-releasing it with this function implemented
Parameters:
 string cardInputString: the string passed in of card inputs
Return Value: void (none)
Local Variables: None
Algorithm: None
Assistance Received: None
********************************************************************* */
// come back to this after you hardcode the cards.
void Deck::stringToCardInputs(std::string cardInputString){
//    std::string text = "3H 4H 5H 6H 7H 8H 9H 10H";
//
//    std::istringstream iss(text);
//    this->cardInputs(std::istream_iterator<std::string>{iss},
//                                     std::istream_iterator<std::string>());
    return;
}

/* *********************************************************************
Function Name: checkIfAllWild
Purpose: checks to see if all cards in a hand are wild cards
    Note: this function was essentially removed as inefficient. Instead, we use the wildCard count, compared against the hand, to confirm if the deck was all wildcards.
Parameters:
 vector<Card*> cardPile: vector of cards (not passed by reference) to be examined
Return Value: true or false
Local Variables:
 bool aretheyWild: holds whether or not all cards in the hand are wildcards. true by default
Algorithm:
 Iterate through the deck
 If the card is not wild, update the areTheyWild variable to false and break from the loop
 Return areTheyWild
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name:countWilds
Purpose: count the number of wild cards in a hand
Parameters:
 vector<Card *> & cardPile: passed in by reference, because wildCards are pruned from the deck
Return Value: integer holding the number of wildcards detected
Local Variables:
 int wildCount: holds the number of wildcards present
 vector<Card*> swapDeck: vector of card pointers that holds the cards that aren't wildCards
Algorithm:
 Iterate through the hand
 For each hand that's a wildcard, increase the wildcard count
 For each hand that's NOT a wildcard, push it onto the temp deck
 If our deck contains all wildcards, the swap deck will be empty
 If the swapDeck is not empty, swap it with the cardPile (prune the wild cards)
 Return the wildCard count
Assistance Received: none
********************************************************************* */
int Deck::countWilds(std::vector<Card *> & cardPile){

    int wildCount=0;
    vector<Card*> swapDeck;

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
    return wildCount;
}

/* *********************************************************************
Function Name:checkIfSameSuit
Purpose: to confirm that all cards in a hand are in the same suite
    Note: this function was ultimately abandoned as too inefficient, but may be resurrected for a future version of this game. I just can't quit it. Instead of using this function, the hand was sorted into sub-decks which were then compared to books/runs
Parameters: vector<Card *> cardPile: a hand passed in as a copy
Return Value: true or false
Local Variables:
 char ourSuite: pulls the suite to be reviewed
Algorithm:
 Take in a hand
 Take the first suit in the hand, and make it the suit we're looking for
 Iterate through the rest of the hand, checking the suit
 If the remaining part of the deck is all in that suit, return true
 Otherwise, return false
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name:checkSuitRun
Purpose: to check an individual suite to see if it's a run
Parameters:
 vector<Card*> & cardPile: the card pile passed in by reference
 int & numWilds: holds the number of wilds in a deck, passed by reference
Return Value: true or false
Local Variables:
 int cardDistance: integer holding the distance between ordered card faces
 vector<int> cardFaces: vector of ints that holds the card faces found in each suite
 int wildsOut: int value holding the number of wilds decremented from the deck to complete a run
 
Algorithm:
 If the suite up for review is empty, skip this function and return true
 If the suite+wild card count is smaller than 3 (minimum needed for run), return false)
 Otherwise, create a vector of ints to hold cardfaces
 Populate it with the face of each card
 Sort the vector so it's in face order
 Loop through the vector (starting at the 2nd position), comparing its value with the face before it
 If the value is greater than 1 (cards aren't next to each other), decrement wildcards until it is 1, or until the wildCards run out
 If it isn't possible to make the distance 1, return the wildCard count to its previous number and return false.
    Note: I realized after doing this that hands with more than 3 cards might not count as runs if they have one card very far away from the others, even if the others are consecutive. In the future, I'll need to count runs differently.
 If the distance between all cards in the suit are 1, return true
Assistance Received: None.
********************************************************************* */
bool Deck::checkSuitRun(std::vector<Card*> & cardPile, int & numWilds){
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
    // create vector to hold the integers of the card faces
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
                // this should never display
                cout << "Illegal card face detected! OH NO!!!" << endl;
                break;
        }
    }
    // iterate through vector and confirm that the values are within 1 of each other
    sort(cardFaces.begin(), cardFaces.end());

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
            return false;
        }
    }

    return true;
}

/* *********************************************************************
Function Name: checkIfRun
Purpose: to check if the cards in the hand are all in a run
Parameters:vector<Card*> & cardPile, int & numWilds
Return Value: true/false
Local Variables:
 vector<Card*> swapDeck: holds cards not in run
 bool areTheyInRun: defaults to true: reflects if ALL cards are in a run
 vector<Card*> hearts/tridents/clubs/spades/diamonds: temp vectors that hold each suite
 
Algorithm:
 Divide hand into suites based on a review of each card
 Check the suite to see if it contains a run
 If any non-empty pile isn't in a run, return false
 If all the non-empty piles are in a run, return true
 
Assistance Received:
********************************************************************* */
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
    
    // return if they're in a run
    return areTheyInRun;
}

/* *********************************************************************
Function Name:checkIfBook
Purpose: checks to see if a hand is a book
Parameters:
 vector<Card*> & cardPile: the temp cardPile being passed through, passed by reference
 int & numWilds: holds the number of wilds, passed by reference
Return Value: true if book, false if not
Local Variables:
 vector<Card*> swapDeck: temporary deck to hold all non-book cards
 bool areInBook: starts true. Turns to false if the hand is all in a book
 vector<int>facesToBook: vector of ints that contains the faces in a book
 int faceCount[11]: array of ints that corresponds to the number of time a face appears in a hand
 int arrayNav: incremental variable for a for loop
Algorithm:
 create an array to tally the number of times a face comes through (each array position corresponds to a face)
 create a vector of ints to translate the faces in the cardPile itself
 Iterate through the cardPile and update the array to count the number of times each face appears
 Cycle through the vector, and if the face number is >2, add it to the vector to be removed (swapDeck)
    Note: I realize that I made a mistake with the math here, which would result in books potentially not being counted. The number of wild cards does not factor into this tally.
 If not empty, swap the swapdeck with the cardPile (updating it, passed by reference)
 Check to confirm that the number of cards+wildcards are sufficient for being a book
 If not, return false
 If so, return true
 
Assistance Received: None.
********************************************************************* */
bool Deck::checkIfBook(std::vector<Card*> & cardPile, int & numWilds){
    // create the swapDeck for uncounted cards
    vector<Card*> swapDeck;
    // hold if all values are in a book
    bool areInBook=true;
    // holds a count of all the times a specific face comes up
    int faceCount[11]={0,0,0,0,0,0,0,0,0,0,0};
    vector<int> facesToBook;
    // populate an array that contains only the faces
    // (sorting the vector by face would be preferred, but at my skill level, not yet possible based on the deadline)
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
    
    // if the face had a count of 3+, add the face number to the faces array
    for(int arrayNav=0;arrayNav<11;arrayNav++){
        if(faceCount[arrayNav]>2){
            facesToBook.push_back(arrayNav+3);
        }
    }
    
    // iterate through the cardPile, and add any faces that can't be removed to the swapDeck
    for(auto i: cardPile){
        // use the point value of the card to match the face int vector, since the point values correspond to the face. Note: wild/joker card point values wouldn't be an issue here, since these cards are pulled and tallied before this part occurs

        if(!(find(facesToBook.begin(),facesToBook.end(),i->getPointValue())!=facesToBook.end())){
            swapDeck.push_back(i);
            areInBook=false;
        }
    }
    
    // swap the cardPile (passed in by reference) with the temp deck, so the temp deck now only contains cards not in the book
    if(!swapDeck.empty()){
        swapDeck.swap(cardPile);
    }
    
    // if they're just shy from a book (with cards in hand & numWilds), but all the cards in the hand would be a book
    if(areInBook && !((cardPile.size()+numWilds)>2)){
        // taunt them
        cout << "Just shy of a book." << endl;
        // ensure that the variable is set to false
        areInBook=false;
    }
    
    // return whether or not the hand is all in a book
    return areInBook;
}

/* *********************************************************************
Function Name:checkIfOut
Purpose: Checks to see if a player's hand lets them go out
Parameters: vector<Card*> cardPile: a vector of card objects
Return Value: true or false
Local Variables:
 numberOfWilds, int, holds the number of wild cards in the deck
 vector<Card*> tempPile, vector of card objects, which is changed to remove all non-book/run cards
Algorithm:
 Create a temp card hand vector and holder for the number of wild cards
 Tally wild cards
 If the deck is all wild, go out
 Check the remaining hand to see if it's a book
 Check the remaining hand to see if it's a run
 Check book/run one more time
 Return true if the player can go out during any of these stages
 Otherwise, display the non-book/run cards, if present, and return false
Assistance Received: None.
********************************************************************* */
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
    // if we still have leftover cards, we're out of luck
    cout << "Remaining non-book/non-run cards: ";
    for (auto i: tempPile){
        cout << i->getCardString() << " ";
    }
    cout << endl;
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
    // if the only difference in deck sizes are the wild cards, the wild cards aren't effective, and should be tallied
    if(tempPile.size()+numberOfWilds!=cardPile.size()){
        // otherwise, include only the temp cards remaining
        tempPile.swap(cardPile);
    }
    totalPoints=countCardPoints(cardPile);
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
