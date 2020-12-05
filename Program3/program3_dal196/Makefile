pageSim: main.o pages.o
	g++ -g main.o pages.o -o pageSim -std=c++11

main.o: main.cpp
	g++ -g -c main.cpp -std=c++11

pages.o: pages.cpp pages.h
	g++ -g -c pages.cpp -std=c++11

clean:
	rm *.o pageSim
