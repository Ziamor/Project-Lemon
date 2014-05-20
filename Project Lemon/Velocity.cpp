#include "Velocity.h"

VelocityComponent::VelocityComponent() :dx(0), dy(0)
{
}

VelocityComponent::VelocityComponent(int dx, int dy) :dx(dx), dy(dy)
{
}


VelocityComponent::~VelocityComponent()
{
}

std::string Component<VelocityComponent>::componentType = "Velocity";