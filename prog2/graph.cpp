#include "graph.h"

using namespace std;

class comparePoints{
    public:
        int operator() (const point& p1, const point& p2){
            return p1.distance > p2.distance;
        }
}

void graph::dijkstra(point p, unsigned int numPoints){
    priority_queue<point, vector<Point>, comparePoints> pointConsideration;
    unordered_set<int> pointsInserted;
    points[0].distance = 0.0;
    pointConsideration.push(points[0]);
    pointsInserted.insert(0);
    for (int i = 1; i < numPoints; i++){
        points[i].distance = std::numeric_limits<double>::infinity();
        pointConsideration.push(points[i]);
        pointsInserted.insert(i);
    }
    map<point, vector<int>> shortestPaths;//map containing the shortest paths for each point ; paths are represented as vectors of indexes of points taken
    point temp;
    vector<point> currentShortestPath;
    while(!pointConsideration.empty()){//while there are still points in the priority queue
        temp.setEqual(pointConsideration.pop());//set temp point equal to the point in priority queue with the min distance and pop it off the queue
        for (edge e : temp.adj){//for every vertex adjacent to the temp point
            if(temp.index == e.p1){//destination point is accessed via e.p2
                if(pointsInserted.find(e.p2) != pointsInserted.end()){//if destination point is in priority queue
                    if(points[e.p2].distance > (points[e.p1].distance + e.weight)){
                        points[e.p2].distance = points[e.p1].distance + e.weight;
                        //at this point, have updated all adjacent points to current node with shortest path value
                        //need to update the distance values in the pointConsideration priority queue somehow so that we can take
                        //the shortest path from the current temp node in the next step of the while loop
                    }
                }
            }else if(temp.index == e.p2){//destination point is accessed via e.p1
                if(pointsInserted.find(e.p1) != pointsInserted.end()){//if destination point is in priority queue
                    if(points[e.p1].distance > (points[e.p2].distance + e.weight)){
                        points[e.p1].distance = points[e.p2].distance + e.weight;
                    }
                }
            }
        }
        //here need to add the current temp node to the shortestPaths vector, along with the path we took to get here
        shortestPaths[temp.index] = //insert path of points to current node here in form of vector of ints
        //here also need to make sure we do pointsInserted.insert(temp.index)
        pointsInserted.insert(temp.index);//this ensures
    }
}
