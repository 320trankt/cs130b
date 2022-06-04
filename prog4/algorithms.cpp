#include "algorithms.h"

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
    a = A(0);
    b = A(1);
    c = A(2);

    return make_tuple(A(0), A(1), A(2));
}