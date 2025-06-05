#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

class Random{
    int low, high;
    public:
    
    Random(int l, int h){
        low = l;
        high = h;

        srand(time(0)); // Sets the seed to current time
    }

    int getRandom(){
        return (low + rand()%high);
    }
};

int main(){
    Random r = Random(1, 5);
    for(int i = 0; i < 100; i++)
        cout << r.getRandom() << " ";
}