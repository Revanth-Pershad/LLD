/*
    How to use dates of different formats for LLD
*/


// Only available in c++ 20
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
using namespace std::chrono;

// Try to parse a string with one of several layouts and
// return a std::chrono::sys_seconds (UTC-seconds-since-epoch).
sys_seconds parse_to_sys_seconds(const string& s)
{
    const char* fmts[] = {
        "%Y-%m-%d %H:%M:%S",          // 2025-06-06 03:15:00
        "%d/%m/%Y %I:%M %p",          // 06/06/2025 03:15 AM
        "%Y-%m-%dT%H:%M:%S%Ez",       // 2025-06-06T03:15:00+05:30
    };

    for (auto fmt : fmts) {
        istringstream in{s};
        sys_seconds tp;
        in >> parse(fmt, tp);         // C++20 chrono::parse
        if (!in.fail()) return tp;
    }
    throw runtime_error("Unrecognised date format: " + s);
}

int main() {
    auto t1 = parse_to_sys_seconds("2025-06-06 03:15:00");
    auto t2 = parse_to_sys_seconds("06/06/2025 08:45 AM");
    cout << "Difference (minutes): "
         << duration_cast<minutes>(t2 - t1).count() << '\n';
}
