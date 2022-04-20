#include <string>
#include "utilityFuncs.h"

class hull{
    public:
        int numPoints;
        std::vector<point> inputPoints;
        std::vector<point> hullPoints;
        std::vector<point> sortedHullPoints;
        hull() : numPoints(0) {}
        void addPoint(point p);
        std::vector<point> quickHull(); // returns vector of points containing points on convex hull in form tuple<index, x-coord, y-coord>
        void recursiveHelper(point a, point b, std::vector<point> points);
        void sortHull();
        void printHull();
};