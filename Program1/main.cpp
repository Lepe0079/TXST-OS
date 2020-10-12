#include "gameLog.h"
#include "Player.h"

int main()
{
    bool win = false;
 
    pthread_t threads[2];

    Deck mainDeck(1);
    Player player1(1,1,&mainDeck);
    Player player2(1,1,&mainDeck);

    Player players[] = {player1, player2};

    
    
    return 0;
}