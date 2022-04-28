#include "hull.h"
#include <iostream>
#include <algorithm>
#include <time.h>

void hull::addPoint(point p){
    inputPoints.push_back(p);
}

vector<point> hull::quickHull(){
    //clock_t t;
    //t = clock();
    point maxX(-1, static_cast<double>(INT_MIN), 0.0);
    point minX(-1, static_cast<double>(INT_MAX), 0.0);
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
    vector<point> leftSidePoints = getAllPointsOnSide(minX, maxX, inputPoints, 1);
    vector<point> rightSidePoints = getAllPointsOnSide(minX, maxX, inputPoints, -1);
    recursiveHelper(minX, maxX, leftSidePoints);
    recursiveHelper(minX, maxX, rightSidePoints);
    //t = clock() - t;
    //cout<<"Runtime for "<<inputPoints.size()<<" points: "<<t<<" clock."<<endl;
    return hullPoints;
}

void hull::recursiveHelper(point a, point b, vector<point> points){
    if (points.size() == 0){
        return;
    }
    point p = findFarthestPoint(a, b, points);
    hullPoints.push_back(p);
    numPoints++;
    std::vector<point> outsidePoints = getAllPointsOutside(a, b, p, points);
    std::vector<point> apLeftPoints = getAllPointsOnSide(a, p, outsidePoints, 1);
    std::vector<point> bpRightPoints = getAllPointsOnSide(b, p, outsidePoints, -1);
    recursiveHelper(a, p, apLeftPoints);
    recursiveHelper(b, p, bpRightPoints);
    return;
}

void hull::sortHull(){
    point lowestY(-1, static_cast<double>(INT_MAX), static_cast<double>(INT_MAX));
    for (point i : hullPoints){
        if (i.y < lowestY.y){
            lowestY.setEqual(i);
        }else if (i.y == lowestY.y){
            if (i.x < lowestY.x){
                lowestY.setEqual(i);
            }
        }
    }
    sortedHullPoints.push_back(lowestY);
    vector<point> rightSideUp;
    vector<point> leftSideDown;
    for (point i : hullPoints){//go up right side
        if (i.x > lowestY.x){
            rightSideUp.push_back(i);
        }
        if(i.x < lowestY.x){
            leftSideDown.push_back(i);
        }
    }
    std::sort(rightSideUp.begin(), rightSideUp.end());
    for (point i : rightSideUp){
        sortedHullPoints.push_back(i);
    }
    std::sort(leftSideDown.begin(), leftSideDown.end());
    std::reverse(leftSideDown.begin(), leftSideDown.end());
    for (point i : leftSideDown){
        sortedHullPoints.push_back(i);
    }
    return;
}

void hull::printHull(){
    cout<<numPoints<<endl;
    sortHull();
    for(point i : sortedHullPoints){
        cout<<i.index<<", "<<i.x<< ", "<< i.y <<endl;
    }
    return;
}