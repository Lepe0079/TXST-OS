#include "Deck.h"
#include <iostream>
#include <algorithm>
#include <cassert>

Deck::Deck():seed(1){
    buildDeck();
}

Deck::Deck(int newSeed):seed(newSeed){
    buildDeck(seed);
}

//creates new deck using a seed
void Deck::buildDeck(int newSeed){
    seed = newSeed;
    if(!isEmpty()){
        cDeck.clear();
        currentCards = 0;
    }
    for(int s = 0; s < 4; ++s){
        for(int n = 1; n < 14; ++n){
            Card *addCard = new Card; 
            addCard->suit = suits[s];
            addCard->value = n;
            cDeck.push_front(addCard);
            ++currentCards;
        }
    }

    std::shuffle(std::begin(cDeck), 
                std::end(cDeck), std::default_random_engine(seed));

}
//overload of default seed buildDeck
void Deck::buildDeck(){
    seed = seed + seed;
    if(!isEmpty()){
        cDeck.clear();
        currentCards = 0;
    }
    for(int s = 0; s < 4; ++s){
        for(int n = 1; n < 14; ++n){
            Card *addCard = new Card; 
            addCard->suit = suits[s];
            addCard->value = n;
            cDeck.push_front(addCard);
            ++currentCards;
        }
    }

    std::shuffle(std::begin(cDeck), 
                std::end(cDeck), std::default_random_engine(seed));

}
Card* Deck::getCard(){
    assert(!isEmpty());

    Card *top = cDeck.front();
    cDeck.pop_front();
    --currentCards;
    return top;
}

void Deck::addCard(Card *cardInsert){
    assert(currentCards != DECKSIZE);
    cDeck.push_back(cardInsert);
    ++currentCards;
}

bool Deck::isEmpty()const{
    return cDeck.empty();
}

int Deck::getRemaining()const{
    return currentCards;
}

std::string Deck::showDeck()const 
{
    std::string s;
    for (int i = 0; i < currentCards; ++i)
    {
        s += "| " + std::to_string(cDeck.at(i)->value) + " ";
    }
    s += "|";
    return s;
}