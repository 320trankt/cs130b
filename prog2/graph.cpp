#include "graph.h"

void graph::dijkstra(point p){
    map<point, vector<point>> shortestPaths;//map containing the shortest paths for each point ; paths are represented as vectors of points
    p.seen = true;
    for (point i : inputGraph.points){
        if (i.index == 0){
            continue;
        }
        
    }
}
