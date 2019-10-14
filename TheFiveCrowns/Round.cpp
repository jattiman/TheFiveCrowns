/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/1/2019                                            *
 ***************************************************************
 */

#include "Round.h"

//For printing statements to screen
#include <iostream>
//For file read/write
#include <fstream>

using namespace std;

Round::Round(){
    // set default round number
    this->setRoundNumber(1);
    // create the deck with the default round number
    this->deck = new Deck(this->getRoundNumber());
    this->setTurn(0);
}

Round::~Round(){
    // debug print once round destroyed
    cout << "\t\tRound ended." << endl;
}

Round::Round(HumanPlayer *h, ComputerPlayer *c){
    // constructor to be called when loading a game
    // set round number to 1 if none specified
//    this->setRoundNumber(1);
    // create the deck with this round number
//    this->deck = new Deck(this->getRoundNumber());
    // create player objects
    this->setupPlayers(h,c);
    // set up who goes first (default)
//    this->setTurn(0);
}

Round::Round(HumanPlayer *h, ComputerPlayer *c, int round, int whosTurn){
    // set round number to round specified
    this->setRoundNumber(round);
    // create deck with that round
    this->deck = new Deck(this->getRoundNumber());
    // set up player objects
    this->setupPlayers(h,c);
    // set up who goes first
    this->setTurn(whosTurn);
}

void Round::setupPlayers(HumanPlayer *h, ComputerPlayer *c){
    // push back players to vector, for future shuffling
    this->ourPlayers.push_back(h);
    this->ourPlayers.push_back(c);
}

int Round::getRoundNumber(){
    // return round number
    return roundNumber;
}

int Round::getTurn(){
    // return whose round it is next
    return nextTurn;
}

int Round::getTotalPlayers(){
    // calculate the total number of players in the round
    return (int)this->ourPlayers.size();
}

Deck Round::getDeck(){
    // return the round's deck
    return *deck;
}

void Round::setRoundNumber(int newNumber){
    // sets the round number
    this->roundNumber=newNumber;
    return;
}
void Round::setTurn(){
    // increments the turn to progress the round
    this->nextTurn++;
    return;
}
void Round::setTurn(int nextUp){
    // sets the turn to decide who goes next
    this->nextTurn=nextUp;
    return;
}

void Round::giveComputerStatus(std::vector<Player*> players){
    // iterate through the player vector
    for(auto &i: players){
        // if computer, print computer info
        if(!(i->getHumanity())){
            cout << "Computer:" << endl
                << "\tScore: " << i->getPoints() << endl
                << "\tHand: ";
                this->deck->printTheDeck(this->deck->getComputerDeck());
                cout << endl;
            }
    }
    return;
    
}
void Round::giveHumanStatus(std::vector<Player*> players){
    // iterate through the vector
    for(auto &i: players){
        // if human, print human player info
        if(i->getHumanity()){
            cout << "Human:" << endl
            << "\tScore: " << i->getPoints() << endl
            << "\tHand: ";
            //this->deck->getHumanDeck();
            this->deck->printTheDeck(this->deck->getHumanDeck());
            cout << endl;
        }
    }
    return;
    
}

void Round::givePlayerStatus(std::vector<Player*> players){
    // iterate through the vector of players
    for(auto &i: players){
        // if human, print human player info
        if(i->getHumanity()){
            cout << "Human:" << endl
            << "\tScore: " << i->getPoints() << endl
            << "\tHand: ";
            //this->deck->getHumanDeck();
            this->deck->printTheDeck(this->deck->getHumanDeck());
            cout << endl;
        }
        // if computer, print computer player info
        else{
            cout << "Computer:" << endl
            << "\tScore: " << i->getPoints() << endl
            << "\tHand: ";
            this->deck->printTheDeck(this->deck->getComputerDeck());
            cout << endl;
        }
    }
    return;
    
}

void Round::getRoundStatus(){
    // display the round number
    cout << "Round: " << this->getRoundNumber() << endl
        << endl;
    // display the player stats for the round
    this->givePlayerStatus(this->ourPlayers);
    // print the draw and discard piles
    this->deck->printDecks();
    cout << endl;
    return;
}

int Round::giveOptions(Player *p){
    int userChoice=0;
    // if player is human, give human options
    if(p->getHumanity()){
        do{
            cout << "Please choose from the following:" << endl
            << "\t1. Save the game" << endl
            << "\t2. Make a move" << endl
            << "\t3. Ask for help (only before human player plays)" << endl
            << "\t4. Quit the game" << endl;
            cin >> userChoice;
        } while(userChoice < 1 || userChoice > 4);
    }
    else{
        cout << "The computer is choosing its next action..." << endl
            << "\t1. Save the game" << endl
            << "\t2. Make a move" << endl
            << "\t3. Quit the game" << endl;
        cout << "Computer chooses: 2 (hard coded)" << endl;
        userChoice=2;
    }
    
    return userChoice;
}



void Round::startRound(){
    
//    int answer = 0;
    int totalPlayers=this->getTotalPlayers();
    int ourTurn=this->getTurn();
    
    do{
        this->getRoundStatus();
        // begin the round progression, one player at a time
        progressRound(this->ourPlayers[ourTurn%totalPlayers]);
        ourTurn++;
        this->setTurn();
        
        // while the NEXT player is still not out, keep going
        // this will cause the game to loop through all players once after
        // the first player goes out
    }while(!(this->ourPlayers[ourTurn%totalPlayers]->getIfOut()));
    for (auto i: ourPlayers){
        if(i->getHumanity()){
            i->setPoints(this->deck->countCardPoints(this->deck->getHumanDeck()));
        }
        else{
            i->setPoints(this->deck->countCardPoints(this->deck->getComputerDeck()));
        }
    }
    cout << "Round is over. Would you like to progress?" << endl;
    return;
}

void Round::progressRound(Player *p){
    while(true){
        switch (giveOptions(p)) {
            case 1:
                //p->saveGame();
                if(this->saveGame()){
                    cout << "File saved." << endl;
                }
                else{
                    cout << "File could not be saved. Sorry, the game is broken." << endl;
                }
                continue;
            case 2:
                p->playRound(this->deck);
                break;
            case 3:
                p->examineOptions();
                continue;
            case 4:
                if(p->confirmExit()){
                    p->setOut(true);
                }
                break;
            default:
                cout << "You shouldn't see this." << endl;
                continue;
        }
        break;
    }
    return;
}

bool Round::saveGame(){
    
    ofstream roundSaveFile("roundSaveFile.txt");
    //roundSaveFile.open("roundSaveFile.txt");
    if(!roundSaveFile){
        cout << "Error opening file." << endl;
        return false;
    }
    cout << "Writing information to file ..." << endl;
    roundSaveFile << "Round: " << this->roundNumber;
    roundSaveFile << endl << endl;
    roundSaveFile << "Computer: ";
    roundSaveFile << endl;
    roundSaveFile << "\tScore: ";
    this->ourPlayers[1]->setPoints(1);
    roundSaveFile << ourPlayers[1]->getPoints();
    roundSaveFile << endl;
    roundSaveFile << "\tHand: ";
    roundSaveFile << deck->deckToString(deck->getComputerDeck());
    roundSaveFile << endl << endl;
    roundSaveFile << "Human: ";
    roundSaveFile << endl;
    roundSaveFile << "\tScore: ";
    this->ourPlayers[0]->setPoints(5);
    roundSaveFile << ourPlayers[0]->getPoints();
    roundSaveFile << endl;
    roundSaveFile << "\tHand: ";
    roundSaveFile << deck->deckToString(deck->getHumanDeck());
    roundSaveFile << endl << endl;
    roundSaveFile << "Draw Pile: ";
    roundSaveFile << deck->deckToString(deck->getDrawPile());
    roundSaveFile << endl << endl;
    roundSaveFile << "Discard Pile: ";
    roundSaveFile << deck->deckToString(deck->getDiscardPile());
    roundSaveFile << endl << endl;
    roundSaveFile << "Next Player: ";
    // write which player is CURRENTLY going, so the file knows who to select
    if(this->getTurn()%this->totalPlayers==0){
        roundSaveFile << "Human";
    }
    else{
        roundSaveFile << "Computer";
    }
    return true;
}

bool Round::loadGame(){
    string userFilePath;
    ifstream loadedFile;
    cout << "Copy your save game file path here: ";
    cin.clear();
    getline(cin,userFilePath);
    loadedFile.open(userFilePath.c_str());
    if(!loadedFile){
        cout << "File not found." << endl;
        return false;
    }
    // remember: loading path:
    // /Users/jatti/Library/Developer/Xcode/DerivedData/TheFiveCrowns-gyhwmffbzuwqphcsgssaygxsygkp/Build/Products/Debug/roundSaveFile.txt
    // regex through the file
    // if round reached
        // read in int
        // confirm int is > 0 and < 12
        // set round number based on that
    this->setRoundNumber(10);
    this->deck = new Deck(this->getRoundNumber());
    // search to see if "computer" reached
        // if no "Computer:" return false
    // search if "score" reached
        // if no "Score:" return false
    this->ourPlayers[1]->setPoints(10);
        // else update computer score
    // search if "hand" reached
        // if next entry is 2 characters long
        // if entry
        // TRY update each hand string to new vector
        // if invalid hand, display error and return false
    // if "human" reached
    // if "score" reached
    this->ourPlayers[0]->setPoints(1);
    // if "hand" reached
    
    this->setTurn(1);
    cout << "Game loaded. Starting round." << endl;
    this->startRound();
    return true;
}

void Round::roundTest(){
    cout << "\tRound Test" << endl;
    // Confirm we can print the deck
    //cout << "Printing the deck." << endl;
    //this->deck->printDecks();
    
    // Confirm that we can print a PLAYER deck
    // NOTE: I'll need to redo this. We don't want to mirror the deck
    //      for each player. Instead, we want to put ownership in the cards
    //      themselves, so they can pull up the player info.
//    cout << "Printing human player deck." << endl;
//    this->human->setDeck(this->deck);
//    this->human->showHand();
    return;
}
