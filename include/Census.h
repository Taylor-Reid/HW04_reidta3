

#pragma once
#include <string>
using namespace std;


class cEntry {
public:
	int pop;
	double x;
	double y;
};


class Census {
public:
	
	virtual void build(cEntry* c, int n) = 0;
	
	
	virtual cEntry* getNearest(double x, double y) = 0;
};