/*
Celal Salih Türkmen
22102498
Section 3
*/
#include "City.h"
#include "FlightMap.h"
#include "Path.h"
#include "Query.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <iterator>
#include <stack>
#include <algorithm>
#include <vector>
using namespace std;
FlightMap::FlightMap(const string cityFile, const string flightFile) {
    ifstream filecity, fileflight;
    filecity.open(cityFile, ios::in);
    fileflight.open(flightFile, ios::in);
    if (!filecity.is_open())
        cout << "Input file " + cityFile + " does not exist" << endl;
    if (!fileflight.is_open())
        cout << "Input file " + flightFile + " does not exist" << endl;
    
    if (filecity.is_open() && fileflight.is_open()) {
        string line;
        while (getline(filecity, line)) {
            list<City> cities;
            City city(line);
            cities.push_front(city);
            graph.insert(lower_bound(graph.begin(), graph.end(), cities), cities);
            list<bool> a;
            a.push_back(0);
            visited.push_back(a);
        }
        while(getline(fileflight, line)) {
            vector<string> tokens;
            string token;
            istringstream token_stream(line);
            while (getline(token_stream, token, ';')) {
                tokens.push_back(token);
            }
            City depart(tokens[0]);
            City dest(tokens[1]);
            Path p(depart, dest, stoi(tokens[2]), stoi(tokens[3]));
            flights.insert(lower_bound(flights.begin(), flights.end(), p), p);
            for (unsigned int i = 0; i < graph.size(); i++) {
                if (graph[i].front() == depart) {
                    graph[i].insert(lower_bound(++graph[i].begin(), graph[i].end(), dest), dest);
                    visited[i].push_back(0);
                }
            }
        }
        filecity.close();
        fileflight.close();
        cout << graph.size() << " cities and " << flights.size() << " flights have been loaded" << endl;
    }
}
FlightMap::~FlightMap() {}

void FlightMap::displayAllCities() const {
    cout << "The list of the cities that HPAir serves is given below:" << endl;
    for (unsigned int i = 0; i < graph.size(); i++) {
        cout << *(graph[i].cbegin()) << ", ";
    }
    cout << endl;
}
void FlightMap::displayAdjacentCities(const string cityName) const {
    cout << "The cities adjacent to " << cityName << " are:" << endl << cityName << " -> ";
    vector<City> disp;
    for (unsigned int i = 0; i < flights.size(); i++) {
        if (flights[i].getDepartureCity().getName() == cityName) {
            const City& c = flights[i].getDestinationCity();
            disp.insert(lower_bound(disp.begin(), disp.end(), c), c);
        }
    }
    for (const City& c : disp)
        cout << c << ", ";
    cout << endl;
}
void FlightMap::displayFlightMap() const {
    cout << "The whole flight map is given below:" << endl;
    for (unsigned int i = 0; i < graph.size(); i++) {
        const list<City>& ls = graph[i];
        list<City>::const_iterator it = ls.cbegin();
        cout << *it << " -> ";
        it++;
        for (; it != ls.cend(); it++) {
            cout << *it << ", ";
        } 
        cout << endl; 
    }
}
void FlightMap::findFlights(const string deptCity, const string destCity) {
    for (unsigned int i = 0; i < visited.size(); i++) {
        for (list<bool>::iterator it = visited[i].begin(); it != visited[i].end(); it++) {
            *it = 0;
        }
    }
    vector<bool> hasDest(graph.size(), 0);
    cout << "Request is to fly from " << deptCity << " to " << destCity << ":" << endl;
    vector<vector<string>> solutions;
    stack<City> st;
    int index = getListIndex(deptCity);
    bool found = false;
    list<City>::iterator it = graph[index].begin();
    list<bool>::iterator itv = visited[index].begin();
    st.push(*it);
    *itv = 1;
    while (!st.empty()) {
        itv = visited[index].begin();
        *itv = 1;
        it = graph[index].begin();
        if (deadend(*it, destCity)) {
            if (hasDest[index]) {
                while (itv != visited[index].end()) {
                    if (it->getName() == destCity) {
                        *itv = 0;
                        break;
                    }
                    itv++;
                    it++;
                }
            }
            st.pop();
            if (!st.empty()) {
                index = getListIndex(st.top());
            }
        }
        else {
            while (it != graph[index].end() && *itv) {
                it++;
                itv++;
            }
            if (it != graph[index].end()) {
                if (it->getName() == destCity) {
                    found = true;
                    hasDest[index] = 1;
                    st.push(*it);
                    *itv = 1;
                    vector<string> sl;
                    stack<City> temp(st);
                    while (!temp.empty()) {
                        sl.push_back(temp.top().getName());
                        temp.pop();
                    }
                    solutions.push_back(sl);
                    st.pop();
                    if (!st.empty())
                        index = getListIndex(st.top());
                }
                else {
                    if (!contains(st, *it)) {
                        index = getListIndex(*it);
                        st.push(*it);
                        *itv = 1;
                    }
                    else {
                        *itv = 1;
                        index = getListIndex(*graph[index].begin());
                    }
                }
            }
        }
    }
    if (!found) {
        cout << "Sorry. HPAir does not fly from " << deptCity <<  " to " << destCity << "." << endl;
        return;
    }
    list<Query> q;
    for (unsigned int i = 0; i < solutions.size(); i++) {
        int tot = 0;
        string s;
        for (unsigned int j = solutions[i].size()-1; j > 0; j--) {
            s += getPath(City(solutions[i][j]), City(solutions[i][j - 1]),tot) + "\n";
        }
        s += "Total Cost: " + to_string(tot) + " TL";
        q.push_back(Query(s,tot));
    }
    q.sort();
    for (list<Query>::const_iterator i = q.cbegin(); i != q.cend(); i++) {
        cout << i->text << endl;
    }
}
int FlightMap::getListIndex(const City& deptCity) const {
    for (unsigned int i = 0; i < graph.size(); i++) 
        if (*graph[i].cbegin() == deptCity)
            return i;
    cout << "Error: city not found" << endl;
    return -1;
}
string FlightMap::getPath(const City &dept, const City &dest, int& c) const {
    for (unsigned int i = 0; i < flights.size(); i++) {
        if (flights[i].getDestinationCity() == dest && flights[i].getDepartureCity() == dept) {
            c += flights[i].getCost();
            return flights[i].getDesc();
        }
    }
    return 0;
}
bool FlightMap::deadend(const City& city, const string dest) const {
    int index = getListIndex(city);
    list<bool>::const_iterator itv = visited[index].cbegin();
    while (itv != visited[index].cend())
    {
        if (!(*itv))
            return false;
        itv++;
    }
    return true;
}
bool FlightMap::contains(stack<City> st, const City &c) const {
    while (!st.empty()) {
        if (st.top() == c) {
            return true;
        }
        st.pop();
    }
    return false;
}