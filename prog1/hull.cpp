#include "hull.h"

void hull::addPoint(point p){
    inputPoints.push_back(p);
}

vector<point> hull::quickHull(){
    point maxX(-1, static_cast<double>(std::INT_MAX), 0.0);
    point minX(-1, static_cast<double>(std::INT_MIN), 0.0);
    for (point i : points){ // iterates through all points and finds min and max x points
        if (i.x > maxX.x){
            maxX.setEqual(i);
        }
        if (i.x < minX.x){
            minX.setEqual(i);
        }
    }
    hullPoints.push_back(maxX);
    hullPoints.push_back(minX);
    //implement recursive step here
    vector<point> leftSidePoints = getAllPointsOnSide(minX, maxX, points, -1);
    vector<point> rightSidePoints = getAllPointsOnSide(minX, maxX, points, 1);
    recursiveHelper(minX, maxX, leftSidePoints);
    recursiveHelper(minX, maxX, rightSidePoints);
    return hullPoints;
}

vector<point> hull::recursiveHelper(point a, point b, vector<point> points){
    point p = findFarthestPoint(a, b, points);
    
}
