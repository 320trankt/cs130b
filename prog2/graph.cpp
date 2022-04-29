#include "graph.h"

using namespace std;

void graph::dijkstra(point p, unsigned int numPoints){
    map<point, vector<point>> shortestPaths;//map containing the shortest paths for each point ; paths are represented as vectors of points
    p.seen = true;
    vector<double> pointDistances(numPoints, INFINITY);
    pointDistances[0] = 0.0;
    while(shortestPaths.size() != (numPoints-1)){
        
    }
}
