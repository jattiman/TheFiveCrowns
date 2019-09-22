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
    this->round=new Round();
    this->h=new HumanPlayer();
    this->c=new ComputerPlayer();
}

//void addPlayers(std::vector<Player*> &ourPlayers, Player *p){
//    cout << "Adding human player." << endl;
//    ourPlayers.push_back(p);
//    return;
//}

void Game::incrementRoundNumber(){
    roundNumber+=1;
    return;
}

void Game::welcome(){
    // stores the user's selected option
    int userOption = 0;
    
    // Welcome the player and prompt them to start a game
    cout << "Welcome to 5 Crowns!" << endl;
    
    // may need to look into cin.fail for error checking
    // Loop until user quits
    while(true){
        cout << "Select your option:" << endl
        << "\t1. New game" << endl
        << "\t2. Load game"<< endl
        << "\t3. Quit" << endl;
        
        //cin.sync();
        cin >> userOption;
        
        // If new game, start new game
        if(userOption==1){
            //this->beginRound();
            this->beginRound(h, c, roundNumber);
            this->incrementRoundNumber();
            //break;
        }
        
        // If loading game, select game file to load and begin game
        else if(userOption==2){
            cout << "Loading game from file ... " << endl;
            break;
        }

        // If quit, exit
        else if(userOption==3){
            cout << "Thank you for playing. Good bye!" << endl;
            break;
        }
        else{
            // Will need to add error checking here
            cout << "Catastrophic error." << endl;
        }
        
    }
}

// We'll most likely get rid of this one
void Game::beginRound(){
    cout << "Starting new game." << endl;
    //this->round->setupRound();
    this->round->displayPrompt();
}

// To do: transfer the players in as a vector/array/etc to better handle
//          more than 2 players.
void Game::beginRound(HumanPlayer *h, ComputerPlayer *c, int roundNumber){
    this->round->setupRound(h,c,roundNumber);
    this->round->displayPrompt();
    
    // this is a good of place as any to test game functions
    testGame();
    
}

// test function

void Game::testGame(){
    //cout << "Testing game now..." << endl;
    //HumanPlayer *p = new HumanPlayer();
    //addPlayers(ourPlayers, p);
    return;
}
