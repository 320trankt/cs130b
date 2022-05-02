#include "graph.h"

using namespace std;

class comparePoints{
    public:
        int operator() (const point& p1, const point& p2){
            return p1.distance > p2.distance;
        }
};

void graph::dijkstra(unsigned int numPoints){
    //set<point, comparePoints> pointConsideration;
    set<pair<double, int>> pointConsideration;
    //priority_queue<point, vector<point>, comparePoints> pointConsideration;
    unordered_set<int> pointsInserted;
    points[0].distance = 0.0;
    //pointConsideration.insert(points[0]);
    pointConsideration.insert(make_pair(points[0].distance, points[0].index));
    pointsInserted.insert(0);
    for (int i = 1; i < numPoints; i++){
        points[i].distance = std::numeric_limits<double>::infinity();
        //pointConsideration.insert(points[i]);
        pointConsideration.insert(make_pair(points[i].distance, points[i].index));
        pointsInserted.insert(i);
    }
    point temp;
    while(!pointConsideration.empty()){//while there are still points in the priority queue
        temp.setEqual(points[(*(pointConsideration.begin())).second]);
        for (edge e : temp.adj){//for every vertex adjacent to the temp point
            if(temp.index == e.p1){//destination point is accessed via e.p2
                if(points[e.p2].distance > (points[e.p1].distance + e.weight)){
                    if(pointsInserted.count(e.p2) > 0){//if destination point is in priority queue
                        //pointConsideration.erase(pointConsideration.find(points[e.p2]));
                        pointConsideration.erase(pointConsideration.find(make_pair(points[e.p2].distance, points[e.p2].index)));
                        points[e.p2].distance = points[e.p1].distance + e.weight;
                        points[e.p2].shortestPath.push_back(temp.index);//add current node to destination node's shortest path
                        //pointConsideration.insert(points[e.p2]);
                        pointConsideration.insert(make_pair(points[e.p2].distance, points[e.p2].index));
                    }else{
                        points[e.p2].distance = points[e.p1].distance + e.weight;
                        points[e.p2].shortestPath.push_back(temp.index);//add current node to destination node's shortest path
                        //pointConsideration.insert(points[e.p2]);
                        pointConsideration.insert(make_pair(points[e.p2].distance, points[e.p2].index));
                    }
                }
            }else if(temp.index == e.p2){//destination point is accessed via e.p1
                if(points[e.p1].distance > (points[e.p2].distance + e.weight)){
                    if(pointsInserted.count(e.p1) > 0){//if destination point is in priority queue
                        //pointConsideration.erase(pointConsideration.find(points[e.p1]));
                        pointConsideration.erase(pointConsideration.find(make_pair(points[e.p1].distance, points[e.p1].index)));
                        points[e.p1].distance = points[e.p2].distance + e.weight;
                        points[e.p1].shortestPath.push_back(temp.index);//add current node to destination node's shortest path
                        //pointConsideration.insert(points[e.p1]);
                        pointConsideration.insert(make_pair(points[e.p1].distance, points[e.p1].index));
                    }else{
                        points[e.p1].distance = points[e.p2].distance + e.weight;
                        points[e.p1].shortestPath.push_back(temp.index);//add current node to destination node's shortest path
                        //pointConsideration.insert(points[e.p1]);
                        pointConsideration.insert(make_pair(points[e.p1].distance, points[e.p1].index));
                    }
                }
            }
        }
        pointsInserted.erase((*(pointConsideration.begin())).second);
        pointConsideration.erase(pointConsideration.begin());//set temp point equal to the point in priority queue with the min distance and pop it off the queue
        //here also need to make sure we do pointsInserted.insert(temp.index)
    }
    for (int i = 1; i < numPoints; i++){
        for(int j : points[i].shortestPath){
            cout<<j<<", ";
        }
        cout<<endl;
    }
}
