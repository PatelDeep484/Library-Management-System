/*
Final Project Milestone 5
Module: Streamable
Filename: Streamable.h
Version 1.0
Author	Deep Patel
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/
#ifndef SDDS_STREAMABLE_H
#define SDDS_STREAMABLE_H
#include <iostream>
using namespace std;
namespace sdds {
    class Streamable {
    public:
        virtual ostream& write(ostream& os) const = 0;
        virtual istream& read(istream& is) = 0;
        virtual bool conIO(ios& io) const = 0;
        virtual operator bool() const = 0;
        virtual ~Streamable();
    };
    ostream& operator<<(ostream& os, const Streamable& ST);
    istream& operator>>(istream& is, Streamable& ST);
}

#endif 



