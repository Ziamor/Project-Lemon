#pragma once
#include <iostream>

struct Component
{
public:
	std::string readableName;
	Component::Component();
	Component(std::string name);
	virtual ~Component();
};

