/*
Celal Salih Türkmen
22102498
Section 3
*/
#ifndef __QUERY_H
#define __QUERY_H
#include <string>
using namespace std;
class Query {
    public:
        Query();
        Query(string t, int c);
        int cost;
        string text;
        bool operator<(const Query &r) const;
        bool operator>(const Query &r) const;
        bool operator==(const Query &r) const;
};
#endif