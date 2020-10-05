pwar: main.o Deck.o
	g++ main.o Deck.o -o pwar -lpthread

main.o: main.cpp Card.h
	g++ -c  main.cpp -lpthread

Deck.o: Deck.cpp Deck.h
	g++ -c Deck.cpp

clean:
	rm *.o pwar game.txt