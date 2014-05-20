#include "Position.h"

PositionComponent::PositionComponent() : x(-1), y(-1)
{

}

PositionComponent::PositionComponent(int x, int y) : x(x), y(y)
{

}


PositionComponent::~PositionComponent()
{
}

std::string Component<PositionComponent>::componentType = "Position";
