#pragma once
#include "Observer.h"
class System :
	public Observer
{
public:
	System(){} // Added definition in header file so we dont have too many pesky .cpp files
	virtual ~System(){}
	virtual bool execute() = 0;
};

