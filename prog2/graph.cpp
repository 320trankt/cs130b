#include "graph.h"

using namespace std;

class compareEdges{
    public:
        int operator() (const pair<double, edge>& e1, const pair<double, edge>& e2){
            return e1.first > e2.first;
        }
};

void graph::dijkstra(int src, unsigned int numPoints){
    clock_t t;
    t = clock();
    priority_queue<pair<double, edge>, vector<pair<double, edge>>, compareEdges> pathConsideration;//each edge's double is the distance from the source
    unordered_set<int> finalizedPoints;
    points[src].distance = 0.0;
    for (edge e : points[src].adj){//for src point, push all edges into consideration
        pathConsideration.push(make_pair(e.weight, e));//for each adjacent point, it's distance is defined as weight of edge between source and destination
        if(src == e.p1){//update destination point's distance from source
            points[e.p2].distance += e.weight;
        }else{
            points[e.p1].distance += e.weight;
        }
    }
    finalizedPoints.insert(src);//finalize source point
    points[src].shortestPath.push_back(src);//add source point to it's own shortest path
    point currentPoint;
    point destinationPoint;
    edge currentEdge;
    while(finalizedPoints.size() != numPoints){//while not all points have been finalized
        currentEdge = pathConsideration.top().second;//consider edge which is smallest distance from source
        pathConsideration.pop();//pop cheapest edge off priority queue
        //here specify currentPoint as point which is already finalized, and destinationPoint as one which must be finalized
        if(finalizedPoints.count(currentEdge.p1) > 0){
            currentPoint = points[currentEdge.p1];
            destinationPoint = points[currentEdge.p2];
        }else{
            currentPoint = points[currentEdge.p2];
            destinationPoint = points[currentEdge.p1];
        }
        if ((finalizedPoints.count(currentPoint.index) > 0) && (finalizedPoints.count(destinationPoint.index) > 0)){//if both points are already finalized, don't process this edge
            continue;
        }
        finalizedPoints.insert(destinationPoint.index);//finalize destinationPoint
        //update destination point's distance from source and shortest path vector here
        points[destinationPoint.index].distance += (currentPoint.distance + currentEdge.weight);
        destinationPoint.distance += (currentPoint.distance + currentEdge.weight);
        points[destinationPoint.index].shortestPath = currentPoint.shortestPath;
        destinationPoint.shortestPath = currentPoint.shortestPath;
        points[destinationPoint.index].shortestPath.push_back(destinationPoint.index);//destinationPoint's shortest path is currentpoint's shortest path + destination point
        destinationPoint.shortestPath.push_back(destinationPoint.index);
        //here push all destination point's edges into consideration
        for (edge e : destinationPoint.adj){
            if (((e.p1 == currentEdge.p1) && (e.p2 == currentEdge.p2)) || ((e.p1 == currentEdge.p2) && (e.p2 == currentEdge.p1))){//makes sure that edge just taken isnt pushed into consideration again
                continue;
            }else{
                if(destinationPoint.index == e.p1){//new destination point is e.p2
                    if(finalizedPoints.count(e.p2) > 0){//if the new destination point is already finalized, don't push edge into consideration
                        continue;
                    }else{
                        pathConsideration.push(make_pair((e.weight + destinationPoint.distance), e));//push edge to consideration. new edge's distance from source is defined as current distance + edge's weight
                        //points[e.p2].distance += (e.weight + destinationPoint.distance);
                    }
                }else{//new destination point is e.p1
                    if(finalizedPoints.count(e.p1) > 0){
                        continue;
                    }else{
                        pathConsideration.push(make_pair((e.weight + destinationPoint.distance), e));
                        //points[e.p1].distance += (e.weight + destinationPoint.distance);
                    }
                }
            }
        }
    }
    t = clock() - t;
    cout<<"Runtime for "<<points.size()<<" points: "<<t<<" clock cycles."<<endl;
    /* for (int i = 1; i < numPoints; i++){//print all finalized points' shortest paths
        int pathSize = points[i].shortestPath.size();
        cout<<points[i].shortestPath[0];
        for (int j = 1; j < pathSize; j++){
            cout<<", "<<points[i].shortestPath[j];
        }
        cout<<endl;
    } */
}
