#include <map>
#include "point.h"
#include "edge.h"
#include "utilityFuncs.h"

using namespace std;

class graph{
    public:
        map<int, point> points;//map where key value is point index and value is point itself
        vector<edge> edges; //vector of edges present in the graph
        void dijkstra(point p, unsigned int numPoints);
};