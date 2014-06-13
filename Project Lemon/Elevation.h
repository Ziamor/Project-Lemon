#pragma once
#include "Component.h"
class ElevationComponent :
	public Component
{
public:
	ElevationComponent(double elevation);
	~ElevationComponent();
	double elevation;
};

