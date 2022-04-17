CC = g++

BINARIES: hull

hull: main.o hull.o utilityFuncs.o point.o
	g++ -o hull main.o hull.o utilityFuncs.o point.o

main.o: main.cpp
	g++ -c main.cpp

hull.o: hull.cpp 
	g++ -c hull.cpp

utilityFuncs.o: utilityFuncs.cpp
	g++ -c utilityFuncs.cpp

point.o: point.cpp
	g++ -c point.cpp

clean:
	/bin/rm -f hull *.o