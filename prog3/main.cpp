#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "dnaCheck.h"

using namespace std;

int main(int argc, char* argv[]) {
    ifstream inputResults(argv[1]); //filename is input as first argument to main
    string line;

    int testCounter = 1;

    double m;
    double c;
    double d;
    string seq1aFile;
    string seq1bFile;
    string seq1a;
    string seq1b;
    ifstream input1;
    ifstream input2;
    string pathToSeq1a;
    string pathToSeq1b;
    while(getline(inputResults, line)){
        stringstream currentLine(line);
        string value;
        getline(currentLine, value, ' ');//get m=2
        m = stof(value.substr(value.find('=')+1));//get 2
        getline(currentLine, value, ' ');//get c=-0.2
        c = stof(value.substr(value.find('=')+1));
        getline(currentLine, value, ' ');
        d = stof(value.substr(value.find('=')+1));
        getline(currentLine, value, ' ');
        seq1aFile = value.substr(value.find('=')+1);
        getline(currentLine, value, ' ');
        seq1bFile = value.substr(value.find('=')+1);

        //cout<<"yuh1"<<endl;

        pathToSeq1a = "testData/" + seq1aFile + ".txt";
        pathToSeq1b = "testData/" + seq1bFile + ".txt";
        input1.open(pathToSeq1a);
        input2.open(pathToSeq1b);
        getline(input1, line);
        seq1a = line;
        getline(input2, line);
        seq1b = line;
        input1.close();
        input2.close();
        dnaCheck test(seq1a, seq1b, m, c, d);

        //cout<<"yuh2"<<endl;
        
        test.fillInProfitTable();
        
        //cout<<"yuh3"<<endl;
        
        cout<<"Test "<<testCounter<<": "<<test.profitTable.back().back()<<endl;
        
        //cout<<"yuh4"<<endl;
        
        testCounter++;
    }
    return 0; // done
}