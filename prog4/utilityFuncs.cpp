#include "utilityFuncs.h"
#include <stdexcept>
#include <limits>

using namespace std;

//returns the line ax+by+c=0 between the points p1 and p2 in the form tuple<a, b, c>
tuple<double, double, double> getLineBetweenPoints(point p1, point p2){
    //a = y1 - y2
    double a = p1.y - p2.y;
    //b = x2-x1
    double b = p2.x - p1.x;
    //c = x1y2 - x2y1
    double c = (p1.x*p2.y) - (p2.x*p1.y);

    return(make_tuple(a, b, c));
}

double findDistanceToLine(tuple<double,double,double> line, point p){
    double a = get<0>(line);
    double b = get<1>(line);
    double c = get<2>(line);
    double distance = (abs((a*p.x) + (b*p.y) + c))/(sqrt(pow(a, 2) + pow(b, 2)));
    return distance;
}

point findFarthestPoint(point a, point b, vector<point> points){
    double maxDistance = 0.0;
    point p;
    tuple<double, double, double> line = getLineBetweenPoints(a, b);
    for (point i : points){
        if(findDistanceToLine(line, i) > maxDistance){
            maxDistance = findDistanceToLine(line, i);
            p.setEqual(i);
        }
    }
    return p;
}

int directionOfPoint(point a, point b, point p){
    //center point a on (0,0)
    /* b.x = b.x - a.x;
    b.y = b.y - a.y;
    p.x = p.x - a.x;
    p.y = p.y - a.y;

    double cross_product = b.x*p.y - b.y*p.x;
 */
    double cross_product = (p.y - a.y) * (b.x - a.x) - (b.y - a.y) * (p.x - a.x);
    if(cross_product > 0){
        return 1;
    }
    else if (cross_product < 0){
        return -1;
    }
    else{
        return 0;
    }
}

vector<point> getAllPointsOnSide(point a, point b, vector<point> inputPoints, int side){
    vector<point> outputPoints;
    //left points
    if (side < 0){
        for(point i : inputPoints){
            if(directionOfPoint(a,b,i) < 0){
                outputPoints.push_back(i);
            }
        }
    }
    else if(side > 0){
        for(point i : inputPoints){
            if(directionOfPoint(a,b,i) > 0){
                outputPoints.push_back(i);
            }
        }
    }
    return outputPoints;
}

double area(point a, point b, point c){
    return abs((a.x*(b.y-c.y) + b.x*(c.y-a.y)+ c.x*(a.y-b.y))/2.0);
}

bool isPointInside(point p, point a, point b, point c){
    //point p is inside a,b,c if the areas of the triangles it forms with a, b, and c sum up to area of triangle a,b,c
    double areaABC = area(a, b, c);
    double areaPAB = area(p, a, b);
    double areaPAC = area(p, a, c);
    double areaPBC = area(p, b, c);

    return std::fabs(areaABC - (areaPAB + areaPAC + areaPBC)) <= std::numeric_limits<double>::epsilon();
}

vector<point> getAllPointsOutside(point a, point b, point c, vector<point> inputPoints){
    vector<point> outsidePoints;
    for (point i : inputPoints){
        if(!isPointInside(i, a, b, c)){
            outsidePoints.push_back(i);
        }
    }
    return outsidePoints;
}

