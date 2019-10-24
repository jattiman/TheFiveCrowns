/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/22/2019                                            *
 ***************************************************************
 */

#include "Game.h"
#include <iostream>
#include <vector>

using namespace std;

/* *********************************************************************
Function Name: Game (constructor function)
Purpose: create game object
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
 Create human player
 Create computer player
 Set default round number to 1
Assistance Received: none
********************************************************************* */
Game::Game(){
    //this->round=new Round();
    this->h=new HumanPlayer();
    this->c=new ComputerPlayer();
    this->setRoundNumber(1);
}

/* *********************************************************************
Function Name: setRoundNumber
Purpose: setter for round number
Parameters:
 int newRound: holds the new round number
Return Value: none
Local Variables: none
Algorithm:
none. Sets the new round based on input, for encapsulation.
Assistance Received: none
********************************************************************* */
void Game::setRoundNumber(int newRound){
    this->roundNumber=newRound;
    return;
}

/* *********************************************************************
Function Name: setNextUp
Purpose: setter for next player up
Parameters:
 int nextPlayer: int holding next player number up
Return Value: none
Local Variables: none
Algorithm:
none. Sets the next player based on input, for encapsulation.
Assistance Received: none
********************************************************************* */
void Game::setNextUp(int nextPlayer){
    this->nextUp=nextPlayer;
}

/* *********************************************************************
Function Name: getRoundNumber
Purpose: gets the round number
Parameters:
 none
Return Value:
 int of round number
Local Variables: none
Algorithm:
none. returns the round number for encapulation purposes.
Assistance Received: none
********************************************************************* */
int Game::getRoundNumber(){
    return this->roundNumber;
}

/* *********************************************************************
Function Name: getNextUp
Purpose: gets the next player up
Parameters:
 none
Return Value:
 int of next player up
Local Variables: none
Algorithm:
none. returns the next player up for encapulation purposes.
Assistance Received: none
********************************************************************* */
int Game::getNextUp(){
    return this->nextUp;
}

/* *********************************************************************
Function Name: welcomeOptions
Purpose: display welcome options
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
 If it's past the first round, display "next round" as an option.
 If it's the first round display "new game" as an option
 Always display the option to load the game or quit
Assistance Received: None
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
Function Name: getValidInput
Purpose: to confirm the user doesn't blow up my program with invalid input
Parameters:
 ints minNum and maxNum, for optional checks on integer input (default values passed if needed)
 Note: I had some issues with cin.ignore() and cin.clear() sometimes causing the user to have to press enter twice. I think it might be due to not flushing the input stream properly somewhere else in the program.
Return Value:
 integer of the user input choice
Local Variables:
 userInput: int holding the user choice
Algorithm:
 while the user input fails, or doesn't fit within min/max boundaries, prompt the user to re-enter valid input
Assistance Received: A lot of research was done online to cin.fail() and other ways to handle invalid input that criss-crossed chars/strings/key commands when an int is needed, but no site in particular is to blame for the odd way I solved this.
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
Function Name: coinToss
Purpose: to toss a coin for the user/determine who goes first
Parameters: none
Return Value: none
Local Variables:
 int userChoice: holds user choice
 unsigned seed: needed for generating
Algorithm:
 create random "seed" number
 prompt user to guess a coin toss
 mod the seed result, and have the user guess if it landed on one side of the other.
 If the guess matches the seed mod, the user goes first. Otherwise, they don't.
Assistance Received: see Deck::shuffleDeck() for more information about the random shuffle generator that I used on the vector. What I learned there was greatly helpful in figuring out how to use chrono/system_clock to rely on a more random number
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
Function Name:welcome
Purpose: start the game and let the user choose from start/load/quit
Parameters: none
Return Value:none
Local Variables:
 int userOption: holds the user choice
Algorithm:
 Welcome prompt the user
 While the round number doesn't pass 11:
 Display choices, and get input
 If new game/next round, decide if coin toss is needed and play round accordingly (based on round number loaded)
 If load game, call functions to load game. If loading successful, continue to round. Otherwise, re-prompt the user.
 If quitting, thank the user and leave.
 
Assistance Received:
********************************************************************* */
void Game::welcome(){
    // stores the user's selected option
    int userOption = 0;
    
    // Welcome the player and prompt them to start a game
    cout << "Welcome to 5 Crowns!" << endl;
    
    // Loop until user quits or round number passes 11
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
Function Name:beginRound
Purpose: begins a round
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
 Create a new round object
 Pass human/computer players into it, along with round number and player order
 Start the round
 If the round is successful/not quit out of:
 set the next round number
 set the next player up
 If the round isn't successful (player quit):
 set the round number back to 1
Assistance Received: none
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

/* *********************************************************************
Function Name:loadRound
Purpose: load a round in
Parameters: none
Return Value: true or false
Local Variables: none
Algorithm:
 Create a new round object
 Attempt to load a game
 If the game loads successfully, set the round number in the game based on what gets returned
 If the game doesn't load successfully, set the round number to 1
Assistance Received: none
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

/* *********************************************************************
Function Name:incrementRound
Purpose: lazy "setter" to increment the round number by 1
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
 increment the round number variable in the game object by 1
Assistance Received: none
********************************************************************* */
void Game::incrementRound(){
    // increment round number by 1
    this->roundNumber++;
    return;
}

/* *********************************************************************
Function Name:displayEndStats
Purpose: display the statistics at the end of the game
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
 Output info to user confirming that the game has ended
 Print out the human and computer points
 Print out the winner/tie status
Assistance Received: None
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
Function Name: destroyStats
Purpose: destroys the total point stats of the players and resets the round number
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
 set human points to 0
 set computer points to 0
 set round number back to 1
 return
Assistance Received: none
********************************************************************* */
void Game::destroyStats(){
    this->h->setTotalPoints(0);
    this->c->setTotalPoints(0);
    this->setRoundNumber(1);
    return;
}

/* *********************************************************************
Function Name: testGame
Purpose: for testing - input whatever you want to test here and run it in main, or wherever
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
 nothing in here now. This is filled in during creation to save time
Assistance Received: none
********************************************************************* */
void Game::testGame(){
    //cout << "Testing game now..." << endl;
    //HumanPlayer *p = new HumanPlayer();
    //addPlayers(ourPlayers, p);
    return;
}
