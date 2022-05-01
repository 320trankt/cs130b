CC = g++

BINARIES: dijkstra

dijkstra: main.o graph.o point.o edge.o
	g++ -o dijkstra main.o graph.o point.o edge.o

main.o: main.cpp
	g++ -c main.cpp

graph.o: graph.cpp 
	g++ -c graph.cpp

point.o: point.cpp
	g++ -c point.cpp

edge.o: edge.cpp
	g++ -c edge.cpp

clean:
	/bin/rm -f dijkstra *.o