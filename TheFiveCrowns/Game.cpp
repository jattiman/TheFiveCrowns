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

#include "Game.h"
#include <iostream>
#include <vector>

using namespace std;

Game::Game(){
    //this->round=new Round();
    this->h=new HumanPlayer();
    this->c=new ComputerPlayer();
    this->setRoundNumber(1);
}

void Game::setRoundNumber(int newRound){
    this->roundNumber=newRound;
    return;
}

void Game::setNextUp(int nextPlayer){
    this->nextUp=nextPlayer;
}

int Game::getRoundNumber(){
    return this->roundNumber;
}

int Game::getNextUp(){
    return this->nextUp;
}

void Game::welcomeOptions(){
    if(this->getRoundNumber()>1){
        cout << "Select your option:" << endl
        << "\t1. Next round" << endl
        << "\t2. Load game"<< endl
        << "\t3. Quit" << endl;
    }
    else{
        cout << "Select your option:" << endl
        << "\t1. New game" << endl
        << "\t2. Load game"<< endl
        << "\t3. Quit" << endl;
    }
    return;
}

int Game::getValidInput(int minNum, int maxNum){
    int userInput;
    while(!(cin >> userInput) || userInput < minNum || userInput > maxNum){
        cin.clear();
        cin.ignore(500,'\n');
        cout << "Please select a valid option." << endl;
    }
    return userInput;
}

void Game::coinToss(){
    int userChoice;
    unsigned seed;
    seed = (unsigned) std::chrono::system_clock::now().time_since_epoch().count();
    
    cout << "Coin toss time!" << endl
    << "Guess which side lands facing up!"<< endl
    << "1. Heads" << endl
    << "2. Tails" << endl;
    
    userChoice=this->getValidInput(1,2);
    
    cout << "You look at the coin and see that it faces ... " << endl;
    cout << "(Press enter to see! Can you feel the anticipation?)";
    cin.ignore(100,'\n');
    cin.get();
    
    if(seed%2==0){
        cout << "Heads!" << endl;
    }
    else{
        cout << "Tails!" << endl;
    }
    
    if(seed%2==(userChoice-1)){
        cout << "You guessed correctly! You're up first." << endl;
        this->setNextUp(0);
    }
    else{
        cout << "You guessed incorrectly. Computer goes first." << endl;
        this->setNextUp(1);
    }
    cout << "(Press enter to continue! Wasn't that fun?)";
    cin.get();
    return;
}

void Game::welcome(){
    // stores the user's selected option
    int userOption = 0;
    
    
    // Welcome the player and prompt them to start a game
    cout << "Welcome to 5 Crowns!" << endl;
    
    // may need to look into cin.fail for error checking
    // Loop until user quits
    while(this->getRoundNumber()<12){
        // prompt for options
        this->welcomeOptions();
                
//        while(!(cin >> userOption)){
//            cin.clear();
//            cin.ignore(100,'\n');
//            cout << "Please select a valid option." << endl;
//            this->welcomeOptions();
//        }
        userOption=this->getValidInput(1,3);
        // If new game, start new game
        if(userOption==1){
            // if it's the first round, call coin toss to determine who goes first
            if(this->getRoundNumber()==1){
                this->coinToss();
            }
            // otherwise, go with the winner from last round
                        
            this->beginRound();
            
            // return from round
            // reset player out status to prepare for next round.
            this->h->setOut(false);
            this->c->setOut(false);
        }
        
        // If loading game, select game file to load and begin game
        else if(userOption==2){
            // reset stats, since loading game
            this->destroyStats();
            // if load is successful, run loaded round
            if(this->loadRound()){
                // reset key variables to ensure next round can run
                this->h->setOut(false);
                this->c->setOut(false);
                this->round->startRound();
                // increment round number in case player wants to progress
                this->setRoundNumber(this->round->getRoundNumber());
//                cout << "Round ended and we're back in choice 2:"
//                << "\t GAME round number: " << this->getRoundNumber()
//                << "\t ROUND round number: " << this->round->getRoundNumber()
//                << endl;
            }
            else{
                cout << "Load file failed." << endl;
                
            }
            //break;
        }

        // If quit, exit
        else if(userOption==3){
            cout << "Thank you for playing. Good bye!" << endl;
            break;
        }
        else{
            // Will need to add error checking here
            cout << "Please enter a valid option." << endl;
        }
        
    }
    this->displayEndStats();
}

void Game::beginRound(){
    this->round=new Round(h,c,roundNumber,this->getNextUp());
    // if round successful (no hard quit)
    if(this->round->startRound()!=4){
        // increment round number
//        this->incrementRound();
//        cout << "\t\tRound ended. Incrementing round number to: ";
        this->setRoundNumber(this->round->getRoundNumber());
//        cout << this->getRoundNumber() << endl;
        // set up next
        this->setNextUp(this->round->getTurn());
    }
    return;
}

// To do: transfer the players in as a vector/array/etc to better handle
//          more than 2 players.
//void Game::beginRound(HumanPlayer *h, ComputerPlayer *c, int roundNumber){
//    cout << "Starting round " << roundNumber << "." << endl;
//    this->round=new Round(h,c,roundNumber);
//    this->round->startRound();
//    return;
//}

bool Game::loadRound(){
    this->round = new Round(h,c);
    if(this->round->loadGame()){
        this->setRoundNumber(this->round->getRoundNumber());
        
        return true;
    }
    else{
        return false;
    }
}

//void Game::beginRound(HumanPlayer *h, ComputerPlayer *c, Deck * savedDeck, int roundNumber){
//    cout << "Starting round " << roundNumber << "." << endl;
//    this->round=new Round(h,c,savedDeck, roundNumber);
//    this->round->startRound();
//    return;
//}

void Game::incrementRound(){
    this->roundNumber++;
    
    return;
}

void Game::displayEndStats(){
//    if(this->roundNumber >11){
        cout << "This game has ended. Final stats:" << endl
        << "Human Player points: " << this->h->getPoints()
        << endl
        << "Computer Player points: " << this->c->getPoints()
        << endl
        << "Winner: ";
        if(this->h->getPoints() < this->c->getPoints()){
            cout << "Human player."
            << endl
            << "Good job!";
        }
        else if (this->c->getPoints() < this->h->getPoints()){
            cout << "Computer player."
            << endl
            << "Better luck next time!";
        }
        else{
            cout << "Tie game. Well, that's exciting, isn't it?";
        }
        cout << endl;
//    }
    return;
}

void Game::destroyStats(){
    this->h->setPoints(0);
    this->c->setPoints(0);
    this->setRoundNumber(1);
    return;
}

// test function

void Game::testGame(){
    //cout << "Testing game now..." << endl;
    //HumanPlayer *p = new HumanPlayer();
    //addPlayers(ourPlayers, p);
    return;
}
