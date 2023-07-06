#include "FlightMap.h"
#include <iostream>
using namespace std;
int main() {
    FlightMap fm("cityFile.txt", "flightFile.txt");
    fm.findFlights("S", "X");
    cout << endl;
    return 0;
}
