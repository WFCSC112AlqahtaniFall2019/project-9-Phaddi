//
// Created by Ryan Phadnis on 12/4/19.
//CSC 112 Project 9
//

#ifndef PROJECT9_DATA_H
#define PROJECT9_DATA_H
#include <iostream>
#include <string>
using namespace std;

class Data
{
    friend ostream& operator << (ostream& os, Data d);
public:
    string name;
    string category;
    double goal;
    string pledged;
    string country;

    Data();
    Data(string n, string cat, double g, string p, string cn);

    friend bool operator < (const Data& d, const Data &da);
    friend bool operator > (const Data& d, const Data &da);
    friend bool operator <= (const Data& d, const Data &da);
};

#endif //PROJECT9_DATA_H
