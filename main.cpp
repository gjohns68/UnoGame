#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <ctype.h>
#include <string>
#include "game_state.h"
#include "card.h"

using namespace std;

/**
 * Function to clear the terminal by inserting many new line characters.
 */
void clearTerminal();

/**
 * Function to populate the deck with cards.
 * 
 * @param deck A vector reference of Card pointers representing the deck
 */
void buildDeck(vector<Card*>& deck);

/**
 * Function to shuffle the deck.
 * 
 * @param deck A vector reference of Card pointers representing the deck
 */
 void shuffleDeck(vector<Card*>&);

/**
 * Function to draw a card from the deck to either the hand or discard pile.
 * 
 * @param deck A vector reference of Card pointers representing the deck
 * @param target A vector representing the structure that the card being drawn 
 * from the deck is being drawn to. This can be either a hand or the discard
 * pile
 */
int drawCards(vector<Card*>& deck, vector<Card*>& target, int);

/**
 * Function to draw 7 cards to each player's hand at the beginning of the game.
 * 
 * @param deck A vector reference of Card pointers representing the deck.
 * @param hands A vector of vector of Card pointers representing each player 
 * and their hands. The indicies of the first vector represents a player, and 
 * the indicies of the vector at that index is each individual card within the
 * player's hand.
 */
void populateHands(vector<Card*>& deck, vector<vector<Card*>>& hands);

/** 
 * Renders the cards in he hand vector passed.
 * 
 * @param hand A vector containing Card pointers
 */
void renderHand(vector<Card*> hand);

/**
 * Renders the top card of the passed discard vector.
 * 
 * @param hand A vector containing Card pointers
 */
void renderDiscard(vector<Card*>);

/**
 * Passed references to the deck, hand, and discard vectors and a reference to 
 * the game state. This function will resolve the turn for the current player
 * (whose index is stored in the game state). TakeTurn will query the user for
 * input, draw cards if the previous card was a draw 2 card, or skip the current
 * players turn (see numCardsToPlay in GameState).
 * 
 * @param deck A vector reference of Card pointers representing the deck
 * @param hand A vector reference of Card pointers representing a single player's hand
 * @param discard A vector reference of Card pointers representing the discard pile
 * @param gameState A reference of the game state object
 */
void takeTurn(vector<Card*>& deck, vector<Card*>& hand, vector<Card*>& discard, GameState& gameState);

void replenishDeck(vector<Card*> &deck, vector<Card*> &discard);

bool verifiyInput(string x){
    bool digit = true;
    for(int i = 0; i < x.length(); i++){
        if(!isdigit(x[i])){
            digit = false;
            break;
        } 
    }
    
    return digit;
}

int main(){
    srand(time(0));
    int NUM_PLAYERS;
    while(true){
        bool isDigit = true;
        cout << "How many players are there?" << endl;
        string INPUT;
        cin >> INPUT;
        //checks if users string is a digit
        if(verifiyInput(INPUT)){
            //assigns string to int
            if(stoi(INPUT) > 1 && stoi(INPUT) < 16){
                NUM_PLAYERS = stoi(INPUT);
                break;
            } else {
                cout << "Please enter a number 2-15" << endl;
            }
        } else {
            cout << "Please enter a number" << endl;
        }
    }
    
    cout << NUM_PLAYERS << endl;
    GameState gameState(NUM_PLAYERS);

    vector<Card*> deck;
    vector<Card*> discard;

    
    vector<vector<Card*>> hands(NUM_PLAYERS);

    buildDeck(deck);
    shuffleDeck(deck);
    populateHands(deck, hands);
    drawCards(deck, discard, 1);
    
    bool winner = false;
    while(1 /* TODO: Check for winner (no cards in hand)*/){
        if(deck.size() < 5){
            replenishDeck(deck, discard);
        }
        
        for(int i = 0; i < NUM_PLAYERS; i++){
            if(hands.at(i).size() == 0 ){
                cout << "Player " << i+1 << "Wins!" << endl;
                bool winner = true;
                break;
            } else {
                break;
            }
        }
        if(winner == false){
            takeTurn(deck, hands.at(gameState.currentPlayerIndex), discard, gameState);
        }
    }
    
    return 0;
}

void replenishDeck(vector<Card*> &deck, vector<Card*> &discard){
    Card* temp = discard.at(discard.size() -1);
    discard.erase(discard.begin() + (discard.size() - 1));
    while(discard.size() > 0){
        int idx1 = rand() % discard.size() - 2;
        deck.push_back(discard.at(idx1));
        discard.erase(discard.begin() + idx1);
    }
}

void clearTerminal(){
    for(int i = 0; i < 100; i++){
        cout << endl;
    }
}

void buildDeck(vector<Card*> &deck){
    // Create Number Cards
    for(int c = RED; c < 4; c++){
        for(int n = 0; n < 10; n++){
            Card* temp = new NumberCard((Color)c, n, NUM);
            deck.push_back(temp);
            deck.push_back(temp);
        }
    }
    for(int i = 0; i < 8; i++){
        Card* temp = new WildCard(WILD);
        deck.push_back(temp);
    }
    for(int i = 0; i < 4; i++){
        Card* temp = new SkipCard((Color)i, SKIP);
        deck.push_back(temp);
        deck.push_back(temp);
    }
    for(int i = 0; i < 4; i++){
        Card* temp = new ReverseCard((Color)i, REVERSE);
        deck.push_back(temp);
        deck.push_back(temp);
    }
    for(int i = 0; i < 4; i++){
        Card* temp = new Plus2Card((Color)i, PLUS2);
        deck.push_back(temp);
        deck.push_back(temp);
    }
}

void shuffleDeck(vector<Card*> &deck){
    for(int i = 0; i < 1000; i++){
        int idx1 = rand() % deck.size();
        int idx2 = rand() % deck.size();
        Card* temp = deck.at(idx1);
        deck.at(idx1) = deck.at(idx2);
        deck.at(idx2) = temp;
    }
}

int drawCards(vector<Card*> &deck, vector<Card*> &target, int numToDraw){
    for(int i = 0; i < numToDraw; i++){
        if(deck.size() > 0){
            target.push_back(deck.at(deck.size() - 1));
            deck.pop_back();
        } else {
            return numToDraw - i;
        }
    }
    return 0;
}

void populateHands(vector<Card*> &deck, vector<vector<Card*>> &hands){
    for(int i = 0; i < hands.size(); i++){
        drawCards(deck, hands.at(i), 7);
    }
}

void renderHand(vector<Card*> hand){
    if(hand.size() > 0){
        for(int i = 0; i <= 7; i++){
            for(int j = 0; j < hand.size(); j++){
                cout << hand.at(j)->render(i) << " ";
            }
            cout << endl;
        }
    } else {
        for(int i = 0; i <= 7; i++)
            cout << endl;
    }
}

void renderDiscard(vector<Card*> discard){
    for(int i = 0; i <= 7; i++){
        cout << discard.at(discard.size() - 1)->render(i) << endl;
    }
}

void takeTurn(vector<Card*> &deck, vector<Card*> &hand, vector<Card*> &discard, GameState &gameState){
    clearTerminal();
    renderDiscard(discard);
    cout << "Player " << gameState.currentPlayerIndex + 1 << "'s turn." << endl;
    
    // TODO: Draw cards if necessary (draw 2 card)
    int check = drawCards(deck, hand, gameState.numCardsToDraw);
    if(check != 0 ){
        replenishDeck(deck, discard);
        drawCards(deck, hand, check);
    }
    gameState.numCardsToDraw = 0; // reset cards to draw back to 0
    
    renderHand(hand);
    
    // loop for number of cards to play (0 if previously played card was a "skip" or "draw 2")
    //for(int j = 0; j < gameState.numCardsToPlay; j++){
    if(!gameState.skipTurn){
        // Collect user input
        cout << "What would you like to do?" << endl;
        int i;
        for(i = 0; i < hand.size(); i++){
            cout << i << ": Play Card" << endl;
        }
        cout << i << ": Draw a Card" << endl;
        string sinput;
        int input;
        
        while(true){
            cin >> sinput;
            if(verifiyInput(sinput)){
                if(stoi(sinput) < i){
                    input = stoi(sinput);
                    break;
                }
            }
        }
        
        
        // Evaluate user input
        if(input < i){
            if(hand.at(input)->getType() == SKIP){
                    gameState.skipTurn = true;
                    Card* temp;
                    temp = hand.at(input);
                    discard.push_back(temp);
                    hand.erase(hand.begin() + input); // Remove card in hand at position "input"
                } else if(hand.at(input)->getType() == REVERSE){
                    cout << "this is a reverse card" << endl;
                    gameState.setReverse();
                    Card* temp;
                    temp = hand.at(input);
                    discard.push_back(temp);
                    hand.erase(hand.begin() + input); // Remove card in hand at position "input"
                } else if(hand.at(input)->getType() == PLUS2){
                    gameState.numCardsToDraw++;
                    gameState.numCardsToDraw++;
                    Card* temp;
                    temp = hand.at(input);
                    discard.push_back(temp);
                    hand.erase(hand.begin() + input); // Remove card in hand at position "input"
                }  else if(hand.at(input)->play(discard.at(discard.size()-1), gameState)){
                    if(hand.at(input)->getType() == WILD){
                        //Makes sure user input is good
                        int wildInput;
                        while(true){
                            cout << "What color do you want to change to?" << endl;
                            cout << "0: Red\n1:Green\n2: Yellow\n3: Blue" << endl;
                            string swildInput;
                            cin >> swildInput;
                            if(verifiyInput(swildInput)){
                                if(stoi(swildInput) > -1 && stoi(swildInput) < 4){
                                    wildInput = stoi(swildInput);
                                    break;
                                }
                            }
                        }
                        
                        switch(wildInput){
                            case 0:
                                hand.at(input)->setColor(RED);
                                break;
                            case 1:
                                hand.at(input)->setColor(GREEN);
                                break;
                            case 2:
                                hand.at(input)->setColor(YELLOW);
                                break;
                            case 3:
                                hand.at(input)->setColor(BLUE);
                                break;
                            default:
                                cout << "Improper choice" << endl;
                                takeTurn(deck, hand, discard, gameState);
                                return;
                        }
                } 
                Card* temp;
                temp = hand.at(input);
                discard.push_back(temp);
                hand.erase(hand.begin() + input); // Remove card in hand at position "input"
            } else {
                cout << "Improper choice" << endl;
                takeTurn(deck, hand, discard, gameState);
                return;
            }
        }else if(input == i){
            drawCards(deck, hand, 1);
        }
    }else{
        gameState.skipTurn = false;
    }
    
    // update variables for next turn
    gameState.nextTurn();
}