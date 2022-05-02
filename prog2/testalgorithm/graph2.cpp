#include "graph2.h"

using namespace std;

class compareEdges{
    public:
        int operator() (const pair<double, edge>& e1, const pair<double, edge>& e2){
            return e1.first > e2.first;
        }
};

void graph::dijkstra(int src, unsigned int numPoints){
    priority_queue<pair<double, edge>, vector<pair<double, edge>>, compareEdges> pathConsideration;
    unordered_set<int> finalizedPoints;
    //vector<int> finalizedPoints;
    for (edge e : points[src].adj){
        pathConsideration.push(make_pair(e.weight, e));
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
        points[destinationPoint.index].distance += currentPoint.distance;
        destinationPoint.distance += currentPoint.distance;
        points[destinationPoint.index].distance += currentEdge.weight;
        destinationPoint.distance += currentEdge.weight;
        for (edge e : destinationPoint.adj){
            if (((e.p1 == currentEdge.p1) && (e.p2 == currentEdge.p2)) || ((e.p1 == currentEdge.p2) && (e.p2 == currentEdge.p1))){
                continue;
            }else{
                pathConsideration.push(make_pair(e.weight + destinationPoint.distance, e));
            }
        }
        points[destinationPoint.index].shortestPath = currentPoint.shortestPath;
        destinationPoint.shortestPath = currentPoint.shortestPath;
        points[destinationPoint.index].shortestPath.push_back(destinationPoint.index);
        destinationPoint.shortestPath.push_back(destinationPoint.index);
        finalizedPoints.insert(destinationPoint.index);
        /* for (auto i = finalizedPoints.begin(); i != finalizedPoints.end(); ++i){
            cout<< *i<<" ";
        }
        cout<<"size of finalizedPoints: "<<finalizedPoints.size()<<endl; */
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
