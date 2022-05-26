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

/* void dnaCheck::getSimilarity(){
    for (int i = 0; i < seq1.size(); i++){
        for (int j = 0; j < seq2.size(); j++){
            profitTable[i][j] = -1.0;
        }
    }
}

double dnaCheck::recursiveHelper(int m, int n){
    if (m==0 || n==0){
        profitTable[m][n]=0;
        return 0;
    }else if(seq1.at(m) == seq2.at(n)){ // if bases match
        profitTable[m][n] = matchValue + recursiveHelper(m-1, n-1);
        seq1Updated += seq1.at(m);
        seq2Updated += seq2.at(n);
        return profitTable[m][n];
    }
}
 */
double dnaCheck::getScore(char b1, char b2){
    if (b1 == b2){
        return matchValue;
    }else{
        return changeValue;
    }
}

void dnaCheck::fillInProfitTable(){
    //cout<<"ohgod1"<<endl;

    profitTable.resize(seq1.size()+1, vector<double>(seq2.size()+1));

    //cout<<"ohgod2"<<endl;

    for (int i = 0; i < seq1.size() + 1; i++){
        profitTable[i][0] = changeValue * i;
    }
    //cout<<"ohgod2"<<endl;
    for (int j = 0; j < seq2.size() + 1; j++){
        profitTable[0][j] = changeValue * j;
    }
    //cout<<"ohgod3"<<endl;
    for (int i = 1; i < seq1.size() + 1; i++){
        //cout<<"ohgod4"<<endl;
        for (int j = 1; j < seq2.size()+1; j++){
            //cout<<"ohgod5"<<endl;
            double match = profitTable[i-1][j-1] + getScore(seq1.at(i-1), seq2.at(j-1));
            double del = profitTable[i-1][j] + deleteValue;
            double insert = profitTable[i][j-1] + deleteValue;
            profitTable[i][j] = max({match, del, insert}); 
            //cout<<"ohgod6"<<endl;
        }
    }
}