#pragma once
#include "Component.h"
struct VelocityComponent :
	Component
{
public:
	VelocityComponent();
	VelocityComponent(int dx, int dy);
	~VelocityComponent();
	int dx, dy;
};

