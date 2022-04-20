#include <iostream>
#include <fstream>
#include <sstream>
#include "hull.h"

using namespace std;

int main(int argc, char* argv[]) {
    ifstream inputPoints(argv[1]); //filename is input as first argument to main
    string line;
    getline(inputPoints, line);
    int numPoints = stoi(line); // get first line of input file as number of points
    hull inputHull;
    int indexCounter = 0;
    while(getline(inputPoints, line)){ // get entire line into "line" variable
        point p;
        p.index = indexCounter;
        stringstream currentLine(line);
        string value;
        getline(currentLine, value, ',');
        p.x = stod(value);
        getline(currentLine, value);
        p.y = stod(value);
        inputHull.addPoint(p);
        indexCounter++;
    }
    vector<point> convexHullPoints = inputHull.quickHull();
    inputHull.printHull();
    return 0; // done
}