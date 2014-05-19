#pragma once
#include "Component.h"
struct PositionComponent :
	public Component
{
public:
	PositionComponent(int x, int y);
	~PositionComponent();
	int x, y;
};

