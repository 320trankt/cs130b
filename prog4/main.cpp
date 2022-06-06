#include <iostream>
#include <fstream>
#include <sstream>
#include "algorithms.h"

using namespace std;

int main(int argc, char* argv[]) {

    //////////////////////////////////////////
    //runs all input test files at once without use of command line argument
    //note: assumes test files are in relative directory testData/
    string filenameBase = "testData/input_";
    string fileName;
    for (int i = 1; i < 6; i++){
        fileName = filenameBase + to_string(i) + ".txt";
        ifstream inputPoints(fileName); //filename is input as first argument to main
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
        tuple<double, double, double> model = ransac(sample, 60);
        cout<<get<0>(model)<<" "<<get<1>(model)<<" "<<get<2>(model)<<endl;
    }
    /////////////////////////////////////////

    ////////////////////////////////////////
    //intended use: input points file is passed in as command line argument
    /* ifstream inputPoints(argv[1]); //filename is input as first argument to main
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
    tuple<double, double, double> model = ransac(sample, 1000);
    cout<<get<0>(model)<<" "<<get<1>(model)<<" "<<get<2>(model)<<endl; */
    ///////////////////////////////////////
    return 0; // done
}