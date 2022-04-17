#include "point.cpp"

using namespace std;

point::point(){
    index = -1;
    x = 0.0;
    y = 0.0;
}

point::point(int index, double x, double y){
    this.index = index;
    this.x = x;
    this.y = y;
}

void point::setEqual(point p){
    this.index = p.index;
    this.x = p.x;
    this.y = p.y;
    return;
}