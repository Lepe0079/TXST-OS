#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <fstream>

#include "Card.h"
#include "Deck.h"

using namespace std;

struct hand
{
    Card* card1 = nullptr;
    Card* card2 = nullptr;
    int emptycard = 1;
};
struct player
{
    int playerID;
    hand playerHand;
};
struct turnArgs{
    player* CurPl;
    int plID;
    Deck* CurDk;
};
struct dealerArgs{
    player* group;
    Deck* CurDK;
    int numPlayers;
    int round;
};

//function declarations for threads
void dealInitial(player*, Deck*, int, int);
void* playerTurn(void*);
void showHands(player*, int);
void gamelog(const string);

pthread_mutex_t plock;
pthread_mutex_t winlock;
bool roundWin = false;
int winningPlayer;

int main(){
    int round = 0;
    int match = 3;
    int numPlayers = 3;
    int seed = 20;
    //create deck
    Deck mainDeck(seed);
    //create the players
    player players[numPlayers];
    for(int i = 0; i < numPlayers; ++i){players[i].playerID = i+1;}

    //create threads
    pthread_t playerThread[numPlayers];

    //initiate the lock
    if (pthread_mutex_init(&plock, NULL) != 0) { 
        cout << "\n mutex init has failed\n"; 
        return 1; 
    } 
    //create arguments
    struct turnArgs *P1 = (struct turnArgs *)malloc(sizeof(struct turnArgs));
    struct turnArgs *P2 = (struct turnArgs *)malloc(sizeof(struct turnArgs));
    struct turnArgs *P3 = (struct turnArgs *)malloc(sizeof(struct turnArgs));
    struct dealerArgs *Dealer = (struct dealerArgs *)malloc(sizeof(struct dealerArgs));

    //player1
    P1->CurPl = &players[0];
    P1->CurDk = &mainDeck;
    P1->plID = players[0].playerID;

    //player2
    P2->CurPl = &players[1];
    P2->CurDk = &mainDeck;
    P2->plID = players[1].playerID;

    //player3
    P3->CurPl = &players[2];
    P3->CurDk = &mainDeck;
    P3->plID = players[2].playerID;
    //put them in an array for iteration
    turnArgs* playerArgs[3] = {P1, P2, P3};

    //dealer
    Dealer->group = players;
    Dealer->CurDK = &mainDeck;
    Dealer->numPlayers = numPlayers;
    Dealer->round = round;

    int tcheck;
//===========================================================================================start game
    dealInitial(players, &mainDeck, numPlayers, round); 

    for(round = 0; round < match; ++round){

    
    
    do{
        for (int i = 0; i < numPlayers; i++)
        {
            tcheck = pthread_create(&playerThread[i], NULL, playerTurn, (void*)playerArgs[i]);
            if(tcheck){
                cout << "error creating thread " << tcheck;
                exit(-1);
            }
        }
        for (int i = 0; i < numPlayers; ++i)
        {
            if(pthread_join(playerThread[i], NULL)){
                cout << "error joining";
                exit(2);
            } 
        }
    }while(!roundWin);
    roundWin = false;  
    gamelog(mainDeck.showDeck());
    dealInitial(players, &mainDeck, numPlayers, round); 
    }
    string s = "\n\nGame with seed " + to_string(seed) + "\n\n";
    gamelog(s);
    return 0;
//===========================================================================================end game
}

void dealInitial(player* players, Deck* gameDeck, int numPlayers, int round)
{
    gamelog("Dealer Shuffles");
    if(round == 2)
        return;
    if(round != 0)
    {
        //shuffle the deck if its a second round using the set seed
        gameDeck->buildDeck();
    }
    for(int i = 0; i < numPlayers; ++i)
    {
        //assign player a clean hand and clear dangling ptr
        hand* oldHand = &players[i].playerHand;
        hand* cleanHand = new hand();
        players[i].playerHand = *cleanHand;
        oldHand = nullptr;

        //assign player a card
        players[i].playerHand.card1 = gameDeck->getCard();
        players[i].playerHand.emptycard = 2;
        string s = "Player " + to_string(players[i].playerID) + " draws " + to_string(players[i].playerHand.card1->value);
        gamelog(s);   
    }
}
void* playerTurn(void* current)
{
    /*fill the hand if not filled already
    if player hands are full, grab one and compare it
    if they are a pair, declare winner and end the round
    if they are discard one at random and place it at the bottom of deck*/
    pthread_mutex_lock(&plock);

    //unpack the struct
    Deck* gameDeck = ((struct turnArgs*)current)->CurDk;
    player* players = ((struct turnArgs*)current)->CurPl;
    int playerID = ((struct turnArgs*)current)->plID;
    string s;
    //randomize discard
    int discard = random()%2 +1;

    //check if anyone else won
    if(roundWin){
        showHands(players, playerID);
        if(playerID == winningPlayer){
            s = "Yes";
        }
        else
        {
            s = "No";
        }
        gamelog("Player " +to_string(playerID) + " Win: " + s);
        gamelog("Player " + to_string(playerID) + " Exits");
        pthread_mutex_unlock(&plock);
        pthread_exit(NULL);
    }
    else{
        if(players->playerHand.emptycard != 0)
        {//fills the hand
            if(players->playerHand.emptycard == 1)
            {   
                players->playerHand.card1 = gameDeck->getCard();
                s = "Player " + to_string(playerID) + " draws " + to_string(players->playerHand.card1->value);
            }
            else
            {
                players->playerHand.card2 = gameDeck->getCard();
                s = "Player " + to_string(playerID) + " draws " + to_string(players->playerHand.card2->value);
            }
            players->playerHand.emptycard = 0;
    }
    }
    //log the draw
    gamelog(s);

    //win condition check
    if(players->playerHand.card1->value == players->playerHand.card2->value)
    {
        
        if(!roundWin == true)
        {
            s = "Player " + to_string(playerID) + " is the winner";
            gamelog(s);
            showHands(players, playerID);
            gamelog("Player " +to_string(playerID) + " Win: Yes");
            s = "Player " + to_string(playerID) + " Exits";
            gamelog(s);
            winningPlayer = playerID;
            roundWin = true;
        }
        pthread_mutex_unlock(&plock);
        pthread_exit(NULL);
    }
    else
    {//discard a card at random
        switch (discard)
        {
        case 1:     s = "Player " + to_string(playerID) + " discards " + to_string(players->playerHand.card1->value);
                    gameDeck->addCard(players->playerHand.card1);
                    players->playerHand.card1 = nullptr;
                    players->playerHand.emptycard = 1;
                    break;

        case 2:     s = "Player " + to_string(playerID) + " discards " + to_string(players->playerHand.card2->value);
                    gameDeck->addCard(players->playerHand.card2);
                    players->playerHand.card2 = nullptr;
                    players->playerHand.emptycard = 2;
                    break;
        default:    cout << "nothing discarded";
                    players->playerHand.emptycard = 0;
                    break;
        }
        gamelog(s); 
    }
    pthread_mutex_unlock(&plock);
    pthread_exit(NULL);
}
void showHands(player* player, int playerID)
{
    string s = "Player " + to_string(player->playerID) + " Hand: |";
    if(player->playerHand.card1){
            s += to_string(player->playerHand.card1->value) + "| ";}
    if(player->playerHand.card2){
            s += "|" + to_string(player->playerHand.card2->value) + "| ";
    }
    gamelog(s);
}

void gamelog(string s)
{
    cout << s << endl;
    ofstream fileOUT;
    ifstream fileIN;
    fileIN.open("game.txt");
    fileOUT.open ("game.txt",ios::app); // Append mode
    if (fileIN.is_open()) {
        fileOUT << s << endl; // Writing data to file
    }
    fileIN.close();
    fileOUT.close();
}
