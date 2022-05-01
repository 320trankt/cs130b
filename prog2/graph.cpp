#include "graph.h"

using namespace std;

class comparePoints{
    public:
        int operator() (const point& p1, const point& p2){
            return p1.distance > p2.distance;
        }
};

void graph::dijkstra(unsigned int numPoints){
    set<point, comparePoints> pointConsideration;
    //priority_queue<point, vector<point>, comparePoints> pointConsideration;
    unordered_set<int> pointsInserted;
    points[0].distance = 0.0;
    pointConsideration.insert(points[0]);
    pointsInserted.insert(0);
    for (int i = 1; i < numPoints; i++){
        points[i].distance = std::numeric_limits<double>::infinity();
        pointConsideration.insert(points[i]);
        pointsInserted.insert(i);
    }
    point temp;
    while(!pointConsideration.empty()){//while there are still points in the priority queue
        temp.setEqual(*(pointConsideration.begin()));
        for (edge e : temp.adj){//for every vertex adjacent to the temp point
            if(temp.index == e.p1){//destination point is accessed via e.p2
                if(points[e.p2].distance > (points[e.p1].distance + e.weight)){
                    if(pointsInserted.find(e.p2) != pointsInserted.end()){//if destination point is in priority queue
                        pointConsideration.erase(points[e.p2]);
                        points[e.p2].distance = points[e.p1].distance + e.weight;
                        points[e.p2].shortestPath.push_back(temp.index);//add current node to destination node's shortest path
                        pointConsideration.insert(points[e.p2]);
                    }else{
                        points[e.p2].distance = points[e.p1].distance + e.weight;
                        points[e.p2].shortestPath.push_back(temp.index);//add current node to destination node's shortest path
                        pointConsideration.insert(points[e.p2]);
                    }
                }
            }else if(temp.index == e.p2){//destination point is accessed via e.p1
                if(points[e.p1].distance > (points[e.p2].distance + e.weight)){
                    if(pointsInserted.find(e.p1) != pointsInserted.end()){//if destination point is in priority queue
                        pointConsideration.erase(points[e.p1]);
                        points[e.p1].distance = points[e.p2].distance + e.weight;
                        points[e.p1].shortestPath.push_back(temp.index);//add current node to destination node's shortest path
                        pointConsideration.insert(points[e.p1]);
                    }else{
                        points[e.p1].distance = points[e.p2].distance + e.weight;
                        points[e.p1].shortestPath.push_back(temp.index);//add current node to destination node's shortest path
                        pointConsideration.insert(points[e.p1]);
                    }
                }
            }
        }
        pointConsideration.erase(pointConsideration.begin());//set temp point equal to the point in priority queue with the min distance and pop it off the queue
        pointsInserted.erase(temp.index);
        //here also need to make sure we do pointsInserted.insert(temp.index)
    }
    for (int i = 1; i < numPoints; i++){
        for(int j : points[i].shortestPath){
            cout<<j<<", ";
        }
        cout<<endl;
    }
}
