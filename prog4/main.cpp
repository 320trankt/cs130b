#include <iostream>
#include <fstream>
#include <sstream>
#include "algorithms.h"

using namespace std;

int main(int argc, char* argv[]) {
    ifstream inputPoints(argv[1]); //filename is input as first argument to main
    string line;
    vector<point> sample;
    while(getline(inputPoints, line)){
        point p;
        stringstream currentLine(line);
        string value;
        getline(currentLine, value, ' ');
        p.x = stod(value);
        getline(currentLine, value);
        p.y = stod(value);
        sample.push_back(p);
    }
    tuple<double, double, double> model = ransac(sample, 10);
    cout<<get<0>(model)<<" "<<get<1>(model)<<" "<<get<2>(model)<<endl;
    return 0; // done
}