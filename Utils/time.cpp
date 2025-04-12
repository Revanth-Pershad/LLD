#include <cstdlib>
#include <ctime>
#include <iostream>

class Random{
    int low, high;
    public:
        Random(int l, int h){
            // Set a time seed
            srand(time(0));

            low = l;
            high = h;
        }

        int getRandom(){
            return (low + rand()%high);
        }
};