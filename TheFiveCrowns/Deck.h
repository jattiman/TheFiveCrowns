/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/1/2019                                            *
 ***************************************************************
 */

#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>


class Deck{
    
public:
    Deck();
    Deck(int roundInput);
    void makeDeck();
    void setRound(int roundInput);
    int getRound();
    unsigned long getDeckSize(std::vector<Card*> cardPile);
    std::vector<Card*> & getHumanDeck();
    std::vector<Card*> & getComputerDeck();
    std::vector<Card*> & getMainPile();
    std::vector<Card*> & getDrawPile();
    std::vector<Card*> & getDiscardPile();
    
    void printDecks();
    void printTheDeck(std::vector<Card*> cardPile);
    void displayDiscardTop();
    void shuffleDeck();
    void shuffleDeck(std::vector<Card*> & cardPile);
    
    // transfering card functions
    // mainly from draw to end of another pile
    void transferCard(std::vector<Card*> &startPile, std::vector<Card*> &endPile);
    // for specific insertion of a card from one pile to another
//    void transferCard(std::vector<Card*> &startPile, int startLocation, std::vector<Card*> &endPile, int endLocation);
    // to pull from Discard pile (will pull from back)
    void transferFromDiscard(std::vector<Card*> &startPile, std::vector<Card*> &endPile);
    void transferFromDiscard(std::vector<Card*> &endPile);
    
    //Card * removeTopCard(std::vector<Card*> & cardPile);
    
    
    
    // for reading in files, this will be useful
    void stringToCardInputs(std::string cardInputString);
    void testDeck(); // for debug only - delete before submission
    
    // to do:
    //  print player hands (based on player name input)
    //  check for runs in a hand
    //  check for

    
private:
    
    // main 3 decks
    std::vector<Card*> mainDeck;
    std::vector<Card*> drawPile;
    std::vector<Card*> discardPile;
    
    // to deal to players
    std::vector<Card*> humanPile;
    std::vector<Card*> computerPile;
    
    std::vector<std::string> cardInputs;
    
    int ourRound=1;
    
};

#endif /* Deck_h */
