#pragma once
#include "Component.h"
struct VelocityComponent :
	Component
{
public:
	VelocityComponent(int dx, int dy);
	~VelocityComponent();
	int dx, dy;
};

