#include "hull.h"

void hull::addPoint(pair<double, double> inputPoint, int index){
    points.push_back(std::make_tuple(index, inputPoint.first, inputPoint.second));
}

vector<tuple<int, double, double>> hull::quickHull(){
    tuple<int, double, double> maxX = make_tuple(0, static_cast<double>(std::INT_MIN), 0.0);
    tuple<int, double, double> minX = make_tuple(0, static_cast<double>(std::INT_MAX), 0.0);
    for (tuple<int, double, double> i : points){ // iterates through all points and finds min and max x points
        if (get<1>(i) > maxX){
            get<0>(maxX) = get<0>(i);
            get<1>(maxX) = get<1>(i);
            get<2>(maxX) = get<2>(i);
        }
        if (get<1>(i) < minX){
            get<0>(minX) = get<0>(i);
            get<1>(minX) = get<1>(i);
            get<2>(minX) = get<2>(i);
        }
    }
}
