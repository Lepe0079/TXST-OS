pageSim: main.o pages.o
	g++ -g main.o pages.o -o pageSim

main.o: main.cpp
	g++ -g -c main.cpp

pages.o: pages.cpp pages.h
	g++ -g -c pages.cpp

clean:
	rm *.o pageSim