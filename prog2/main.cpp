#include <iostream>
#include <fstream>
#include <sstream>
#include "edge.h"

using namespace std;

int main(int argc, char* argv[]) {
    ifstream inputPoints(argv[1]); //filename is input as first argument to main
    string line;
    getline(inputPoints, line);
    int numPoints = stoi(line); // get first line of input file as number of points
    vector<point> points;
    int indexCounter = 0;
    //read in points
    graph inputGraph;
    for(int i = 0; i < numPoints; i++){
        if(getline(inputPoints, line)){
            point p;
            p.index = indexCounter;
            stringstream currentLine(line);
            string value;
            getline(currentLine, value, ',');
            p.x = stod(value);
            getline(currentLine, value);
            p.y = stod(value);
            p.seen = false;
            points.push_back(p);
            inputGraph.points[indexCounter] = p;
            indexCounter++;
        }else{
            cout<<"Incorrect number of points. Exiting."<<endl;
            return 0;
        }
    }
    //read in edges
    getline(inputPoints, line);
    int numEdges = stoi(line);
    for(int i = 0; i < numEdges; i++){
        if(getline(inputPoints, line)){
            edge e;
            stringstream currentLine(line);
            string value;
            getline(currentLine, value, ',');
            e.p1 = stoi(value);
            getline(currentLine, value);
            e.p2 = stoi(value);
            e.weight = distanceBetweenPoints(points[e.p1], points[e.p2]);
            inputGraph.edges.push_back(e);
            inputGraph.points[e.p1].adj.push_back(e);//add p2 to p1's adjacency list
            inputGraph.points[e.p2].adj.push_back(e);//add p1 to p2's adjacency list
        }else{
            cout<<"Incorrect number of edges. Exiting."<<endl;
            return 0;
        }
    }
    inputGraph.dijkstra(inputGraph.points[0]);
    return 0; // done
}