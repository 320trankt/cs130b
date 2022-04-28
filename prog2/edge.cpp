#include "edge.h"

edge::edge(){
    this->a = -1;
    this->b = -1;
    this->weight = 0.0;
}

edge::edge(int a, int b){
    this->a = a;
    this->b = b;
    setWeight();
}

void edge::setWeight(){
    //weight = distanceBetweenPoints(a, b);
    return;
}