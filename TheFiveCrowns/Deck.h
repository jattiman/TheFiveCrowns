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
    void makeDeck();
    void printDecks();
    unsigned long getDeckSize(std::vector<Card*> cardPile);
    void printTheDeck(std::vector<Card*> cardPile);
    void shuffleDeck();
    
    // for reading in files, this will be useful
    void stringToCardInputs(std::string cardInputString);
    void testDeck(); // for debug only - delete before submission
    
    // to do:
    //  print player hands (based on player name input)
    //  check for runs in a hand
    //  check for

    
private:
    
    std::vector<Card*> mainDeck;
    std::vector<Card*> drawPile;
    std::vector<Card*> discardPile;
    
    std::vector<std::string> cardInputs;
    
    // debug. for array deck.
    // will most likely not use in lieu of vectors
    Card *cards[116];
};

#endif /* Deck_h */
