using namespace std;

class point{
    public:
        point();
        point(int p_index, double p_x, double p_y);
        int index;
        double x;
        double y;
        vector<edge> adj;
        double distance;
        void setEqual(point p);
};