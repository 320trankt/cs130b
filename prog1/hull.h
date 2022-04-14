#include <string>
#include <climits>

class hull{
    public:
        int numPoints;
        vector<tuple<int, double, double>> points;
        hull() : numPoints(0) {}
        void addPoint(pair<double, double> inputPoint, int index);
        vector<tuple<int, double, double>> quickHull(); // returns vector of points containing points on convex hull in form tuple<index, x-coord, y-coord>
        string printHull();
};