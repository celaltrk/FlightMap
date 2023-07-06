/*
Celal Salih Türkmen
22102498
Section 3
*/
#ifndef __PATH_H
#define __PATH_H
#include <string>
#include "City.h"
#include <iostream>
using namespace std;
class Path {
    private:
        City departure;
        City destination;
        int id;
        int cost;
    public:
        Path();
        Path(City depart, City dest, int id, int cost);
        City getDepartureCity() const;
        City getDestinationCity() const;
        friend ostream& operator<<(ostream& out, const Path& obj);
        bool operator==(const Path &r) const;
        bool operator!=(const Path &r) const;
        bool operator<(const Path &r) const;
        bool operator>(const Path &r) const;
        bool operator<=(const Path &r) const;
        bool operator>=(const Path &r) const;
        int getID() const;
        int getCost() const;
        void setDepartureCity(City depart);
        void setDestinationCity(City dest);
        void setID(int id);
        void setCost(int cost);
        string getDesc() const;
};
#endif