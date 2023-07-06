/*
Celal Salih Türkmen
22102498
Section 3
*/
#ifndef __CITY_H
#define __CITY_H
#include <iostream>
#include <string>
using namespace std;
class City {
    public:
        City();
        City(const City& r);
        City& operator=(const City& c);
        City(string name);
        string getName() const;
        friend ostream& operator<<(ostream& out, const City& obj);
        bool operator==(const City &r) const;
        bool operator!=(const City &r) const;
        bool operator<(const City &r) const;
        bool operator>(const City &r) const;
        bool operator<=(const City &r) const;
        bool operator>=(const City &r) const;
    private: 
        string name;
};
#endif