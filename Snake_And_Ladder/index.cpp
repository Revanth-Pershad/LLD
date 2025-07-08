#include <bits/stdc++.h>
#include <random>

using namespace std;

class RandomGenerator{
    public:
        RandomGenerator(){
            srand(time(0));
        }

        int getRandom(int low, int high){
            return (low + rand()%high);
        }
};

int main(){

}