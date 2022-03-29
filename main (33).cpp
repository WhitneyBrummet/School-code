#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

/*
Function to take from top of deck
Function to create random cards (for infinite deck)

Function to determine hand points
Function for policy1
Function for policy2
*/
vector<string> shuffleDeck(vector<string> deck){
    random_shuffle(deck.begin(), deck.end());
    
    return deck;
}
vector<string> createDeck(vector<string> deck){
    string suit;
    string cardName;
    for (int i = 0; i < 4; i++){
        if (i == 0){suit = "of Hearts";}
        if (i == 1){suit = "of Diamonds";}
        if (i == 2){suit = "of Spades";}
        if (i == 3){suit = "of Clubs";}
        
        for (int i = 0; i < 13; i++){
            if (i == 0){cardName = "Ace ";}
            if (i == 1){cardName = "Two ";}
            if (i == 2){cardName = "Three ";}
            if (i == 3){cardName = "Four ";}
            if (i == 4){cardName = "Five ";}
            if (i == 5){cardName = "Six ";}
            if (i == 6){cardName = "Seven ";}
            if (i == 7){cardName = "Eight ";}
            if (i == 8){cardName = "Nine ";}
            if (i == 9){cardName = "Ten ";}
            if (i == 10){cardName = "Jack ";}
            if (i == 11){cardName = "Queen ";}
            if (i == 12){cardName = "King ";}
            
            deck.push_back(cardName + suit);
        }
        
    }
    
    return deck;
}
int addHand(vector<string> playerHand){
    int number = 0;
    int numOfAces = 0;
    for (int i = 0; i < playerHand.size(); i++){
        ;
        if (playerHand.at(i).substr(0,3) == "Two"){number += 2;}
        else if (playerHand.at(i).substr(0,5) == "Three"){number += 3;}
        else if (playerHand.at(i).substr(0,4) == "Four"){number += 4;}
        else if (playerHand.at(i).substr(0,4) == "Five"){number += 5;}
        else if (playerHand.at(i).substr(0,3) == "Six"){number += 6;}
        else if (playerHand.at(i).substr(0,5) == "Seven"){number += 7;}
        else if (playerHand.at(i).substr(0,5) == "Eight"){number += 8;}
        else if (playerHand.at(i).substr(0,4) == "Nine"){number += 9;}
        else if (playerHand.at(i).substr(0,3) == "Ace"){number += 11; numOfAces += 1;}
        else {number += 10;}
        
        if (number > 21 && numOfAces != 0){
            number -= 10;
            numOfAces -= 1;
        }
    }
    return number;
}
int addHardHand(vector<string> playerHand){
    int number = 0;
    for (int i = 0; i < playerHand.size(); i++){
        if (playerHand.at(i).substr(0,3) == "Two"){number += 2;}
        else if (playerHand.at(i).substr(0,5) == "Three"){number += 3;}
        else if (playerHand.at(i).substr(0,4) == "Four"){number += 4;}
        else if (playerHand.at(i).substr(0,4) == "Five"){number += 5;}
        else if (playerHand.at(i).substr(0,3) == "Six"){number += 6;}
        else if (playerHand.at(i).substr(0,5) == "Seven"){number += 7;}
        else if (playerHand.at(i).substr(0,5) == "Eight"){number += 8;}
        else if (playerHand.at(i).substr(0,4) == "Nine"){number += 9;}
        else if (playerHand.at(i).substr(0,3) == "Ace"){number += 1;}
        else {number += 10;}
    }
    return number;
}
double numOfWins(vector<string> dealerHand, vector<string> playerHand, vector<string> deck, vector<string> shuffledDeck, string policy, string deckType){
    int numberOfTimes = 1000;
    int numOfTimesWon = 0;
    while (numberOfTimes != 0){  
        int totalOfPHand = 0;
        int totalOfDHand = 0;
        playerHand.clear();
        dealerHand.clear();
        
        shuffledDeck = shuffleDeck(deck);
        
        if (deckType == "Finite"){
            //give player 2 cards
            playerHand.push_back(shuffledDeck.back());
            shuffledDeck.pop_back();
            playerHand.push_back(shuffledDeck.back());
            shuffledDeck.pop_back();

            //give dealer 2 cards 
            dealerHand.push_back(shuffledDeck.back());
            shuffledDeck.pop_back();
            dealerHand.push_back(shuffledDeck.back());
            shuffledDeck.pop_back();
            
            if (policy == "Policy1"){
                totalOfPHand = addHand(playerHand);
                
                //hit until hand totals to 17 or greater
                while (totalOfPHand < 17){
                    playerHand.push_back(shuffledDeck.back());
                    shuffledDeck.pop_back();
                    totalOfPHand = addHand(playerHand);
                }
                cout << "Player's amount of points is: " << totalOfPHand << endl;
                if (totalOfPHand > 21){cout << "Player has made a bust. Player has lost." << endl << endl;}
                
                //if hand total is not a bust
                if (totalOfPHand <= 21){
                    totalOfDHand = addHand(dealerHand);
                    //hit until hand totals to 17 or greater
                    while (totalOfDHand < 17){
                        dealerHand.push_back(shuffledDeck.back());
                        shuffledDeck.pop_back();
                        totalOfDHand = addHand(dealerHand);
                    }  
                    cout << "Dealer's amount of points is: " << totalOfDHand << endl;
                    
                    //if dealer hand is a bust and player hand is not a bust, player wins
                    //else if dealer hand is not a bust and playerhand is greater than dealer hand, player wins
                    //else if dealer and player tie, player is considered a win.
                    if (totalOfDHand > 21){numOfTimesWon += 1; cout << "Dealer has made a bust. Player has won." << endl << endl;}
                    else if (totalOfDHand <= 21 && totalOfPHand > totalOfDHand){numOfTimesWon += 1; cout << "Player's hand is higher than Dealer's. Player has won." << endl << endl;}
                    else if (totalOfDHand <= 21 && totalOfPHand == totalOfDHand){numOfTimesWon += 1; cout << "Player's hand is the same as Dealer's. Player has won." << endl << endl;}
                    else {cout << "Dealer wins" << endl << endl;}
                }
            }
            else if (policy == "Policy2"){
                totalOfPHand = addHardHand(playerHand);
                //hit until hand totals to 17 or greater
                while (totalOfPHand < 17){
                    playerHand.push_back(shuffledDeck.back());
                    shuffledDeck.pop_back();
                    totalOfPHand = addHardHand(playerHand);
                }
                cout << "Player's amount of points is: " << totalOfPHand << endl;
                if (totalOfPHand > 21){cout << "Player has made a bust. Player has lost." << endl << endl;}
                
                //if hand total is not a bust
                if (totalOfPHand <= 21){
                    totalOfDHand = addHand(dealerHand);
                    //hit until hand totals to 17 or greater
                    while (totalOfDHand < 17){
                        dealerHand.push_back(shuffledDeck.back());
                        shuffledDeck.pop_back();
                        totalOfDHand = addHand(dealerHand);
                    }  
                    cout << "Dealer's amount of points is: " << totalOfDHand << endl;
                    
                    //if dealer hand is a bust and player hand is not a bust, player wins
                    //else if dealer hand is not a bust and playerhand is greater than dealer hand, player wins
                    //else if dealer and player tie, player is considered a win.
                    if (totalOfDHand > 21){numOfTimesWon += 1; cout << "Dealer has made a bust. Player has won." << endl << endl;}
                    else if (totalOfDHand <= 21 && totalOfPHand > totalOfDHand){numOfTimesWon += 1; cout << "Player's hand is higher than Dealer's. Player has won." << endl << endl;}
                    else if (totalOfDHand <= 21 && totalOfPHand == totalOfDHand){numOfTimesWon += 1;cout << "Player's hand is the same as Dealer's. Player has won." << endl << endl;}
                    else {cout << "Dealer wins" << endl << endl;}
                }
                
            }
            cout << "Shuffling cards for next game..." << endl << endl;
            shuffledDeck = shuffleDeck(deck);
        }
        else if (deckType == "Infinite"){
            //give player 2 cards
            int rNum = rand() % 52;
            playerHand.push_back(deck.at(rNum));
            rNum = rand() % 52;
            playerHand.push_back(deck.at(rNum));
            
            //give dealer 2 cards
            rNum = rand() % 52;
            dealerHand.push_back(deck.at(rNum));
            rNum = rand() % 52;
            dealerHand.push_back(deck.at(rNum));

            if (policy == "Policy1"){
                totalOfPHand = addHand(playerHand);
                
                //hit until hand totals to 17 or greater
                while (totalOfPHand < 17){
                    int rNum = rand() % 52;
                    playerHand.push_back(deck.at(rNum));
                    totalOfPHand = addHand(playerHand);
                }
                cout << "Player's amount of points is: " << totalOfPHand << endl;
                if (totalOfPHand > 21){cout << "Player has made a bust. Player has lost." << endl << endl;}
                
                //if hand total is not a bust
                if (totalOfPHand <= 21){
                    totalOfDHand = addHand(dealerHand);
                    
                    //hit until hand totals to 17 or greater
                    while (totalOfDHand < 17){
                        rNum = rand() % 52;
                        dealerHand.push_back(deck.at(rNum));
                        totalOfDHand = addHand(dealerHand);
                    }  

                    cout << "Dealer's amount of points is: " << totalOfDHand << endl;
                    
                    //if dealer hand is a bust and player hand is not a bust, player wins
                    //else if dealer hand is not a bust and playerhand is greater than dealer hand, player wins
                    //else if dealer and player tie, player is considered a win.
                    if (totalOfDHand > 21){numOfTimesWon += 1;cout << "Dealer has made a bust. Player has won." << endl << endl;}
                    else if (totalOfDHand <= 21 && totalOfPHand > totalOfDHand){numOfTimesWon += 1;cout << "Player's hand is higher than Dealer's. Player has won." << endl << endl;}
                    else if (totalOfDHand <= 21 && totalOfPHand == totalOfDHand){numOfTimesWon += 1;cout << "Player's hand is the same as Dealer's. Player has won." << endl << endl;}
                    else {cout << "Dealer wins" << endl << endl;}
                }
            }
            else if (policy == "Policy2"){
                totalOfPHand = addHardHand(playerHand);
                
                //hit until hand totals to 17 or greater
                while (totalOfPHand < 17){
                    int rNum = rand() % 52;
                    playerHand.push_back(deck.at(rNum));
                    totalOfPHand = addHardHand(playerHand);
                }
                cout << "Player's amount of points is: " << totalOfPHand << endl;
                if (totalOfPHand > 21){cout << "Player has made a bust. Player has lost." << endl << endl;}
                
                //if hand total is not a bust
                if (totalOfPHand <= 21){
                    totalOfDHand = addHand(dealerHand);
                    //hit until hand totals to 17 or greater
                    while (totalOfDHand < 17){
                        rNum = rand() % 52;
                        dealerHand.push_back(deck.at(rNum));
                        totalOfDHand = addHand(dealerHand);
                    }  
                    cout << "Dealer's amount of points is: " << totalOfDHand << endl;
                    
                    //if dealer hand is a bust and player hand is not a bust, player wins
                    //else if dealer hand is not a bust and playerhand is greater than dealer hand, player wins
                    //else if dealer and player tie, player is considered a win.
                    if (totalOfDHand > 21){numOfTimesWon += 1; cout << "Dealer has made a bust. Player has won." << endl << endl;}
                    else if (totalOfDHand <= 21 && totalOfPHand > totalOfDHand){numOfTimesWon += 1; cout << "Player's hand is higher than Dealer's. Player has won." << endl << endl;}
                    else if (totalOfDHand <= 21 && totalOfPHand == totalOfDHand){numOfTimesWon += 1;cout << "Player's hand is the same as Dealer's. Player has won." << endl << endl;}
                    else {cout << "Dealer wins" << endl << endl;}
                }
            }
        }
        numberOfTimes -= 1;
    }
    
    return numOfTimesWon/1000.0;
}
int main()
{
    vector<string> dealerHand;
    vector<string> playerHand;
    vector<string> deck;
    
    srand(time(0));

    deck = createDeck(deck);
    
    vector<string> shuffledDeck = shuffleDeck(deck);
    
    
    double winProbabilityP1 = numOfWins(dealerHand, playerHand, deck, shuffledDeck, "Policy1", "Infinite");
    double winProbabilityP2 = numOfWins(dealerHand, playerHand, deck, shuffledDeck, "Policy1", "Finite");
    double winProbabilityP3 = numOfWins(dealerHand, playerHand, deck, shuffledDeck, "Policy2", "Infinite");
    double winProbabilityP4 = numOfWins(dealerHand, playerHand, deck, shuffledDeck, "Policy2", "Finite");
    
    cout << "Calculating win probabilities..." << endl;
    cout << "The probability of winning if the deck is infinite and the player sticks after reaching 17: " << winProbabilityP1 << endl;
    cout << "The probability of winning if the deck is standard and the player sticks after reaching 17: " << winProbabilityP2 << endl;
    cout << "The probability of winning if the deck is infinite and the player sticks after reaching a hard 17: " << winProbabilityP3 << endl;
    cout << "The probability of winning if the deck is standard and the player sticks after reaching a hard 17: " << winProbabilityP4 << endl;
    
    return 0;
}

