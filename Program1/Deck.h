#ifndef DECK_H
#define DECK_H

#include <vector>
#include <deque>
#include <random>
#include "Card.h"

class Deck
{
    private:
        static const int DECKSIZE = 52; 
        int currentCards = 0;
        int seed; 
        std::deque<Card*> cDeck;
        char suits[4] = {'C', 'D', 'H', 'S'};

    public:
        Deck();
        Deck(int);
        void buildDeck(int);
        void buildDeck();
        Card* getCard();
        void addCard(Card*);

        bool isEmpty() const;
        int getRemaining() const;
        std::string showDeck() const;
};

#endif