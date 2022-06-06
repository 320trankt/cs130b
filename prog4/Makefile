CC = g++

BINARIES: prog4

prog4: main.o algorithms.o point.o
	g++ -o prog4 main.o algorithms.o point.o -O2 -larmadillo -llapack -lblas

main.o: main.cpp
	g++ -c main.cpp

algorithms.o: algorithms.cpp 
	g++ -c algorithms.cpp

point.o: point.cpp
	g++ -c point.cpp

clean:
	/bin/rm -f prog4 *.o