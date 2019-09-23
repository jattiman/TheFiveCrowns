
Five Crowns
Five Crowns is a card game played by 2 players.
The Objective
The objective of this game is to score the fewest points after all the rounds.
The Players
Two players play this game - one player will be the human user of your program, and the other player will be your program/computer.
The Setup
Two 58-card decks are used. Each deck contains:

    five suites: spades, clubs, diamonds, hearts and tridents.
    eleven cards in each suit: 3 through 10, Jack, Queen and King. Note no Ace, 1 or 2 cards.
    three jokers. 

The values of the cards are as follows:

    Cards 3-10 are worth their face value.
    Jack is worth 11 points, Queen is 12 and King is 13.
    Joker is worth 50 points.
    Each round has a wild card. The wild card of a round is the card with the face value equal to the number of cards dealt in the round, e.g., in a round where players are dealt 7 cards each, 7 is the wild card. The wild card is worth 20 points. 

A Round
A round proceeds as follows:

    The two decks are shuffled together.
    Each player is dealt n cards. On the first round, n = 3. On the next round, n = 4, and so on. On the last round, n = 13.
        For each round, the wild card is the card with the value of n. 
    The remaining cards are placed in draw pile face down. The top card in the draw pile is removed from the draw pile and placed face up in discard pile.
    First player:
        On the first round, a coin is tossed to determine who plays first. Human player is asked to call the toss.
        On subsequent rounds, the player to go out first on the previous round plays first. 
    The two players take alternate turns thereafter till the round ends.
    The round ends when one player goes out and the other player plays a turn to earn points. 

A Turn
During her/his turn, a player plays as follows:

    Draws the top card from the draw pile or the top card from the discard pile.
    Tries to assemble the cards in hand as runs and books:
        A run is a sequence of three or more cards of the same suit, e.g., 5, 6 and 7 of diamonds.
        A book is three or more cards of the same value, e.g., 9 of clubs, clubs and tridents. 
    Each card can be part of only one book or run.

    Jokers and wild cards make it easier to assemble runs and books:
        A joker can stand in for any card in a run or book, e.g., a run can be 5 of diamonds, a joker standing for 6 of diamonds and 7 of diamonds.
        A wild card can stand in for any card in a run or book, e.g., on the first round when the wild card is 3, a book can be 9 of clubs, 3 of any suit and 9 of tridents. 
    The player can have any number of wild cards and jokers in a run or book, and they can be anywhere in a run. A Joker or wild card can be moved from one book/run to another between turns, e.g., a Joker used as part of a 3-4-5 run on turn 1 can be re-purposed to be part of a 7-7-7 book on the next turn if the player picks up a 3, 4 or 5 card during turn 1.
    Discard one card on to the discard pile.
    If all the remaining cards in the player's hand can be arranged in runs and/or books, the player will go out by displaying the runs and books.
    If the other player has just gone out, the player will display all the runs and books in her/his hand. The sum of the values of the remaining cards in the player's hand will be the points awarded to the player. 

A Game
A game consists of 11 rounds:

    In the first round, each player is dealt 3 cards and the wild card is 3.
    In each subsequent round, the number of cards dealt to the players and therefore, the wild card increases by 1.
    In the last round, the cards dealt to each player is 13, and the wild card is King (13). 

Score
A player's score is the sum of the points earned by the player on all 11 rounds. Note that a player who goes out first in a round earns 0 points. The winner of the game is the player with the lowest score.
Computer Player's Strategy
Your computer player must play to win. It must have a strategy for each of the following:

    Whether to draw from the draw pile or discard pile;
    Which card to discard on the discard pile on each turn;
    How to use jokers and wild cards;
    When to go out. 

Implementation Notes

    User Interface: You must provide a user-friendly interface for the game. For C++, LISP and Prolog, ASCII graphics and command-line input are sufficient.
    All human inputs must be validated.
    Before each player plays, the following menu must be displayed and processed:
        Save the game
        Make a move
        Ask for help (only before human player plays)
        Quit the game 
    The turn played by the computer as well as the strategy it uses must be displayed on the screen, e.g.,

          The computer chose to pick up from the draw pile because ...
          It discarded 5 of clubs because ...
          The computer used the joker to ....
        

    The following must be displayed always on the screen:
        round number
        human hand and computer hand
        human game score and computer game score
        the card on top of the discard pile
        the cards in the draw pile - although they will be visible, assume that neither player can see them. 
    The points earned by the losing player must be declared at the end of each round.
    Help Mode: When the human player is playing, the computer must provide a help mode. If the human player asks for help, the computer must suggest:
        Whether to draw from draw pile or discard pile;
        Which card to discard on discard pile;
        How to assemble books and runs with the current hand;
        Whether to go out. 
    The computer must use its own playing strategy to come up with its recommendations. It must print the rationale for its recommendations, e.g.,

         I recommend you create a run of ...
         I recommend you drop 5 of Clubs because ....
       

    Serialization: The user should be able to suspend the game before either player's turn, and resume at a later time from where the game was left off. In order to do this:
        Provide the option to serialize before each player's turn
        When the serialization option is exercised, your program should save the current state of the game into a file and quit. We will use text format for the file.
        The text format for C++/Java Android will be as follows:

        Round: 1
          
        Computer:
           Score: 0
           Hand: XS KH J1
         
        Human:
           Score: 0
           Hand: JD 3T QC

        Draw Pile: 6S 5S 4S 3S 7S J1 3C 5C 6C 7C 9H JH QH 4T 6T J3 QS XS 9S 8C 4C 9C QC KC JC XC 8S JS KS J2 6H 3H 4H 5H XH 8H 7H XD QD KD 6D 5D 3D 4D 7D JD 9D 8D 8T 5T 3T 9T XT QT KT JT 7T 

        Discard Pile: 8T 6S 5S 4S 3S 7S 3C 5C 6C 7C 9H JH KH 4T 6T J3 QS 9S 8C 4C 9C KC JC XC 8S JS KS J2 6H 3H 4H 5H XH 8H 7H XD QD KD 6D 5D 3D 4D 7D 9D 8D 5T 9T XT QT KT JT 7T

        Next Player: Human

        The above snapshot is for the 1st round in the tournament. Each player has been dealt 3 cards and has a game score of 0. Computer hand contains 10 of Spades, King of Hearts and Joker 1. Human hand contains Jack of Diamonds, 3 of Tridents and Queen of Clubs. Draw pile contains the cards not yet played. The top of the draw pule is 6 of Spades - the card that the next player cannot see, but can pick up. The cards in the draw pile are always displayed on the screen, although the players play as though they are not aware of the cards. Discard pile contains the cards that have already been played. The top of the discard pile is 8 of Tridents - the card that the next player can see and pick up. The next player is Human player.

        The text format for LISP will be as follows:

        (
          ; Round:
          1
          
           ; Computer Score:
           0

           ; Computer Hand:
           ( XS KH J1 )

           ; Human Score: 
           0

           ; Human Hand: 
           ( JD 3T QC )

           ; Draw Pile: 
           ( 6S 5S 4S 3S 7S J1 3C 5C 6C 7C 9H JH QH 4T 6T J3 QS XS 9S 8C 4C 9C QC KC JC XC 8S JS KS J2 6H 3H 4H 5H XH 8H 7H XD QD KD 6D 5D 3D 4D 7D JD 9D 8D 8T 5T 3T 9T XT QT KT JT 7T )

           ; Discard Pile: 
           ( 8T 6S 5S 4S 3S 7S 3C 5C 6C 7C 9H JH KH 4T 6T J3 QS 9S 8C 4C 9C KC JC XC 8S JS KS J2 6H 3H 4H 5H XH 8H 7H XD QD KD 6D 5D 3D 4D 7D 9D 8D 5T 9T XT QT KT JT 7T )

           ; Next Player: 
           Human
        )

        Note that the comments above are for your convenience. You do not need to parse those - they will not appear in actual serialization files.

        The text format for Prolog will be as follows:

        [
          % Round:
          1,
          
           % Computer Score:
           0,

           % Computer Hand:
           [ xs, kh, j1 ],

           % Human Score: 
           0,

           % Human Hand: 
           [ jd, 3t, qc ],

           % Draw Pile:  
           [ 6s, 5s, 4s, 3s, 7s, j1, 3c, 5c, 6c, 7c, 9h, jh, qh, 4t, 6t, j3, qs, xs, 9s, 8c, 4c, 9c, qc, kc, jc, xc, 8s, js, ks, j2, 6h, 3h, 4h, 5h, xh, 8h, 7h, xd, qd, kd, 6d, 5d, 3d, 4d, 7d, jd, 9d, 8d, 8t, 5t, 3t, 9t, xt, qt, kt, jt, 7t ],

           % Discard Pile: 
           [ 8t, 6s, 5s, 4s, 3s, 7s, 3c, 5c, 6c, 7c, 9h, jh, kh, 4t, 6t, j3, qs, 9s, 8c, 4c, 9c, kc, jc, xc, 8s, js, ks, j2, 6h, 3h, 4h, 5h, xh, 8h, 7h, xd, qd, kd, 6d, 5d, 3d, 4d, 7d, 9d, 8d, 5t, 9t, xt, qt, kt, jt, 7t ],

           % Next Player: 
           human
        ]

        Note that the comments above are for your convenience. You do not need to parse those - they will not appear in actual serialization files.

        Note that the first card in the draw pile is the top card - the only card that the player cannot see, but can pick next. Similarly, the first card in the discard pile is the top card - the only card that the player can see and pick.
        When your program is started, it should provide the option to resume a game from a previously saved state. If yes, it should ask for the name of the text file from which to read the current state of the game, and resume playing from that state. 
    Using any part of code available in textbooks or on the web is unacceptable. 

Grading
Please see the rubric for some of the features on which your program will be graded.

Any implementation without serialization cannot qualify for more than 50% of the total points.
Milestones
The following are recommended milestones for each project:

    Week 1: A basic, complete game except the items listed for week 2
    Week 2: All the strategies for the computer player, help for human player and serialization.
    Week 3: Code refactoring, cleaning, documentation. 

Acknowledgments
This game was adapted and modified from the description at setgame.com 
