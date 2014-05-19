#include "Component.h"

Component::Component() : readableName("empty")
{
}

Component::Component(std::string name) : readableName(name)
{
}


Component::~Component()
{
	std::cout << "dcon";
}
