#include "Velocity.h"
VelocityComponent::VelocityComponent() :dx(0), dy(0), Component("velocity")
{
}

VelocityComponent::VelocityComponent(int dx, int dy) : dx(dx), dy(dy), Component("velocity")
{
}


VelocityComponent::~VelocityComponent()
{
}