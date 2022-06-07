#include <string>
#include <cmath>
#include <climits>
#include <vector>
#include <tuple>
#include <algorithm>
#include <armadillo>
#include "point.h"

using namespace std;

double getDistanceToModel(point p, tuple<double,double,double> model); // returns absolute distance between point p and the parabola described by the model y = ax^2 + bx + c

double getMedianError(vector<point> &inputSet); // returns the median error of a set of points based on distance from a model

tuple<double, double, double> leastSquares(vector<point> &inputSet); // takes the least square quadratic regression of a set of points to generate a parabolic model y = ax^2 + bx + c

tuple<double, double, double> randomizedBestFit(vector<point> &inputSet, int numTrials); // combines RANSAC procedure and least squares fit to generate good fit model to input data set