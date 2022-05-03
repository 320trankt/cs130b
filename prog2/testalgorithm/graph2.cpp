#include "graph2.h"

using namespace std;

class compareEdges{
    public:
        int operator() (const pair<double, edge>& e1, const pair<double, edge>& e2){
            return e1.first > e2.first;
        }
};

void graph::dijkstra(int src, unsigned int numPoints){
    priority_queue<pair<double, edge>, vector<pair<double, edge>>, compareEdges> pathConsideration;//each edge's double is the distance from the source
    unordered_set<int> finalizedPoints;
    for (edge e : points[src].adj){
        pathConsideration.push(make_pair(e.weight, e));
        if(src == e.p1){
            points[e.p2].distance += e.weight;
        }else{
            points[e.p1].distance += e.weight;
        }
    }
    finalizedPoints.insert(src);
    points[src].shortestPath.push_back(src);
    point currentPoint;
    point destinationPoint;
    edge currentEdge;
    while(finalizedPoints.size() != numPoints){
        currentEdge = pathConsideration.top().second;
        pathConsideration.pop();
        if(finalizedPoints.count(currentEdge.p1) > 0){
            currentPoint = points[currentEdge.p1];
            destinationPoint = points[currentEdge.p2];
        }else{
            currentPoint = points[currentEdge.p2];
            destinationPoint = points[currentEdge.p1];
        }
        if ((finalizedPoints.count(currentPoint.index) > 0) && (finalizedPoints.count(destinationPoint.index) > 0)){
            continue;
        }
        finalizedPoints.insert(destinationPoint.index);
        //update destination point's distance from source and shortest path vector here
        points[destinationPoint.index].distance += currentPoint.distance;//
        destinationPoint.distance += currentPoint.distance;
        points[destinationPoint.index].distance += currentEdge.weight;
        destinationPoint.distance += currentEdge.weight;
        points[destinationPoint.index].shortestPath = currentPoint.shortestPath;
        destinationPoint.shortestPath = currentPoint.shortestPath;
        points[destinationPoint.index].shortestPath.push_back(destinationPoint.index);
        destinationPoint.shortestPath.push_back(destinationPoint.index);
        //here push all destination point's edges into consideration
        for (edge e : destinationPoint.adj){
            if (((e.p1 == currentEdge.p1) && (e.p2 == currentEdge.p2)) || ((e.p1 == currentEdge.p2) && (e.p2 == currentEdge.p1))){//makes sure that edge just taken isnt pushed into consideration again
                continue;
            }else{
                if(destinationPoint.index == e.p1){//new destination point is e.p2
                    if(finalizedPoints.count(e.p2) > 0){//if the new destination point already has a shorter path
                        continue;//don't push edge with new point to consideration
                    }else{
                        pathConsideration.push(make_pair(e.weight + destinationPoint.distance, e));//push edge to consideration. new edge's distance from source is defined as current distance + edge's weight
                    }
                }else{//new destination point is e.p1
                    if(finalizedPoints.count(e.p1) > 0){
                        continue;
                    }else{
                        pathConsideration.push(make_pair(e.weight + destinationPoint.distance, e));
                    }
                }
            }
        }
    }
    for (int i = 1; i < numPoints; i++){
        int pathSize = points[i].shortestPath.size();
        cout<<points[i].shortestPath[0];
        for (int j = 1; j < pathSize; j++){
            cout<<", "<<points[i].shortestPath[j];
        }
        cout<<endl;
    }
}
