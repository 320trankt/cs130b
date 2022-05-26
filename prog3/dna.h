#include<list>

using namespace std;

class dna{
    public:
        dna();
        list<char> bases;
        list<char>::iterator currentBase;
};