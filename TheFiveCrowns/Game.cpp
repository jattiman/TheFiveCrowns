/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/1/2019                                            *
 ***************************************************************
 */

#include "Game.h"
#include <iostream>
#include <vector>

using namespace std;

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received:
********************************************************************* */
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

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received:
********************************************************************* */
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

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received:
********************************************************************* */
int Game::getValidInput(int minNum, int maxNum){
    int userInput;
    while(!(cin >> userInput) || userInput < minNum || userInput > maxNum){
        cin.clear();
        cin.ignore(500,'\n');
        cout << "Please select a valid option." << endl;
    }
    return userInput;
}

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received:
********************************************************************* */
void Game::coinToss(){
    // to store user choice
    int userChoice;
    // to store random number
    unsigned seed;
    seed = (unsigned) std::chrono::system_clock::now().time_since_epoch().count();
    
    // toss the coin
    cout << "Coin toss time!" << endl
    << "Guess which side lands facing up!"<< endl
    << "1. Heads" << endl
    << "2. Tails" << endl;
    
    // intake user guess
    userChoice=this->getValidInput(1,2);
    
    // get the user hyped for the result!
    cout << "You look at the coin and see that it faces ... " << endl;
    cout << "\t(Press enter to see! Can you feel the anticipation?)";
    cin.ignore(100,'\n');
    cin.get();
    
    // display result to user
    if(seed%2==0){
        cout << "Heads!" << endl;
    }
    else{
        cout << "Tails!" << endl;
    }
    
    // tell user if they won or not, and set next up accordingly
    if(seed%2==(userChoice-1)){
        cout << "You guessed correctly! You're up first." << endl;
        // human goes first
        this->setNextUp(0);
    }
    else{
        cout << "You guessed incorrectly. Computer goes first." << endl;
        // computer goes first
        this->setNextUp(1);
    }
    cout << "\t(Press enter to continue! Wasn't that fun?)";
    cin.get();
    return;
}

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received:
********************************************************************* */
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
        
        // confirm user choice
        userOption=this->getValidInput(1,3);
        
        // If new game, start new game
        if(userOption==1){
            // if it's the first round, call coin toss to determine who goes first
            if(this->getRoundNumber()==1){
                this->coinToss();
            }
            // begin round
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
    // if the user didn't quit, and the round went past 11 (finished game), display end stats
    if(this->getRoundNumber()>11){
        this->displayEndStats();
    }
}

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received:
********************************************************************* */
void Game::beginRound(){
    this->round=new Round(h,c,roundNumber,this->getNextUp());
    // if round successful (no hard quit)
    if(this->round->startRound()!=4){
        // increment round number
        this->setRoundNumber(this->round->getRoundNumber());
        // set up next
        this->setNextUp(this->round->getTurn());
    }
    else{
        // ensure our round resets to 1
        this->setRoundNumber(1);
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

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received:
********************************************************************* */
bool Game::loadRound(){
    this->round = new Round(h,c);
    // if the game loads correctly
    if(this->round->loadGame()){
        // ensure round number transfers over
        this->setRoundNumber(this->round->getRoundNumber());
        // return that the program loaded
        return true;
    }
    // if the game didn't load right
    else{
        // reset the round to 1
        this->setRoundNumber(1);
        // return that the program did not load
        return false;
    }
}

//void Game::beginRound(HumanPlayer *h, ComputerPlayer *c, Deck * savedDeck, int roundNumber){
//    cout << "Starting round " << roundNumber << "." << endl;
//    this->round=new Round(h,c,savedDeck, roundNumber);
//    this->round->startRound();
//    return;
//}

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received:
********************************************************************* */
void Game::incrementRound(){
    // increment round number by 1
    this->roundNumber++;
    return;
}

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received:
********************************************************************* */
void Game::displayEndStats(){
    // let user know that the game is over, and display points
    cout << endl << endl
    << "Our game has ended!"
    << endl << endl
    << "Final stats:"
    << endl
    << "Human Player points: \t\t" << this->h->getPoints()
    << endl
    << "Computer Player points: \t" << this->c->getPoints()
    << endl << endl
    << "Winner: ";
    // output the winner based on who has lower points
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
    return;
}

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received:
********************************************************************* */
void Game::destroyStats(){
    this->h->setTotalPoints(0);
    this->c->setTotalPoints(0);
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
