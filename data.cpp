//
// Created by Ryan Phadnis on 12/4/19.
//

#include <string>
#include <iostream>
#include "data.h"
using namespace std;

Data::Data() //default constructor
{
    name = "";
    category = "";
    goal = 0.0;
    //pledged = 0.0;
    pledged = "";
    country = "";
}

Data::Data(string n, string cat, double g, string p, string cn) //preferable constructor
{
    name = n;
    category = cat;
    goal = g;
    pledged = p;
    country = cn;
}

//ostream operator overloader
ostream& operator << (ostream& os, Data d)
{
    os << "Name: " << d.name << endl;
    os << "Category: " << d.category << endl;
    os << "Goal: " << d.goal << endl;
    os << "Pledged: " << d.pledged << endl;
    os << "Country: " << d.country << endl;
    os << endl;
    return os;
}

bool operator > (const Data &d, const Data &da)
{
    return d.goal > da.goal;
}

bool operator < (const Data &d, const Data &da)
{
    return d.goal < da.goal;
}

bool operator <= (const Data &d, const Data &da)
{
    return d.goal <= da.goal;
}