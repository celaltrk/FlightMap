/*
Celal Salih Türkmen
22102498
Section 3
*/
#include "Query.h"
bool Query::operator<(const Query &r) const {
    return cost < r.cost;
}
bool Query::operator>(const Query &r) const {
    return cost > r.cost;
}
bool Query::operator==(const Query &r) const {
    return cost == r.cost;
}
Query::Query(){
    cost = 0;
};
Query::Query(string s, int c){
    text = s;
    cost = c;
};
