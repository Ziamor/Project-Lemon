#include "Position.h"

PositionComponent::PositionComponent() : x(-1), y(-1), Component("position")
{

}

PositionComponent::PositionComponent(int x, int y) : x(x), y(y), Component("position")
{

}


PositionComponent::~PositionComponent()
{
}
