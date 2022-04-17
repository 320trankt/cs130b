#include <iostream>
#include "hull.h"
#include "point.h"
#include "utilityFuncs.h"

using namespace std;

int main(int argc, char* argv[]) {
    ifstream inputPoints(argv[1]); //filename is input as first argument to main
    string line;
    getline(inputPoints, line, "\n");
    int numPoints = stoi(line); // get first line of input file as number of points
    vector<point> points;
    int indexCounter = 0;
    while(getline(inputPoints, line, "\n")){ // get entire line into "line" variable
        point p;
        p.index = indexCounter;
        istringstream currentLine(line);
        string value;
        getline(currentLine, value, ",");
        p.x = stod(value);
        getline(currentLine, value, "\n");
        p.y = stod(value);
        points.push_back(point);
        indexCounter++;
    }
    //at this point points should be a vector containing all points from input file as pair<double, double>
    hull inputHull;
    for (int i; i < numPoints; i++){
        inputHull.addPoint(points[i]);
    }//add all points to vector of points in hull object
    vector<point> convexHullPoints = inputHull.quickHull();
    //int numConvexHullPoints = convexHullPoints.size(); //this may take too long, could build into quickHull to return size if this takes too long
    /* cout<<numConvexHullPoints<<endl; // print out number of points in convex hull
    for (tuple<int,double,double> i : convexHullPoints){ // range-based for loop prints out each point in convex hull
        cout<< get<0>(i) << ", " << get<1>(i) << ", " << get<2>(i) << endl;
    } */
    inputHull.printHull();
    return 0; // done
}