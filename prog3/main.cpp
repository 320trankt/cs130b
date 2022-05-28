#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <getopt.h>
#include "dnaCheck.h"

using namespace std;

int main(int argc, char* argv[]) {
    dnaCheck test;//initialize dnaCheck object
    string pathToSeq1a;//string will be used as path to seq1a input file
    string pathToSeq1b;//string will be used as path to seq1b input file
    int opt;//opt used to handle flags in command line input
    while ((opt = getopt(argc, argv, "m:c:d:1:2:")) != -1){
        switch (opt){
            case 'm'://if m is supplied as an argument
                test.matchValue = stod(optarg);//set match value to m
            case 'c':
                test.changeValue = stod(optarg);
            case 'd':
                test.deleteValue = stod(optarg);
            case '1':
                pathToSeq1a = optarg;
            case '2':
                pathToSeq1b = optarg;
        }
    }
    string line;
    ifstream input1;
    ifstream input2;
    input1.open(pathToSeq1a);
    input2.open(pathToSeq1b);
    getline(input1, line);
    test.seq1 = line;//set seq1 as line from seq1a input file
    getline(input2, line);
    test.seq2 = line;//set seq2 as line from seq1b input file
    input1.close();
    input2.close();
    test.fillInProfitTable();//fills in profit table bottom-up approach
    cout<<test.profitTable.back().back()<<endl;//max profit for full strings is bottom rightmost entry in profit table
    cout<<test.seq1Updated<<endl;//output updated seq1 with substitutions and insertions
    cout<<test.seq2Updated<<endl;
    return 0; // done
}