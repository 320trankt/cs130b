#include "edge.h"

edge::edge(){
    this->p1 = -1;
    this->p2 = -1;
    this->weight = 0.0;
}

edge::edge(int a, int b){
    this->p1 = a;
    this->p2 = b;
}

void edge::operator =(const edge& e){
    this->p1 = e.p1;
    this->p2 = e.p2;
    this->weight = e.weight;
}