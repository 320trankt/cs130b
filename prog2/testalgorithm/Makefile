CC = g++

BINARIES: dijkstra

dijkstra: main.o graph2.o point.o edge.o
	g++ -o dijkstra main.o graph2.o point.o edge.o

main.o: main.cpp
	g++ -c main.cpp

graph2.o: graph2.cpp 
	g++ -c graph2.cpp

point.o: point.cpp
	g++ -c point.cpp

edge.o: edge.cpp
	g++ -c edge.cpp

clean:
	/bin/rm -f dijkstra *.o