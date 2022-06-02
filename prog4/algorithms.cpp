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