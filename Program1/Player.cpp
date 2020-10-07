#include "Player.h"

//initiate static variable
int Player::randSeed;

//default constructor
Player::Player():playerID(1)
{
    randSeed = 1;
    initLocks();
    changeSeed(1);
}
    
//actual constructor. 
Player::Player(int ID, int newSeed, Deck* deckRef)
{
    randSeed = newSeed;
    initLocks();
    if(ID <=0)
        playerID = 1;
    else
        playerID = ID;    
    changeSeed(newSeed);
    gameDeck = deckRef;
}

//function for players to draw will lock if the player(thread) is accessing the deck
void Player::playerDraw()
{   
    pthread_mutex_lock(&drawLock);
    if(!playerHand.drawn)
    {
        playerHand.drawn = gameDeck->getCard();
        if(!playerHand.held){
            playerHand.held = playerHand.drawn;
            playerHand.drawn = nullptr;}   
    }
    else
    {
        gameLog("cannot draw anymore cards");
    }
    pthread_mutex_unlock(&drawLock);
}

//function to start player thread
void Player::threadEntry(bool* win){

}
//player discards a card at random
void Player::playerDiscard(){
    pthread_mutex_lock(&discardLock);
    srand(randSeed);
    int discard = random() % 2 +1;

    //put card back on deck and keep card in held hand
    switch(discard){
        case 1: gameDeck->addCard(playerHand.drawn);
                playerHand.drawn = playerHand.held;
                playerHand.held = nullptr;
                break;
        case 2: gameDeck->addCard(playerHand.held);
                playerHand.held = nullptr;
                break;
        default: break;
    }
    pthread_mutex_unlock(&discardLock);
}

//check if player has won
bool Player::playerWin()
{
    pthread_mutex_lock(&winLock);
    //short eval to make sure there is a second card to compare, then compared
    if((playerHand.drawn) 
        && (playerHand.drawn->value == playerHand.held->value)){isWinner = true;}

    pthread_mutex_unlock(&winLock);
    return isWinner;
}

//the function to run a thread of player 
void* Player::playerTurn(void* win)
{
    bool winnerFound = (bool)win;
    pthread_mutex_lock(&turnLock);
    if(!winnerFound)
    {
        playerDraw();
        playerWin();
        playerDiscard();
    }
    pthread_mutex_unlock(&turnLock);
    pthread_exit(NULL);
}

std::string Player::showHand()const{
    std::string hand;

    hand = "Player " + std::to_string(playerID) + " Hand: ";
    hand += std::to_string(playerHand.held->value);
    //makes sure there is a second card before concat to string
    if(playerHand.drawn)
        hand += ", " + std::to_string(playerHand.drawn->value);

    return hand;
}

void Player::resetWin(){isWinner = false;}

void Player::changeSeed(int newSeed){randSeed = newSeed;}

//initiate mutex locks
void Player::initLocks()
{
    if(pthread_mutex_init(&drawLock, NULL) != 0){
        gameLog("could not Initiate Draw Lock");
        EXIT_FAILURE;
    }
    if(pthread_mutex_init(&winLock, NULL) != 0){
        gameLog("could not Initiate Win Lock");
        EXIT_FAILURE;
    }
    if(pthread_mutex_init(&discardLock, NULL) != 0){
        gameLog("could not Initiate Win Lock");
        EXIT_FAILURE;
    }
    if(pthread_mutex_init(&turnLock, NULL) != 0){
        gameLog("could not Initiate Win Lock");
        EXIT_FAILURE;
    }
}