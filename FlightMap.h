/*
Celal Salih Türkmen
22102498
Section 3
*/
#ifndef __FLIGHT_MAP_H
#define __FLIGHT_MAP_H
#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include "City.h"
#include "Path.h"
using namespace std;
class FlightMap {
    public:
        vector<list<City> > graph;
        vector<list<bool>> visited;
        vector<Path> flights;
        int getListIndex(const City& deptCity) const;
        bool deadend(const City& city, const string dest) const;
        bool contains(stack<City> st, const City &c) const;
    public: 
        FlightMap(const string cityFile, const string flightFile);
        ~FlightMap();
        void displayAllCities() const;
        void displayAdjacentCities(const string cityName) const;
        void displayFlightMap() const;
        void findFlights(const string deptCity, const string destCity);
        string getPath(const City& c1, const City& c2, int& c) const;
};
#endif