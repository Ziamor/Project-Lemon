#pragma once
#include "Component.h"
struct PositionComponent :
	public Component<PositionComponent>
{
public:
	PositionComponent();
	PositionComponent(int x, int y);
	~PositionComponent();
	int x, y;
};

