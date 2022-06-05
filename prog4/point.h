using namespace std;

class point{
    public:
        point();
        point(double p_x, double p_y);
        double x;
        double y;
        double distanceToLine;
        void setEqual(point p);
        void operator= (const point &other);
        bool operator< (const point &other) const;
};