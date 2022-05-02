#include <fstream>
#include <sstream>
#include <cmath>
#include "graph2.h"

using namespace std;

double distanceBetweenPoints(point p1, point p2){
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) * 1.0);
}

int main(int argc, char* argv[]) {
    ifstream inputPoints(argv[1]); //filename is input as first argument to main
    string line;
    getline(inputPoints, line);
    int numPoints = stoi(line); // get first line of input file as number of points
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
    if (numEdges == 0){
        edge e;
        for (int i = 0; i < numPoints; i++){
            for (int j = i+1; j < numPoints; j++){
                e.p1 = i;
                e.p2 = j;
                e.weight = distanceBetweenPoints(inputGraph.points[i], inputGraph.points[j]);
                inputGraph.edges.push_back(e);
                inputGraph.points[i].adj.push_back(e);
                inputGraph.points[j].adj.push_back(e);
            }
        }
    }else{
        for(int i = 0; i < numEdges; i++){
            if(getline(inputPoints, line)){
                edge e;
                stringstream currentLine(line);
                string value;
                getline(currentLine, value, ' ');
                e.p1 = stoi(value);
                getline(currentLine, value);
                e.p2 = stoi(value);
                e.weight = distanceBetweenPoints(inputGraph.points[e.p1], inputGraph.points[e.p2]);
                inputGraph.edges.push_back(e);
                inputGraph.points[e.p1].adj.push_back(e);//add p2 to p1's adjacency list
                inputGraph.points[e.p2].adj.push_back(e);//add p1 to p2's adjacency list
            }else{
                cout<<"Incorrect number of edges. Exiting."<<endl;
                return 0;
            }
        }
    }
    inputGraph.dijkstra(0, numPoints);
    return 0; // done
}