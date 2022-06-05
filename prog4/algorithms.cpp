#include "algorithms.h"

double getDistanceBetweenPoints(point p1, point p2){
    return sqrt(pow(p2.x - p1.x, 2.0) + pow(p2.y - p1.y,2.0));
}

double calcYFromModel(double x, tuple<double, double, double> model){
    double a = get<0>(model);
    double b = get<1>(model);
    double c = get<2>(model);
    return ((a * pow(x, 2.0)) + (b * x) + c);
}

double getDistanceToModel(point p, tuple<double,double,double> model){
    double a = get<0>(model);
    double b = get<1>(model);
    double c = get<2>(model);
    double x = p.x;
    double y = p.y;
    double coefficientx3 = 2.0 * pow(a,2.0);
    double coefficientx2 = 4.0 * a * b;
    double coefficientx = 2.0 + (4*a*c) - (4*a*y) + (2 * pow(b, 2.0));
    double coefficientconst = (2*b*c) - (2*x) - (2*b*y);
    arma::vec P;
    P.resize(4);
    P (0) = coefficientx3;
    P (1) = coefficientx2;
    P (2) = coefficientx;
    P (3) = coefficientconst;
    arma::cx_vec R = roots(P);
    double minDistance = INFINITY;
    double currentDistance;
    double currentX;
    point p2;
    for (int i = 0; i < R.n_elem; i++){
        currentX = std::arg(R(i));
        p2.x = currentX;
        p2.y = calcYFromModel(p2.x, model);
        currentDistance = getDistanceBetweenPoints(p, p2);
        if (currentDistance < minDistance){
            minDistance = currentDistance;
        }
    }
    return minDistance;
}

bool comparePointsDistance(point p1, point p2){//comparator for 2 points
    return (p1.distanceToLine < p2.distanceToLine);
}

double getMedianError(vector<point> inputSet){
    //IMPORTANT: NEED TO REDEFINE POINT COMPARISON OPERATOR SO THAT SORT WILL WORK PROPERLY
    //FIND OUT HOW TO DEFINE THE MEDIAN VALUE OF A POINT IN 2D SPACE
    bool isEven;
    double medianValue;
    std::sort(inputSet.begin(), inputSet.end(), comparePointsDistance);///sort by distance from best fit line
    size_t setSize = inputSet.size();
    if (setSize%2 == 0){//if set has even number of elements
        medianValue = (inputSet[setSize/2 - 1].distanceToLine + inputSet[setSize/2].distanceToLine)/2.0;//median distance
        isEven = true;
    }else{
        medianValue = inputSet[setSize/2].distanceToLine;//median distance
        isEven = false;
    }
    vector<double> medianErrorVector;//create vector of distance to line values - median distance
    for (point p : inputSet){
        medianErrorVector.push_back(p.distanceToLine - medianValue);
    }
    std::sort(medianErrorVector.begin(), medianErrorVector.end());//sort median deviation values
    if (isEven){
        return (medianErrorVector[setSize/2 - 1] + medianErrorVector[setSize/2])/2.0;//return median deviation
    }else{
        return medianErrorVector[setSize/2];//return median deviation
    }
}

tuple<double, double, double> getModel(vector<point> inputSet){
    double n = inputSet.size();
    double sumx4 = 0;
    double sumx3 = 0;
    double sumx2 = 0;
    double sumx = 0;
    double sumy = 0;
    double sumxy = 0;
    double sumx2y = 0;
    double temp;
    for (point p : inputSet){
        temp = pow(p.x, 2.0);
        sumx += p.x;
        sumx2 += temp;
        sumx3 += (p.x * temp);
        sumx4 += pow(temp, 2.0);
        sumy += p.y;
        sumxy += (p.x * p.y);
        sumx2y += (temp * p.y);
    }
    arma::mat X;
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
    arma::mat inverseX = arma::inv(X);
    arma::vec Y;
    Y.resize(3);
    Y (0) = sumx2y;
    Y (1) = sumxy;
    Y (2) = sumy;
    arma::vec A = inverseX * Y;

    return make_tuple(A(0), A(1), A(2));
}

tuple<double, double, double> ransac(vector<point> inputSet, int numTrials){
    vector<point> lastInputSet = inputSet;
    vector<point> potentialInputSet;
    double minMedianError = INFINITY;
    double currentMedianError;
    vector<point> trialPoints;
    int randNum;
    tuple<double, double, double> currentModel;
    tuple<double, double, double> finalModel;
    for (int i = 0; i < numTrials; i++){
        lastInputSet = potentialInputSet;
        for (int j = 0; j < 3; j++){
            randNum = rand()%(potentialInputSet.size());
            trialPoints.push_back(potentialInputSet[randNum]);
            potentialInputSet.erase(potentialInputSet.begin() + randNum);
        }
        currentModel = getModel(trialPoints);
        for (point p : potentialInputSet){
            p.distanceToLine = getDistanceToModel(p, currentModel);
        }
        currentMedianError = getMedianError(potentialInputSet);
        if (currentMedianError < minMedianError){
            minMedianError = currentMedianError;
            finalModel = currentModel;
        }else{
            potentialInputSet = lastInputSet;
        }
        trialPoints.clear();
    }
    for (point p : inputSet){
        p.distanceToLine = getDistanceToModel(p, finalModel);
    }
    sort(inputSet.begin(), inputSet.end());
    inputSet.erase(inputSet.begin() + inputSet.size()/2, inputSet.end());
    return getModel(inputSet);
}