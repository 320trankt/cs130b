#include <string>

class hull{
    public:
        int numPoints;
        vector<tuple<int, double, double>> points;
        hull() : numPoints(0) {}
        void findHull(vector<pair<double, double>> inputPoints);
};