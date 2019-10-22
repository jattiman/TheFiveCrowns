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
    void dealDeck();

    void setRound(int roundInput);
    void setPlayerHand(std::vector<std::string> playerHand);
    //void setPlayerHand(std::vector<Card*> playerHand);
    void setComputerHand(std::vector<std::string> computerHand);
    //void setComputerHand(std::vector<Card*> computerHand);
    void setDrawPile(std::vector<std::string> drawHand);
    void setDiscardPile(std::vector<std::string> discardHand);
    
    
    int getRound();
    // make this more robust so all decks can be fed in at once
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
    bool transferCard(std::vector<Card*> &startPile, int startLocation, std::vector<Card*> &endPile);
    // to pull from Discard pile (will pull from back)
//    bool transferFromDiscard(std::vector<Card*> &startPile, std::vector<Card*> &endPile);
    bool transferFromDiscard(std::vector<Card*> &endPile);
    bool transferFromDraw(std::vector<Card*> & endPile);
    
    int countCardPoints(std::vector<Card*> & hand);
    
    // find a card
    int findCard(std::vector<Card*> & hand, std::string userSearch);
    
    // for reading in files, this will be useful
    void stringToCardInputs(std::string cardInputString);
    
    // to check for going out
    bool checkIfAllWild(std::vector<Card*> cardPile);
    int countWilds(std::vector<Card*> & cardPile);
    bool checkIfSameSuit(std::vector<Card*> cardPile);
    bool checkSuitRun(std::vector<Card*> & cardPile, int & numWilds);
    bool checkIfRun(std::vector<Card*> & cardPile, int & numWilds);
    bool checkIfBook(std::vector<Card*> & cardPile, int & numWilds);
    bool checkIfOut(std::vector<Card*> cardPile);
    
    std::string deckToString(std::vector<Card*> cardPile);
    std::string discardPileString(std::vector<Card*> cardPile);
    
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
    
    // player decks
    std::vector<Card*> humanPile;
    std::vector<Card*> computerPile;
    
    // book checking decks
    std::vector<Card*> humanBooks;
    std::vector<Card*> computerBooks;
    
    // run checking decks
    std::vector<Card*> humanRuns;
    std::vector<Card*> computerRuns;
    
    
    // garbage pile
    std::vector<Card*> garbagePile;
    
    std::vector<std::string> cardInputs;
    
    int ourRound=1;
    
};

#endif /* Deck_h */
