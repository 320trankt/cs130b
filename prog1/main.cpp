#include <iostream>
#include "hull.h"
#include "utilityFuncs.h"

using namespace std;

int main(int argc, char* argv[]) {
    ifstream inputPoints(argv[1]); //filename is input as first argument to main
    string line;
    getline(inputPoints, line, "\n");
    int numPoints = stoi(line); // get first line of input file as number of points
    vector<pair<double, double>> points;
    while(getline(inputPoints, line, "\n")){ // get entire line into "line" variable
        pair<double, double> point;
        istringstream currentLine(line);
        string value;
        getline(currentLine, value, ",");
        point.first = stod(value);
        getline(currentLine, value, "\n");
        point.second = stod(value);
        points.push_back(point);
    }
    //at this point points should be a vector containing all points from input file as pair<double, double>
    
}