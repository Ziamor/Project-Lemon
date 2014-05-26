#include "Component.h"
Component::Component() : readableName("blank componant")
{
}

Component::Component(std::string name) : readableName(name)
{
}


Component::~Component()
{
	std::cout << "dcon";
}

