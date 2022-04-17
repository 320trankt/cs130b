#include "point.h"

point::point(){
    index = -1;
    x = 0.0;
    y = 0.0;
}

point::point(int p_index, double p_x, double p_y){
    index = p_index;
    x = p_x;
    y = p_y;
}

void point::setEqual(point p){
    index = p.index;
    x = p.x;
    y = p.y;
}