#include "hull.h"
#include <iostream>

void hull::addPoint(point p){
    inputPoints.push_back(p);
}

vector<point> hull::quickHull(){
    point maxX(-1, static_cast<double>(INT_MAX), 0.0);
    point minX(-1, static_cast<double>(INT_MIN), 0.0);
    for (point i : inputPoints){ // iterates through all points and finds min and max x points
        if (i.x > maxX.x){
            maxX.setEqual(i);
        }
        if (i.x < minX.x){
            minX.setEqual(i);
        }
    }
    hullPoints.push_back(maxX);
    numPoints++;
    hullPoints.push_back(minX);
    numPoints++;
    //implement recursive step here
    vector<point> leftSidePoints = getAllPointsOnSide(minX, maxX, inputPoints, -1);
    vector<point> rightSidePoints = getAllPointsOnSide(minX, maxX, inputPoints, 1);
    recursiveHelper(minX, maxX, leftSidePoints);
    recursiveHelper(minX, maxX, rightSidePoints);
    return hullPoints;
}

void hull::recursiveHelper(point a, point b, vector<point> points){
    
    point p = findFarthestPoint(a, b, points);
    hullPoints.push_back(p);
    numPoints++;
    std::vector<point> outsidePoints = getAllPointsOutside(a, b, p, points);
    if(outsidePoints.size() == 0){
        return;
    }else{
        recursiveHelper(a, p, outsidePoints);
        recursiveHelper(b, p, outsidePoints);
        return;
    }
}

void hull::printHull(){
    cout<<numPoints<<endl;
    for(point i : hullPoints){
        cout<<i.index<<", "<<i.x<< ", "<< i.y <<endl;
    }
    return;
}