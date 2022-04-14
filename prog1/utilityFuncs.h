#include <string>


//returns the line ax+by+c=0 between the points a and b in the form tuple<a, b, c>
tuple<double, double, double> getLine(tuple<int, double, double> a, tuple<int, double, double> b); 

//returns the euclidean distance between the line denoted by tuple<a, b, c> such that ax+by+c=0 and point c
double findDistanceToLine(tuple<double,double,double> line, tuple<int, double, double> c);

//returns the point within the input vector of points which is the farthest from the line between points a and b
tuple<int, double, double> findFarthestPoint(tuple<int, double, double> a, tuple<int, double, double> b, vector<tuple<int, double, double>> points);