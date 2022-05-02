#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <limits>
#include <unordered_set>
#include "point.h"

using namespace std;

class graph{
    public:
        map<int, point> points;//map where key value is point index and value is point itself
        vector<edge> edges; //vector of edges present in the graph
        void dijkstra(unsigned int numPoints);
};