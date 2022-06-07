#include "point.h"

point::point(){
    x = 0.0;
    y = 0.0;
}

point::point(double p_x, double p_y){
    x = p_x;
    y = p_y;
}

void point::operator= (const point &other){
    x = other.x;
    y = other.y;
    distanceToLine = other.distanceToLine;
}

bool point::operator< (const point &other) const{
    return distanceToLine < other.distanceToLine;
}