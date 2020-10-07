pwar: main.o Deck.o
	g++ main.o Deck.o Player.o gameLog.o -o pwar -lpthread

main.o: main.cpp
	g++ -c  main.cpp -lpthread

Deck.o: Deck.cpp Deck.h
	g++ -c Deck.cpp

Player.o: Player.cpp Player.h
	g++ -c Player.cpp -lpthread

gameLog.o: gameLog.cpp
	g++ -c gameLog.cpp

clean:
	rm *.o pwar game.txt