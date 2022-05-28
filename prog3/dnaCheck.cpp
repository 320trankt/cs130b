#include "dnaCheck.h"

dnaCheck::dnaCheck(){
    matchValue = 2.0;
    changeValue = -0.5;
    deleteValue = -1.0;
}

dnaCheck::dnaCheck(string seq1, string seq2){
    matchValue = 2.0;
    changeValue = -0.5;
    deleteValue = -1.0;
    this->seq1 = seq1;
    this->seq2 = seq2;
}

dnaCheck::dnaCheck(string seq1, string seq2, double m, double c, double d){
    matchValue = m;
    changeValue = c;
    deleteValue = d;
    this->seq1 = seq1;
    this->seq2 = seq2;
}

double dnaCheck::isMatching(char b1, char b2){
    if (b1 == b2){
        return matchValue;
    }else{
        return changeValue;
    }
}

void dnaCheck::fillInProfitTable(){
    // Fill out profit table here: bottom-up approach

    //resize empty profit table to # of rows = # of chars in seq1 + "_" char, cols = # of chars in seq2 + "_" char
    profitTable.resize(seq1.size()+1, vector<double>(seq2.size()+1));

    //profit of deleting all characters in seq2 is deleteValue * # of chars deleted
    for (int i = 0; i < seq1.size() + 1; i++){
        profitTable[i][0] = deleteValue * i;
    }
    //profit of deleting all characters in seq1 is deleteValue * # of chars deleted
    for (int j = 0; j < seq2.size() + 1; j++){
        profitTable[0][j] = deleteValue * j;
    }
    //Fill out rest of table here
    for (int i = 1; i < seq1.size() + 1; i++){
        for (int j = 1; j < seq2.size()+1; j++){
            //Current profit cell is equal to the max of the diagonal left, left, and above cell
            //I.e. maximum of matching current chars, deleting either char, or changing one char
            double match = profitTable[i-1][j-1] + isMatching(seq1.at(i-1), seq2.at(j-1));//getScore accounts for both matching and for changing one base to other
            double del = profitTable[i-1][j] + deleteValue;//profit of deleting char from seq1
            double insert = profitTable[i][j-1] + deleteValue;//profit of deleting char from seq2
            profitTable[i][j] = max({match, del, insert});//take max option from three as profit for current cell
        }
    }
    
    // Rebuild updated seq1 and seq2 strings with deletions and substitutions from profit table

    seq1Updated="";
    seq2Updated="";

    int i = seq1.size();
    int j = seq2.size();
    
    double currentProfit = profitTable[i][j];
    double leftProfit = profitTable[i-1][j];
    double upProfit = profitTable[i][j-1];
    double leftDiagProfit = profitTable[i-1][j-1];

    //approach builds seq1 and seq2 updated versions backwards from the most significant entry in the cell
    //starts at the bottom rightmost cell, finds which adjacent cell its current value came from, then traces
    //backwards to it until the top leftmost cell of the table is reached
    while ((i > 0) || (j > 0)){//while there are still chars in either sequence
        currentProfit = profitTable[i][j];
        if (i > 0){//if statements catch out of bound error
            leftProfit = profitTable[i-1][j];
        }
        if (j > 0){
            upProfit = profitTable[i][j-1];
        }
        if ((i > 0) && (j > 0)){
            leftDiagProfit = profitTable[i-1][j-1];
        }
        if ((i > 0)&&(j > 0)&&(currentProfit == (leftDiagProfit + matchValue))){//if current profit was reached by matching identical bases
            seq1Updated = seq1.at(i-1) + seq1Updated;
            seq2Updated = seq2.at(j-1) + seq2Updated;
            i = i - 1;
            j = j - 1;
        }else if((i > 0)&&(j > 0)&&(currentProfit == (leftDiagProfit + changeValue))){//if current profit was reached by changing a base
            seq1Updated = seq1.at(i-1) + seq1Updated;
            seq2Updated = "R" + seq2Updated;
            i = i - 1;
            j = j - 1;
        }else if((i > 0) && (currentProfit == (leftProfit + deleteValue))){//if current profit was reached by deleting a char from seq2
            seq1Updated = seq1.at(i-1) + seq1Updated;
            seq2Updated = "_" + seq2Updated;
            i = i - 1;
        }else if ((j > 0) && (currentProfit == (upProfit + deleteValue))){//if current profit was reached by deleting a char from seq1
            seq1Updated = "_" + seq1Updated;
            seq2Updated = seq2.at(j-1) + seq2Updated;
            j = j - 1;
        }
    }

}