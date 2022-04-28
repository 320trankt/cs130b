#include "point.h"
#include "utilityFuncs.h"

using namespace std;

class edge{
    public:
        edge();
        edge(int a, int b);
        int a;
        int b;
        double weight;
        void setWeight();
};