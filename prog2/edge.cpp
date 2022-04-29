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