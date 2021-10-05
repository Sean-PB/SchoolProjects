/***************************************************************************************************
* Sean Brandon, spbrando
* 2021 Spring CSE101 pa4
* Shuffle.cpp
* Client file for counting the number of suffles to return to original order using List ADT
***************************************************************************************************/
#include<iostream>
#include<string>
#include"List.h"

// Prototype for shuffle function
void shuffle(List &deck);

int main(int argc, char * argv[]){
    if (argc != 2 || atoi(argv[1]) < 0){
        std::cerr << "Shuffle requires a positive integer value as input" << '\n';
        exit(EXIT_FAILURE);
    }

    List deck;                      // original deck
    List shuffleDeck;               // a shuffled version of the deck
    int num = atoi(argv[1]);	    // the input number
    int count;                      // the number of times shuffled


    std::cout << "deck size\tshuffle count\n------------------------------" << '\n';

    // loop through 0 - n-1 sizes of decks
    for (int size = 1; size <= num; size++){
        // reset all
        deck.clear();
        shuffleDeck.clear();
        count = 0;

        // make deck
        for (int i = 0; i < size; i++){
            deck.insertBefore(i);
        }
        shuffleDeck = deck;                 // Copy the original deck to the one to be shuffled
        // shuffle deck repeatedly
        do{
            shuffle(shuffleDeck);
            count++;
        }while(!(deck == shuffleDeck));
        std::cout << size << "\t\t" << count << '\n';
    }
}

void shuffle(List &deck){
    List first;                     // first half of deck
    List second;                    // second half of deck
    int size = deck.size();         // size of deck
    int half = size / 2;            // where the half mark is

    // split the deck
    for (deck.moveFront(); deck.position() < deck.size(); ){
        if(deck.position() < half){
            first.insertBefore(deck.moveNext());
        }
        else{
            second.insertBefore(deck.moveNext());
        }
    }
    first.moveFront();
    second.moveFront();
    deck.clear();
    // insert first and second back into deck
    while (deck.position() < size){
        if(deck.position() % 2 == 0){       // if position of shuffled is even (or 0)
            deck.insertBefore(second.moveNext());
        }
        else{                                   // if poosition of shuffled is odd
            deck.insertBefore(first.moveNext());
        }
    }
}

