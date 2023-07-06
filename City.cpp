/*
Celal Salih Türkmen
22102498
Section 3
*/
#include "City.h"
#include <string>
using namespace std;
City::City() {
    name = "unknown";
}
City::City(const City &r) {
    name = r.name;
}
City::City(string name) {
    this -> name = name;
}
ostream& operator<<(ostream& out, const City& obj) {
    out << obj.name;
    return out;
}
string City::getName() const {
    return name;
}
bool City::operator==(const City &r) const {
    return name == r.name;
}
bool City::operator!=(const City &r) const
{
    return !(r == *this);
}
bool City::operator<(const City &r) const
{
    return name < r.name;
}
bool City::operator>(const City &r) const
{
    return name > r.name;
}
bool City::operator<=(const City &r) const
{
    return name <= r.name;
}
bool City::operator>=(const City &r) const
{
    return name >= r.name;
}
City& City::operator=(const City &c) {
    this -> name = c.name;
    return *this;
}