#ifndef PLAYER_H
#define PLAYER_H


#include "gameLog.cpp"
#include "stdlib.h"
#include <pthread.h>
#include <random>


class Player
{
    private:
        struct Hand
        {
            Card* held;
            Card* drawn;
        };
        int playerID;
        static int randSeed;
        bool isWinner = false;
        Hand playerHand;
        Deck* gameDeck;
        pthread_mutex_t drawLock, discardLock, winLock, turnLock;


    public:
        Player();
        Player(int, int, Deck*);

        void playerDraw();
        void playerDiscard();
        bool playerWin();
      
        void* playerTurn(void*);

        std::string showHand() const;
        void resetWin();
        void changeSeed(int);
        void initLocks();
};
#endif