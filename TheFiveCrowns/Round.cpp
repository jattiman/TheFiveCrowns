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
#include <sstream>
#include <regex>
// for loading files based on folder contents
#include <sys/types.h>
#include <dirent.h>


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

int Round::getHumanRoundPoints(){
    return this->humanRoundPoints;
}

int Round::getComputerRoundPoints(){
    return this->computerRoundPoints;
}

void Round::setRoundNumber(int newNumber){
    // sets the round number
    this->roundNumber=newNumber;
    return;
}
void Round::incrementTurn(){
    // increments the turn to progress the round
    this->nextTurn++;
    return;
}
void Round::incrementRound(){
    this->roundNumber++;
    return;
}
void Round::setTurn(int nextUp){
    // sets the turn to decide who goes next
    this->nextTurn=nextUp;
    return;
}

void Round::setHumanRoundPoints(int points){
    this->humanRoundPoints=points;
    return;
}

void Round::setComputerRoundPoints(int points){
    this->computerRoundPoints=points;
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
    return;
}

int Round::getValidInput(int minNum, int maxNum){
    int userInput;
    while(!(cin >> userInput) || userInput < minNum || userInput > maxNum){
        cin.clear();
        cin.ignore(500,'\n');
        cout << "Please select a valid option." << endl;
    }
    return userInput;
}

int Round::giveOptions(Player *p){
    int userChoice=0;
    // if player is human, give human options
    if(p->getHumanity()){
        do{
            cout << "Please choose from the following:" << endl
            << "\t1. Save the game" << endl
            << "\t2. Make a move" << endl
            << "\t3. Ask for help" << endl
            << "\t4. Quit the game" << endl;
            userChoice=this->getValidInput(1,4);
        } while(userChoice < 1 || userChoice > 4);
    }
    else{
        cout << "The computer is choosing its next action..." << endl
            << "\t1. Save the game" << endl
            << "\t2. Make a move" << endl
            << "\t3. Quit the game" << endl;
        cout << "Computer chooses to make a move. (It really has no choice, does it?)" << endl;
        userChoice=2;
    }
    
    return userChoice;
}

int Round::endRound(){
    cout << "Round ended successfully. Good job, everyone." << endl << endl;
     
    cout << "Setting round points ... " << endl;
    // set round points
    //this->setHumanRoundPoints(this->deck->countCardPoints(this->deck->getHumanDeck()));
    //this->setComputerRoundPoints(this->deck->countCardPoints(this->deck->getHumanDeck()));
    // add points to total player score
    
    for (auto i: ourPlayers){
        // if you're human AND not out
        if(i->getHumanity() && !(i->getIfOut())){
            cout << "Human leftover cards: ";
            this->setHumanRoundPoints(this->deck->tallyRemainingCardPoints(this->deck->getHumanDeck()));
            deck->printTheDeck(deck->getHumanDeck());
            cout << "Computer:\tAdding 0 points." << endl;
            cout << "Human:\t\tAdding " << this->getHumanRoundPoints() << " points." << endl;
            i->addPoints(this->getHumanRoundPoints());
        }
        // if you're a computer AND not out
        else if((!i->getHumanity()) && !(i->getIfOut())){
            cout << "Computer leftover cards: ";
            this->setComputerRoundPoints(this->deck->tallyRemainingCardPoints(this->deck->getComputerDeck()));
            deck->printTheDeck(deck->getComputerDeck());
            cout << "Computer:\tAdding " << this->getComputerRoundPoints() << " points." << endl;
            cout << "Human:\t\tAdding 0 points." << endl;
            i->addPoints(this->getComputerRoundPoints());
        }
    }
    
    // increment round number
    this->incrementRound();
    
    // if the game still isn't over after this round
    if(this->getRoundNumber()<12){
        // give a current total point standing
        cout << "Total points:"
        << endl
        << "\tComputer:\t" << ourPlayers[1]->getPoints()
        << endl
        << "\tHuman:\t\t" << ourPlayers[0]->getPoints()
        << endl << endl;
        
        // display who goes next
        cout << "Next player up: ";
        if(this->getHumanRoundPoints()>this->getComputerRoundPoints()){
             // if computer had lower points, they go next
             this->setTurn(1);
             cout << "Computer!" << endl << endl;
            return 1;
         }
        else{
             // if human had lower points, they go next
             this->setTurn(0);
             cout << "Human!" << endl << endl;
            return 0;
        }
    }
    return 0;
}

int Round::startRound(){
//    int answer = 0;
    int totalPlayers=this->getTotalPlayers();
    int ourTurn=this->getTurn();
    int roundResult=0;
    do{
        this->getRoundStatus();
        // begin the round progression, one player at a time
        roundResult=this->progressRound(this->ourPlayers[ourTurn%totalPlayers]);

        ourTurn++;
        this->incrementTurn();
        
        // if quit/progress loss confirmed
        if(roundResult==4){
            // delete ALL points and break from loop
            for (auto i: ourPlayers){
                i->deletePoints();
            }
            // reset round number if quitting
            this->setRoundNumber(1);
            break;
        }
        
        
        // while the NEXT player is still not out, keep going
        // this will cause the game to loop through all players once after
        // the first player goes out
    }while(!(this->ourPlayers[ourTurn%totalPlayers]->getIfOut()));
    // if the player didn't hard quit, tally points from round.
    if(roundResult!=4){
        roundResult=this->endRound();
    }
    cout << "The round is over." << endl;
    return roundResult;
}

int Round::progressRound(Player *p){
    while(true){
        switch (giveOptions(p)) {
            case 1:
                // attempt to save the game
                if(this->saveGame()){
                    cout << "File saved." << endl;
                }
                // if error encountered, display issue
                // (This shouldn't happen)
                else{
                    cout << "File could not be saved. Sorry, the game is broken." << endl;
                }
                continue;
            case 2:
                // have the player begin their move
                p->playRound(this->deck);
                // cycle to next player
                break;
            case 3:
                // give advice
                p->examineOptions(this->deck);
                // prompt player for action
                continue;
            case 4:
                // if the player confirms they want to quit
                if(p->confirmExit()){
                    p->setOut(true);
                    // send signal to hard-quit the game (no save)
                    return 4;
                }
                // if the player changes their mind
                else{
                    // prompt them again
                    continue;
                }
                break;
            default:
                // really hope this doesn't print during the demo!
                cout << "You shouldn't see this." << endl;
                continue;
        }
        break;
    }
    return 0;
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
    roundSaveFile << ourPlayers[1]->getPoints();
    roundSaveFile << endl;
    roundSaveFile << "\tHand: ";
    roundSaveFile << deck->deckToString(deck->getComputerDeck());
    roundSaveFile << endl << endl;
    roundSaveFile << "Human: ";
    roundSaveFile << endl;
    roundSaveFile << "\tScore: ";
    roundSaveFile << ourPlayers[0]->getPoints();
    roundSaveFile << endl;
    roundSaveFile << "\tHand: ";
    roundSaveFile << deck->deckToString(deck->getHumanDeck());
    roundSaveFile << endl << endl;
    roundSaveFile << "Draw Pile: ";
    roundSaveFile << deck->deckToString(deck->getDrawPile());
    roundSaveFile << endl << endl;
    roundSaveFile << "Discard Pile: ";
    roundSaveFile << deck->discardPileString(deck->getDiscardPile());
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

bool Round::loadPlayerOrder(std::string nextPlayer){
    // if you can find a human on the line
    if(nextPlayer.find("man")!=std::string::npos){
        // set human as the next player
        this->setTurn(0);
        return true;
    }
    // if there is no human found
    else{
        // make sure the computer goes next
        this->setTurn(1);
        return true;
    }
    return false;
}

bool Round::loadNums(std::string passedNums, char numChoice){
    // create variables to parse the string
    string numString=passedNums;
    // create variable to hold the point/round value
    int ourNumber=0;
    // create variable to ensure extra numbers aren't present on the line
    int numCheck=0;
    smatch matches;
    regex numberFinder("[\\d]{1,}");
    while(regex_search(numString, matches, numberFinder)){
        for(auto i:matches){
            //cout << " " << i << " ";
            ourNumber=stoi(i);
            numString=matches.suffix().str();
            numCheck++;
        }
    }
    if(numCheck>1){
        cout << "numCheck is: " << numCheck << endl;
        cout << "Too many numbers - invalid" << endl;
        return false;
    }
    if(numChoice=='r'){
        if(ourNumber>11 || ourNumber <1){
            cout << "Proposed round number is illegal." << endl;
            return false;
        }
        this->setRoundNumber(ourNumber);
        return true;
    }
    if(numChoice=='h'){
        //cout << "human points: " << ourNumber << endl;
        this->ourPlayers[0]->setTotalPoints(ourNumber);
        return true;
    }
    if(numChoice=='c'){
        //cout << "computer points: " << ourNumber << endl;
        this->ourPlayers[1]->setTotalPoints(ourNumber);
        return true;
    }
    return false;
}

bool Round::loadCards(std::string passedHand, char deckChoice){
    // create variables to parse the string
    string cardString=passedHand;
    // create a vector to hold card face strings
    vector<string> cardValues;
    // create a regex match system that ensures only cards in the right format will be accepted
    smatch matches;
    regex cards("([123456789XQKJ][1234CHTSD])");
    sregex_iterator cardIterator(cardString.begin(), cardString.end(), cards);
    sregex_iterator empty;
    while(cardIterator!=empty){
        matches=*cardIterator;
        cardValues.push_back(matches.str());
        cardIterator++;
    }
    if(deckChoice=='h'){
        //cout << "Assigning Human Deck: ";
        this->deck->setPlayerHand(cardValues);
        //this->deck->printTheDeck(this->deck->getHumanDeck());
        return true;
    }
    if(deckChoice=='c'){
        //cout << "Assigning Computer Deck: ";
        this->deck->setComputerHand(cardValues);
        //this->deck->printTheDeck(this->deck->getComputerDeck());
        return true;
    }
    if(deckChoice=='D'){
        //cout << "Assigning Draw Deck: ";
        this->deck->setDrawPile(cardValues);
        //this->deck->printTheDeck(this->deck->getDrawPile());
        return true;
    }
    if(deckChoice=='d'){
        //cout << "Assigning Discard: ";
        this->deck->setDiscardPile(cardValues);
        //this->deck->displayDiscardTop();
        return true;
    }
    cout << "Card loading issue." << endl;
    return false;
}

bool Round::loadFileStats(std::vector<std::string> passedHand){
    // confirm serialized file was created with correct entries
    if(!(passedHand.size()==10)){
        cout << "Save file incomplete." << endl;
        return false;
    }
    
    // check and set round number
    if(!(this->loadNums(passedHand[0],'r'))){
        return false;
    }
    // create placeholder deck based on round number
    this->deck = new Deck(this->getRoundNumber());
    
    // load computer score
    if(!(this->loadNums(passedHand[2],'c'))){
        return false;
    }
    
    //load computer hand
    if(!(this->loadCards(passedHand[3],'c'))){
        return false;
    }
    
    //load human score
    if(!(this->loadNums(passedHand[5],'h'))){
        return false;
    }
    
    // load human hand
    if(!(this->loadCards(passedHand[6],'h'))){
        return false;
    }
    
    // load draw pile
    if(!(this->loadCards(passedHand[7],'D'))){
        return false;
    }
    
    // load discard pile
    if(!(this->loadCards(passedHand[8],'d'))){
        return false;
    }
    
    // load next player up
    if(!(this->loadPlayerOrder(passedHand[9]))){
        return false;
    }
    
    return true;
}


bool Round::loadGame(){
    // hold the save game file path selection
    string userFilePath;
    // variable for each line in the file
    string fileLine;
    // for opening and closing of file
    ifstream loadedFile;
    // for listing files in the directory
    vector<string> ourFiles;
    // for each line of the file to be loaded
    vector<string> fileStrings;
    // for confirming numerical order of files in the directory
    int fileCount=0;
    // holds user choice for prompts
    int userChoice=0;
    
    // ask user if they want to drop in a specific file or pick from the directory
    do{
        cout << "Would you like to load a specific file, or select from the directory?" << endl
            << "1. Load from new file." << endl
            << "2. Load from current save." << endl;
        userChoice = this->getValidInput(1,2);
    }while(userChoice !=1 && userChoice !=2);
    
    // if the user wants to drop a file, let them drop the full path
    if(userChoice==1){
        cout << "Place your save game file path here: ";
        
        cin.clear();
        cin.ignore();
        getline(cin,userFilePath);
        //cout << endl << "File path shows as: " << userFilePath << endl;
        
    }
    // if the user wants to select from the directory, display .txt files present
    if(userChoice==2){
        // help for this function is from here: https://stackoverflow.com/questions/12976733/how-can-i-get-only-txt-files-from-directory-in-c
        
        // declare and open directory for files (game defined)
        // note: chosen file name will be appended to the end of this
        //       directory
        DIR* ourDirectory = opendir("/Users/jatti/Library/Developer/Xcode/DerivedData/TheFiveCrowns-gyhwmffbzuwqphcsgssaygxsygkp/Build/Products/Debug/");
        // declare directory iteration info
        struct dirent * dp;
        // while the directory isn't empty
        while ((dp = readdir(ourDirectory)) != NULL) {
            // if the file is a .txt, push to vector
            size_t fileLength = strlen(dp->d_name);
            if(fileLength > 4 && strcmp((dp->d_name + fileLength - 4), ".txt")==0){
                ourFiles.push_back(dp->d_name);
            }
        }
        // close the directory
        closedir(ourDirectory);
        
        // prompt user to select from file list
        do{
            cout << "Select file from below: " << endl;
            // iterate through list, and display with corresponding file count #
            for(auto i: ourFiles){
                fileCount++;
                cout << fileCount << ": " << i << endl;
            }
            // reset the file count number in case loop is repeated
            fileCount=0;
            // take in user choice and confirm it's valid
            userChoice=this->getValidInput(1,(int)ourFiles.size());
        }while(userChoice < 1 || userChoice > ourFiles.size());
        // decrement choice for correct vector index access
        userChoice--;
        // append specific file name to path 
        userFilePath+=ourFiles[userChoice];
    }
    // attempt to open the file
    loadedFile.open(userFilePath.c_str());
    // if error, display the error and let user try again from
    if(!loadedFile){
        cout << "File not found." << endl;
        return false;
    }
    // if no error, iterate through the file and pull variables
    
    // iterate through each line of the file
    
    while(getline(loadedFile,fileLine)){
        istringstream fileStream(fileLine);
        // confirm we only read in lines with data
        if(fileLine.find(':')!=std::string::npos){
            fileStrings.push_back(fileLine);
        }
        
    }
//    int debugCount=0;
//    cout << "Printing our file ... " << endl;
//    for (auto i:fileStrings){
//        cout << debugCount << i << endl;
//        debugCount++;
//    }
    
    
    //close the file and start the round
    loadedFile.close();
    if(!this->loadFileStats(fileStrings)){
        cout << "File load issue." << endl;
        return false;
    }
    cout << "Game loaded." << endl;
    //this->startRound();
    return true;
}

void Round::clearPoints(){
    for(auto i: ourPlayers){
        i->deletePoints();
    }
}

void Round::roundTest(){
    cout << "\tRound Test" << endl;
    return;
}
