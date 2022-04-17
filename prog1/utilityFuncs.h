#include <string>
#include <math>
#include <climits>
#include "hull.h"
#include "point.h"

using namespace std;

//returns the line ax+by+c=0 between the points a and b in the form tuple<a, b, c>
tuple<double, double, double> getLine(point a, point b); 

//returns the euclidean distance between the line denoted by tuple<a, b, c> such that ax+by+c=0 and point c
double findDistanceToLine(tuple<double,double,double> line, point p);

//returns the point within the input vector of points which is the farthest from the line between points a and b
point findFarthestPoint(point a, point b, vector<point> points);

//returns direction of point p in relation to line between a and b, -1 for left, 1 for right, 0 for colinear
int directionOfPoint(point a, point b, point p);

//returns all points from inputPoints that are on the side of the line between a and b specified by int side (1 for right, -1 for left, 0 for colinear)
vector<point> getAllPointsOnSide(point a, point b, vector<point> inputPoints, int side);

//returns the area of the triangle created by points a, b, and c
double area(point a, point b, point c);

//returns true if point p is inside triangle created by points a, b, and c
bool isPointInside(point p, point a, point b, point c);

//returns vector of all points from inputPoints which are outside the triangle formed by points a, b, and c
vector<point> getAllPointsOutside(point a, point b, point c, vector<point> inputPoints);