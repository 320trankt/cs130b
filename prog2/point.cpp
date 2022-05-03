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
    //distance = std::numeric_limits<double>::infinity();
}

void point::setEqual(point p){
    index = p.index;
    x = p.x;
    y = p.y;
    distance = p.distance;
    adj = p.adj;
    shortestPath = p.shortestPath;
}

void point::operator =(const point& p){
    this->index = p.index;
    this->x = p.x;
    this->y = p.y;
    this->distance = p.distance;
    this->adj = p.adj;
    this->shortestPath = p.shortestPath;
}