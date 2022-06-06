#include <string>
#include <cmath>
#include <climits>
#include <vector>
#include <tuple>
#include <algorithm>
#include <armadillo>
#include "point.h"

using namespace std;

double getDistanceToModel(point p, tuple<double,double,double> model);

double getMedianError(vector<point> &inputSet);

tuple<double, double, double> leastSquares(vector<point> &inputSet);

tuple<double, double, double> ransac(vector<point> &inputSet, int numTrials);