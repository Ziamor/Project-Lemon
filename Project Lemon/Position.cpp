#include "Position.h"
PositionComponent::PositionComponent() : x(-1), y(-1), Component(getNameFromEnum(POSITION))
{

}

PositionComponent::PositionComponent(int x, int y) : x(x), y(y), Component(getNameFromEnum(POSITION))
{

}


PositionComponent::~PositionComponent()
{
}