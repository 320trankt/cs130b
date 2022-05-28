#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "dna.h"

using namespace std;

class dnaCheck{
    public:
        dnaCheck();
        dnaCheck(string seq1, string seq2);
        dnaCheck(string seq1, string seq2, double m, double c, double d);
        string seq1;
        string seq2;
        string seq1Updated;
        string seq2Updated;
        double matchValue;
        double changeValue;
        double deleteValue;
        vector<vector<double>> profitTable;
        double isMatching(char b1, char b2);
        void fillInProfitTable();
};