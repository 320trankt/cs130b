#include <string>
#include <cmath>
#include <climits>
#include <vector>
#include <tuple>
#include <algorithm>
#include <armadillo>
#include "utilityFuncs.h"
#include "matrix.c"

using namespace std;

double getMedianError(vector<point> inputSet);

tuple<double, double, double> getModel(vector<point> inputSet);

tuple<double, double, double> ransac(vector<point> inputSet, double tolerance)