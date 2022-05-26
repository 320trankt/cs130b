CC = g++

BINARIES: prog3

prog3: main.o dnaCheck.o 
	g++ -o prog3 main.o dnaCheck.o 

main.o: main.cpp
	g++ -c main.cpp

dnaCheck.o: dnaCheck.cpp 
	g++ -c dnaCheck.cpp

clean:
	/bin/rm -f prog3 *.o