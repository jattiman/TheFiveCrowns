/*
***************************************************************
* Name:  John Atti                                            *
* Project:  5Crowns C++ Project 1                             *
* Class:  CMPS 366 01 - Organization of Programming Languages *
* Date:  10/22/2019                                            *
***************************************************************
*/
#include <stdio.h>

// this enum class was ultimately not used. Holding onto this for the future, though.


// I set the suites to equal values over the max card value
// If I'm correct with my assumptions, this will help avoid
// confusion with the card faces, and can help me with
// differentiating Jacks and Jokers.
enum CardSuites{
    S=14,
    C=15,
    D=16,
    H=17,
    T=18
};
