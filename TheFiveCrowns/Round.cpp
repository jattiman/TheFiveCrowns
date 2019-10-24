/*
 ***************************************************************
 * Name:  John Atti                                            *
 * Project:  5Crowns C++ Project 1                             *
 * Class:  CMPS 366 01 - Organization of Programming Languages *
 * Date:  10/22/2019                                            *
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

/* *********************************************************************
Function Name: Round
Purpose: constructor - unused
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
 Set round number to 1
 Make a new deck with that round number.
 Set default turn to 0 (human)
Assistance Received:
********************************************************************* */
Round::Round(){
    // set default round number
    this->setRoundNumber(1);
    // create the deck with the default round number
    this->deck = new Deck(this->getRoundNumber());
    // set turn to 0 (human)
    this->setTurn(0);
}

/* *********************************************************************
Function Name: ~Round
Purpose: deconstructor - mostly unused
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
 Deconstructor for the round class. I never implemented anything fancy here. Sorry.
Assistance Received: None.
********************************************************************* */
Round::~Round(){
    // debug print once round destroyed
    cout << "\t\tRound ended." << endl;
}

/* *********************************************************************
Function Name:Round
Purpose: constructor - unused
Parameters:
 h: human player object
 c: computer player object
Return Value: none
Local Variables: none
Algorithm:
 Set up human and computer players based on setter function
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name:Round
Purpose: The constructor that is actually called by this program
Parameters:
 HumanPlayer *h: our human player object, passed in
 ComputerPlayer *c: computer player object, passed in
 int round: the round number
 int whosTurn: next player
Return Value: none
Local Variables: none
Algorithm:
 Set round number based on input
 Set up deck based on round number
 Set up players based on input
 Set who goes first (defaults to human)
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received:
********************************************************************* */
void Round::setupPlayers(HumanPlayer *h, ComputerPlayer *c){
    // push back players to vector, for future shuffling
    this->ourPlayers.push_back(h);
    this->ourPlayers.push_back(c);
}

/* *********************************************************************
Function Name:getRoundNumber
Purpose: returns round number
Parameters: none
Return Value: int for round number
Local Variables: none
Algorithm:
 Returns int representing round number. Getter.
Assistance Received: None.
********************************************************************* */
int Round::getRoundNumber(){
    // return round number
    return roundNumber;
}

/* *********************************************************************
Function Name:getTurn
Purpose: gets turn to help decide player that goes next
Parameters: none
Return Value: integer representing nextTurn variable, used to help who goes up next
Local Variables: none
Algorithm:
 Returns the nextTurn class variable, which is used to determine who is up next
Assistance Received: none
********************************************************************* */
int Round::getTurn(){
    // return whose round it is next
    return nextTurn;
}

/* *********************************************************************
Function Name:getTotalPlayers
Purpose: return total number of players playing
Parameters: none
Return Value: integer representing total players
Local Variables: none
Algorithm:
 All at once:
 Get the vector size containing the players (will always be 2 for this version of the game, but when more players are added, this will be useful)
 Cast it at an int
 Return that value
Assistance Received: none
********************************************************************* */
int Round::getTotalPlayers(){
    // calculate the total number of players in the round
    return (int)this->ourPlayers.size();
}

/* *********************************************************************
Function Name:getDeck
Purpose: return the deck - unused
Parameters: none
Return Value: Deck
Local Variables: none
Algorithm:
 Retuns the deck object of the round.
Assistance Received: none
********************************************************************* */
Deck Round::getDeck(){
    // return the round's deck
    return *deck;
}

/* *********************************************************************
Function Name:getHumanRoundPoints
Purpose: Gets the total points for the human in the round
Parameters: none
Return Value: int of human points
Local Variables: none
Algorithm:
 Returns humanRoundPoints int
Assistance Received: none
********************************************************************* */
int Round::getHumanRoundPoints(){
    return this->humanRoundPoints;
}

/* *********************************************************************
Function Name:getComputerRoundPoints
Purpose: Gets the total points for the computer in the round
Parameters: none
Return Value: int of computer points
Local Variables: none
Algorithm:
 Returns computerRoundPoints int
Assistance Received: none
********************************************************************* */
int Round::getComputerRoundPoints(){
    return this->computerRoundPoints;
}

/* *********************************************************************
Function Name:setRoundNumber
Purpose: sets the round number
Parameters:
 int newNumber: int for new round number
Return Value: none
Local Variables: none
Algorithm:
 Sets roundNumber based on input. Setter.
Assistance Received: none.
********************************************************************* */
void Round::setRoundNumber(int newNumber){
    // sets the round number
    this->roundNumber=newNumber;
    return;
}

/* *********************************************************************
Function Name:incrementTurn
Purpose: increments the turn variable by one
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
 Increment nextTurn by 1
Assistance Received: none
********************************************************************* */
void Round::incrementTurn(){
    // increments the turn to progress the round
    this->nextTurn++;
    return;
}

/* *********************************************************************
Function Name:incrementRound
Purpose: increment round number by 1
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
 Increments the roundNumber variable by 1
Assistance Received: none
********************************************************************* */
void Round::incrementRound(){
    this->roundNumber++;
    return;
}

/* *********************************************************************
Function Name:setTurn
Purpose: sets the turn number
Parameters:
 int nextUp: reflects turn number
Return Value: none
Local Variables: none
Algorithm:
 Sets nextTurn to the input. Setter.
Assistance Received: none.
********************************************************************* */
void Round::setTurn(int nextUp){
    // sets the turn to decide who goes next
    this->nextTurn=nextUp;
    return;
}

/* *********************************************************************
Function Name:setHumanRoundPoints
Purpose: sets human round points (not total points)
Parameters:
 int points: new points to be put in
Return Value: none
Local Variables: none
Algorithm:
 Sets humanRoundPoints based on input
Assistance Received: none
********************************************************************* */
void Round::setHumanRoundPoints(int points){
    this->humanRoundPoints=points;
    return;
}

/* *********************************************************************
Function Name:setComputerRoundPoints
Purpose: sets computer round points (not total points)
Parameters:
 int points: new points to be put in
Return Value: none
Local Variables: none
Algorithm:
 Sets computerRoundPoints based on input
Assistance Received: none
********************************************************************* */
void Round::setComputerRoundPoints(int points){
    this->computerRoundPoints=points;
    return;
}

/* *********************************************************************
Function Name:giveComputerStatus
Purpose: prints computer score info
Parameters: players vector, holding human and computer players
Return Value: none
Local Variables: none (aside from auto iterator)
Algorithm:
 If the player isn't human, output the point info and hand
 Note: this is inefficient, and will be made better on the next version.
Assistance Received: None
********************************************************************* */
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

/* *********************************************************************
Function Name:giveHumanStatus
Purpose: prints human score info
Parameters: players vector, holding human and computer players
Return Value: none
Local Variables: none (aside from auto iterator)
Algorithm:
 If the player is human, output the point info and hand
 Note: this is inefficient, and will be made better on the next version.
Assistance Received: None
********************************************************************* */
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

/* *********************************************************************
Function Name:givePlayerStatus
Purpose: give point info for all players
Parameters: players vector
Return Value: none
Local Variables: none aside from auto iterator
Algorithm:
 For each index in the players vector
 Output player score info and hand.
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name:getRoundStatus
Purpose: display the round status
Parameters: none
Return Value: none
Local Variables: none
Algorithm:
 Display round information
 Call player status functions to display player status info
 Print deck info
Assistance Received: none
********************************************************************* */
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
int Round::getValidInput(int minNum, int maxNum){
    int userInput;
    while(!(cin >> userInput) || userInput < minNum || userInput > maxNum){
        cin.clear();
        cin.ignore(500,'\n');
        cout << "Please select a valid option." << endl;
    }
    return userInput;
}

/* *********************************************************************
Function Name:giveOptions
Purpose: displays options for player or computer
Parameters: player object (human or computer)
Return Value: int of userChoice
Local Variables:
 int userChoice: holds user choice
Algorithm:
 Check user's humanity, display prompt, and take input accordingly.
Assistance Received: none
********************************************************************* */
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
    // otherwise, output computer options
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

/* *********************************************************************
Function Name:endRound
Purpose: display end round info for successful round ending
Parameters: none
Return Value: integer based on which player goes next
Local Variables:
 none
Algorithm:
 Output that round ended and that points will be displayed
 Calculate round points based on player out status
 Increment round number
 If the game isn't over, give current point standing and who goes next
 
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name: startRound
Purpose: starts the round
Parameters: none
Return Value: integer based on detected round result
Local Variables:
 totalPlayers: int of total players in round
 ourTurn: int displaying who is up next, based on getTurn
 roundResult: int displaying the code of the round result
Algorithm:
 Display rund status
 Play round with player who is up (mod turn vs total players, and cycle through player vector)
 As long as the round wasn't quit, increment the turn
 If round was quit, game is ending prematurely:
 delete points
 reset round number
 If round wasn't quit and ended normally:
 display round end results
Assistance Received:
********************************************************************* */
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

/* *********************************************************************
Function Name:progressRound
Purpose: prompt user and save/load/play round
Parameters:
 Player *p: human or computer player that is playing
Return Value:
 int displaying if round was successful or not (in the future: other codes)
Local Variables:none
Algorithm:
 Give player options
 If selecting 1, save game (or tell player if the same game feature didn't work)
 If selecting 2, play round
 If selecting 3, examine options
 If selecting 4, confirm they want to quit
Assistance Received:
********************************************************************* */
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

/* *********************************************************************
Function Name:saveGame
Purpose: to save the game. Serialization
Parameters: none
Return Value: true or false based on successful save
Local Variables:
 ofstream roundSaveFile
Algorithm:
 Create and open the roundSaveFile in current directory
 If issue, output to screen and return false
 If no issue, record all variables accordingly in the file, through string stream
 Return true if no issues encountered
Assistance Received: none
********************************************************************* */
bool Round::saveGame(){
    
    ofstream roundSaveFile("roundSaveFile.txt");
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

/* *********************************************************************
Function Name:loadPlayerOrder
Purpose: load in the player order based on string in file (serialization)
Parameters:
 string nextPlayer: the string showing the next player up
Return Value: true or false based on issues encountered
Local Variables: none
Algorithm:
 Take in string.
 If "man" is found in string, "human" is most likely on the line, so setTurn accordingly
 No "man" found? Computer goes first.
 If there's an issue with the string for any reason, return false.
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name:loadNums
Purpose: Load all number based information from file to game, using THE POWER OF REGEX
Parameters:
 string passedNums: holds string input
 char numChoice: used to determine which line is loaded
Return Value: true or false (if issues encountered)
Local Variables:
    string numString: copy of passedNums in
 int ourNumber: the number ultimately read in
 int numCheck: used to check number length for validity
 smatch matched: used for regex matching confirmations
 regex numberFinder: the regex needed to match numbers. Fancy!
Algorithm:
 Iterate through the string read in
 Compare it with the regex
 Whenever a number is matched, increment the numCheck variable
 If numCheck is greater than 1, then there is more than 1 number on the line. Return false.
 Otherwise:
 If numChoice is 'r', load round number after checking validity
 If 'h' set human points
 If 'c' set computer points
 If issues encountered during this, return false. Otherwise, return true.
Assistance Received: Lots of regex websites. Ultimately, regex101 wa very helpful, but no site covered c++ specifically, so I had to kind of figure this out.
********************************************************************* */
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

/* *********************************************************************
Function Name:loadCards
Purpose: load cards from a line
Parameters:
 string passedHand: string of line passed in
 char deckChoice: choice prompting how the function will proceed
Return Value: true or false based on issues encountered
Local Variables:
 string cardString: copy of passed hand
 vector<string> cardValues: vector used to populate cards in deck, later
 smatch matches: matching for regex
 regex cards: regex phrase to match each card value on a line
 sregex_iterator cardIterator/empty: the iterators needed to go through a line and pull out multiple card values into the vector. Fun.
Algorithm:
 Iterate through the line
 For each card found, push it onto the back of the string vector
 Then, all based on Deck functions:
 If choice 'h', load human hand based on string
 If 'c', load computer hand
 If 'D', set draw pile
 If 'd', set discard pile
 Each of the above choices returns true when done.
 If not returned after choices are checked, return false because nothing loaded.
Assistance Received: None
********************************************************************* */
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

/* *********************************************************************
Function Name:loadFileStats
Purpose: loads the file, basically, with all validity checks
Parameters:
 vector<string> passedHand: vector of all file lines
Return Value: true or false based on success
Local Variables: none
Algorithm:
 Take the file vector
 Check to ensure that it has the appropriate number of lines on it. If not, return false.
 Set all variables based on other functions
 If issues encountered, return false.
 If no issues, return true.
Assistance Received: none.
********************************************************************* */
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

/* *********************************************************************
Function Name:loadGame
Purpose: to load the game from file
 NOTE/IMPORTANT: displaying files will work for the MacOS file system only. Will not work on windows. Runs through Xcode.
Parameters: none
Return Value: true or false based on success
Local Variables:
 string userFilePath: holds file path
 string fileLine: holds line of file
 ifstream loadedFile: for our file object
 vector<string> ourFiles: for listing files in the directory
 vector<string> fileStrings: for each line of the file to be loaded
 int fileCount: for confirming numerical order of files in the directory
 int userChoice: holds user choice for prompts
Algorithm:
 Ask user if they want to load a file from the directory, or if they want to put in their own custom path
 If from their own path, have them enter the path and populate the file path based on it
 If from current save on file, display files and have user pick from list. Note: in this case, I choose the default directory for the file, as any game would have their files in a set directory. I chose not to create a folder for this, but instead used the default Xcode file saving location.
 Open the file.
 Copy contents to a vector based on lines with data.
 
 
Assistance Received:
 Lots of online forums helped with this, since this is my first time navigating the Mac file system. I did not upgrade my OS to the latest version, and unfortunately Xcode is limiting my C++17 access (a little) based on the version it's in. That being said, the following forum was extremely useful in learning about how to make sure I accessed/displayed the files correctly: https://stackoverflow.com/questions/12976733/how-can-i-get-only-txt-files-from-directory-in-c
********************************************************************* */
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

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Local Variables:
Algorithm:
Assistance Received:
********************************************************************* */
void Round::clearPoints(){
    for(auto i: ourPlayers){
        i->deletePoints();
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
void Round::roundTest(){
    cout << "\tRound Test" << endl;
    return;
}
