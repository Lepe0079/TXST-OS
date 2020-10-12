#ifndef PLAYER_H
#define PLAYER_H


#include "gameLog.h"
#include "Deck.h"
#include "stdlib.h"
#include <pthread.h>
#include <random>


class Player
{
    private:
        struct Hand
        {
            Card* held = nullptr;
            Card* drawn = nullptr;
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


        static void* playerTurn(void *);
        void threadEntry(bool*);

        std::string showHand() const;
        void resetWin();
        void changeSeed(int);
        void initLocks();
};
#endif