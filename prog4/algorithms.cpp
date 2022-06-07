#include "algorithms.h"

double getDistanceBetweenPoints(point p1, point p2){// get absolute distance between two points
    return sqrt(pow(p2.x - p1.x, 2.0) + pow(p2.y - p1.y,2.0));
}

tuple<double, double, double> getModel(vector<point> inputThree){// helper function to obtain the equation of a parabola from three input points stored in inputThree
    point p1 = inputThree[0];
    point p2 = inputThree[1];
    point p3 = inputThree[2];
    double x1 = p1.x;
    double y1 = p1.y;
    double x2 = p2.x;
    double y2 = p2.y;
    double x3 = p3.x;
    double y3 = p3.y;
    //use equation for coefficients of a parabolic equation from 3 points
    double denominator = (x1-x2) * (x1-x3) * (x2-x3);
    double a = (x3 * (y2-y1) + x2 * (y1-y3) + x1 * (y3-y2)) / denominator;
    double b = (x3*x3 * (y1-y2) + x2*x2 * (y3-y1) + x1*x1 * (y2-y3)) / denominator;
    double c = (x2 * x2 * (x3 * y1 - x1 * y3) + x2 * (x1 * x1 * y3 - x3 * x3 * y1) + x1 * x3 * (x3 - x1) * y2)/denominator;
    return make_tuple(a, b, c);
}

double calcYFromModel(double x, tuple<double, double, double> model){// helper function to calculate y value of point on parabola given by y = ax^2 + bx + c
    double a = get<0>(model);
    double b = get<1>(model);
    double c = get<2>(model);
    return ((a * pow(x, 2.0)) + (b * x) + c);
}

double getDistanceToModel(point p, tuple<double,double,double> model){ // function to calculate the absolute distance from a point p to a parabola modeled by y = ax^2 + bx + c
    double a = get<0>(model);
    double b = get<1>(model);
    double c = get<2>(model);
    double x = p.x;
    double y = p.y;
    //approach utilizes the distance formula between a parabola with equation y = ax^2 + bc + c, and point (x,y)
    //the distance between point (x,y) and y = ax^2+bc+c is d^2 = (x2 - x1)^2 + (y2 - y1)^2, so we use x = x and y = ax^2 + bx + c for the parabola for x1 and y1, and use the point's (x,y) for x2 and y2
    //derive the squared distance equation to minimize squared distance, resulting in a 3rd degree polynomial in x with roots that will yield the max or min values for the distance
    double coefficientx3 = 2.0 * pow(a,2.0);
    double coefficientx2 = 4.0 * a * b;
    double coefficientx = 2.0 + (4.0*a*c) - (4.0*a*y) + (2.0 * pow(b, 2.0));
    double coefficientconst = (2.0*b*c) - (2.0*x) - (2.0*b*y);
    arma::vec P;
    P.resize(4);
    P (0) = coefficientx3;
    P (1) = coefficientx2;
    P (2) = coefficientx;
    P (3) = coefficientconst;
    arma::cx_vec R = roots(P);
    //solve the 3rd degree polynomial to find the extreme roots x
    double minDistance = INFINITY;
    double currentDistance;
    double currentX;
    point p2;
    //consider extreme roots of distance equation on parabola to find minimum distance value
    for (int i = 0; i < R.n_elem; i++){
        currentX = std::arg(R(i));
        p2.x = currentX;
        p2.y = calcYFromModel(p2.x, model);
        currentDistance = getDistanceBetweenPoints(p, p2);
        if (currentDistance < minDistance){
            minDistance = currentDistance;
        }
    }
    return minDistance;//return minimum distance found
}

bool comparePointsDistance(point &p1, point &p2){//comparator for 2 points
    return (p1.distanceToLine < p2.distanceToLine);
}

double getMedianError(vector<point> &inputSet){ // return median error of an input set of points using absolute distance from a model as the metric of deviation
    bool isEven;
    double medianValue;
    std::sort(inputSet.begin(), inputSet.end(), comparePointsDistance);///sort by distance from parabola
    size_t setSize = inputSet.size();
    if (setSize%2 == 0){//if set has even number of elements
        medianValue = (inputSet[inputSet.size()/2 - 1].distanceToLine + inputSet[inputSet.size()/2].distanceToLine)/2.0;//median distance
        isEven = true;
    }else{
        medianValue = inputSet[inputSet.size()/2].distanceToLine;//median distance
        isEven = false;
    }
    vector<double> medianErrorVector;//create vector of absolute deviations from median
    for (point &p : inputSet){
        medianErrorVector.push_back(abs(p.distanceToLine - medianValue));
    }
    std::sort(medianErrorVector.begin(), medianErrorVector.end());//sort deviation from median values
    if (isEven){
        return (medianErrorVector[(medianErrorVector.size()/2) - 1] + medianErrorVector[medianErrorVector.size()/2])/2.0;//return median deviation
    }else{
        return medianErrorVector[medianErrorVector.size()/2];//return median deviation
    }
}

tuple<double, double, double> leastSquares(vector<point> &inputSet){ // least squares quadratic regression returns parabolic model from input set of points using absolute distance from model as the deviation metric
    double n = inputSet.size();
    double sumx4 = 0;
    double sumx3 = 0;
    double sumx2 = 0;
    double sumx = 0;
    double sumy = 0;
    double sumxy = 0;
    double sumx2y = 0;
    double temp;
    for (point &p : inputSet){ // generate sum values all at once
        temp = pow(p.x, 2.0); // use temp to store x^2 since this value is reused multiple times in constructions
        sumx += p.x;
        sumx2 += temp;
        sumx3 += (p.x * temp);
        sumx4 += pow(temp, 2.0);
        sumy += p.y;
        sumxy += (p.x * p.y);
        sumx2y += (temp * p.y);
    }
    arma::mat X; // generate 3x3 matrix of sum values = X
    X.resize(3, 3);
    X (0,0) = sumx4;
    X (0,1) = sumx3;
    X (0,2) = sumx2;
    X (1,0) = sumx3;
    X (1,1) = sumx2;
    X (1,2) = sumx;
    X (2,0) = sumx2;
    X (2,1) = sumx;
    X (2,2) = n;
    arma::mat inverseX = arma::inv(X); // take inverse of X
    arma::vec Y; // generate 3 column vector of other sum values = Y
    Y.resize(3);
    Y (0) = sumx2y;
    Y (1) = sumxy;
    Y (2) = sumy;
    arma::vec A = inverseX * Y; // solve A = X' * Y

    return make_tuple(A(0), A(1), A(2));
}

tuple<double, double, double> randomizedBestFit(vector<point> &inputSet, int numTrials){ // combine RANSAC approach and least squares fit to generate best fit model and handle outliers
    vector<point> trialInputSet = inputSet; // will become the n-3 set of data points
    double minMedianError = INFINITY; // minimum median error found
    double currentMedianError;
    vector<point> trialPoints; // trialPoints will become the 3 randomly picked points used to generate a parabola model
    int randNum;
    tuple<double, double, double> currentModel; // current trial model
    tuple<double, double, double> finalModel; // final model used in least squares fit
    for (int i = 0; i < numTrials; i++){ // iterate for a number of trials
        trialInputSet = inputSet; // reset input set of n points to initial input set
        for (int j = 0; j < 3; j++){
            randNum = rand()%(trialInputSet.size());
            trialPoints.push_back(trialInputSet[randNum]); // push 3 random points to trialPoints (3 set of points for model)
            trialInputSet.erase(trialInputSet.begin() + randNum); // remove 3 random points from trialInputSet (n-3 set of points)
        }
        currentModel = getModel(trialPoints); // generate parabola equation from 3 random points
        for (point &p : trialInputSet){ // update distance from point to parabola for all other n-3 points
            p.distanceToLine = getDistanceToModel(p, currentModel);
        }
        currentMedianError = getMedianError(trialInputSet); // calculate median error of n-3 points in relation to model generated by 3 randomly chosen points
        if (currentMedianError < minMedianError){ // if the median error of the current model and the n-3 remaining points is the minimum, set finalModel to current model
            minMedianError = currentMedianError;
            finalModel = currentModel;
        }
        trialPoints.clear(); // reset set of 3 random points
    }
    for (point &p : inputSet){ // for all n points of original input set, update distance to parabola specified by final model from trials
        p.distanceToLine = getDistanceToModel(p, finalModel);
    }
    sort(inputSet.begin(), inputSet.end(), comparePointsDistance); // sort n points by their absolute distance from final model
    inputSet.erase(inputSet.begin() + inputSet.size()/2 - 1, inputSet.end()); // erase 2nd half of points, i.e. erase half of points with higher deviation from final model
    return leastSquares(inputSet); // take least squares quadratic regression of lower half of points and return the parabolic model generated
}