#include <string>
#include <climits>
#include "point.h"
#include "utilityFuncs.h"

class hull{
    public:
        int numPoints;
        vector<point> inputPoints;
        vector<point> hullPoints;
        hull() : numPoints(0) {}
        void addPoint(point p);
        vector<point> quickHull(); // returns vector of points containing points on convex hull in form tuple<index, x-coord, y-coord>
        vector<point> recursiveHelper(point a, point b, vector<point> points);
        string printHull();
};