#include "algorithms.h"

double getDistanceBetweenPoints(point p1, point p2){
    return sqrt(pow(p2.x - p1.x, 2.0) + pow(p2.y - p1.y,2.0));
}

tuple<double, double, double> getModel(vector<point> inputThree){
    point p1 = inputThree[0];
    point p2 = inputThree[1];
    point p3 = inputThree[2];
    double x1 = p1.x;
    double y1 = p1.y;
    double x2 = p2.x;
    double y2 = p2.y;
    double x3 = p3.x;
    double y3 = p3.y;
    double denominator = (x1-x2) * (x1-x3) * (x2-x3);
    double a = (x3 * (y2-y1) + x2 * (y1-y3) + x1 * (y3-y2)) / denominator;
    double b = (x3*x3 * (y1-y2) + x2*x2 * (y3-y1) + x1*x1 * (y2-y3)) / denominator;
    //double c = (x2 * x3 * (x2-x3) * y1+x3 * x1 * (x3-x1) * y2+x1 * x2 * (x1-x2) * y3) / denominator;
    double c = (x2 * x2 * (x3 * y1 - x1 * y3) + x2 * (x1 * x1 * y3 - x3 * x3 * y1) + x1 * x3 * (x3 - x1) * y2)/denominator;
    return make_tuple(a, b, c);
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
    //approach utilizes the distance formula between a parabola with equation y = ax^2 + bc + c, and point (x,y)
    //the distance between point (x,y) and y = ax^2+bc+c is d^2 = 
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

bool comparePointsDistance(point &p1, point &p2){//comparator for 2 points
    return (p1.distanceToLine < p2.distanceToLine);
}

double getMedianError(vector<point> &inputSet){
    bool isEven;
    double medianValue;
    std::sort(inputSet.begin(), inputSet.end(), comparePointsDistance);///sort by distance from best fit line
    size_t setSize = inputSet.size();
    if (setSize%2 == 0){//if set has even number of elements
        medianValue = (inputSet[inputSet.size()/2 - 1].distanceToLine + inputSet[inputSet.size()/2].distanceToLine)/2.0;//median distance
        isEven = true;
    }else{
        medianValue = inputSet[inputSet.size()/2].distanceToLine;//median distance
        isEven = false;
    }
    vector<double> medianErrorVector;//create vector of distance to line values - median distance
    for (point &p : inputSet){
        //cout<<p.distanceToLine-medianValue<<endl;
        medianErrorVector.push_back(abs(p.distanceToLine - medianValue));
    }
    std::sort(medianErrorVector.begin(), medianErrorVector.end());//sort median deviation values
    if (isEven){
        //cout<<(medianErrorVector[(medianErrorVector.size()/2) - 1] + medianErrorVector[medianErrorVector.size()/2])/2.0<<endl;
        return (medianErrorVector[(medianErrorVector.size()/2) - 1] + medianErrorVector[medianErrorVector.size()/2])/2.0;//return median deviation
    }else{
        //cout<<medianErrorVector[medianErrorVector.size()/2]<<endl;
        return medianErrorVector[medianErrorVector.size()/2];//return median deviation
    }
}

tuple<double, double, double> leastSquares(vector<point> &inputSet){
    double n = inputSet.size();
    double sumx4 = 0;
    double sumx3 = 0;
    double sumx2 = 0;
    double sumx = 0;
    double sumy = 0;
    double sumxy = 0;
    double sumx2y = 0;
    double temp;
    for (point &p : inputSet){
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

tuple<double, double, double> ransac(vector<point> &inputSet, int numTrials){
    vector<point> trialInputSet = inputSet;
    double minMedianError = INFINITY;
    double currentMedianError;
    vector<point> trialPoints;
    int randNum;
    tuple<double, double, double> currentModel;
    tuple<double, double, double> finalModel;
    for (int i = 0; i < numTrials; i++){
        trialInputSet = inputSet;
        for (int j = 0; j < 3; j++){
            randNum = rand()%(trialInputSet.size());
            trialPoints.push_back(trialInputSet[randNum]);
            trialInputSet.erase(trialInputSet.begin() + randNum);
        }
        //currentModel = leastSquares(trialPoints);
        currentModel = getModel(trialPoints);
        for (point &p : trialInputSet){
            p.distanceToLine = getDistanceToModel(p, currentModel);
        }
        currentMedianError = getMedianError(trialInputSet);
        //cout<<"trial "<<i<<", currentMedianError: "<<currentMedianError<<", minMedianError: "<<minMedianError<<endl;
        if (currentMedianError < minMedianError){
            minMedianError = currentMedianError;
            finalModel = currentModel;
        }
        trialPoints.clear();
    }
    for (point &p : inputSet){
        p.distanceToLine = getDistanceToModel(p, finalModel);
    }
    sort(inputSet.begin(), inputSet.end(), comparePointsDistance);
    inputSet.erase(inputSet.begin() + inputSet.size()/2 - 1, inputSet.end());
    return leastSquares(inputSet);
}