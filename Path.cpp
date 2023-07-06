/*
Celal Salih Türkmen
22102498
Section 3
*/
#include "City.h"
#include "Path.h"
#include <string>
#include <iostream>
using namespace std;
Path::Path() {}
Path::Path(City depart, City dest, int id, int cost) : departure(depart), destination(dest), id(id), cost(cost) {}
City Path::getDepartureCity() const {
    return departure;
}
City Path::getDestinationCity() const {
    return destination;
}
ostream &operator<<(ostream &out, const Path &obj) {
    out << "Flight #" << obj.id << " from " << obj.departure << " to " << obj.destination << ", Cost: " << obj.cost << " TL";
    return out;
}
string Path::getDesc() const {
    return "Flight #" + to_string(id) + " from " + departure.getName() + " to " + destination.getName() + ", Cost: " + to_string(cost) + " TL";
}
int Path::getID() const {
    return id;
}
int Path::getCost() const {
    return cost;
}
void Path::setDepartureCity(City depart) {
    departure = depart;
}
void Path::setDestinationCity(City dest) {
    destination = dest;
}
void Path::setID(int id) {
    this -> id = id;
}
void Path::setCost(int cost) {
    this -> cost = cost;
}
bool Path::operator==(const Path &r) const {
    return id == r.id;
}
bool Path::operator!=(const Path &r) const
{
    return id != r.id;
}
bool Path::operator<(const Path &r) const
{
    return id < r.id;
}
bool Path::operator>(const Path &r) const
{
    return id > r.id;
}
bool Path::operator<=(const Path &r) const
{
    return id <= r.id;
}
bool Path::operator>=(const Path &r) const
{
    return id >= r.id;
}