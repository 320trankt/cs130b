#include <iostream>
#include <fstream>
#include <sstream>
#include "algorithms.h"

using namespace std;

int main(int argc, char* argv[]) {

    //////////////////////////////////////////
    //runs all input test files at once without use of command line argument
    //note: assumes test files are in relative directory testData/
    /* string filenameBase = "testData/input_";
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
        double epsilon = 0.30;
        double p = 0.95;
        int numTrials = (int) (log(1-p))/(log(1-pow(1-epsilon, 3)));
        tuple<double, double, double> model = randomizedBestFit(sample, numTrials);
        cout<<get<0>(model)<<" "<<get<1>(model)<<" "<<get<2>(model)<<endl;
    } */
    /////////////////////////////////////////

    ////////////////////////////////////////
    //intended use: input points file is passed in as command line argument
    if (argc != 2){
        cerr<<"Failed to supply path to input file. Try again."<<endl;
        return 1;
    }
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
    double epsilon = 0.30;// assume 30% of data points are outliers
    double p = 0.95; // aim for 95% chance of generating good seed across numTrials runs
    int numTrials = (int) (log(1-p))/(log(1-pow(1-epsilon, 3))); // solve for numTrials given epsilon and p
    tuple<double, double, double> model = randomizedBestFit(sample, numTrials); // generate best fit model
    cout<<get<0>(model)<<" "<<get<1>(model)<<" "<<get<2>(model)<<endl; // output coefficients such that y = ax^2 + bx + c
    ///////////////////////////////////////
    return 0; // done
}