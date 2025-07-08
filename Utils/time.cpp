#include <iostream>
#include <chrono>

using namespace std;

int main() {
    // Write C++ code here
    chrono::system_clock::time_point a = chrono::system_clock::now();
    int ax; std::cin >> ax;
    chrono::system_clock::time_point b = chrono::system_clock::now();
    auto duration = b - a;
    
    std::cout << chrono::duration_cast<chrono::seconds>(duration).count();

    return 0;
}