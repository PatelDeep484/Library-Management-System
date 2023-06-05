/*
Final Project Milestone 5
Module: Streamable
Filename: Streamable.cpp
Version 1.0
Author	Deep Patel
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------*/
#include "Streamable.h"
using namespace std;
namespace sdds {
	Streamable::~Streamable() {}
	ostream& operator<<(ostream& os, const Streamable& ST) {
		if (ST) ST.write(os);
		return os;
	}
	istream& operator>>(istream& is, Streamable& ST) { return ST.read(is); }

}