#include "Component.h"

const std::string Component::EnumStrings[] = { "position", "texture", "velocity", "tile", "elevation" };
std::string Component::getNameFromEnum(int enumVal)
{
	return EnumStrings[enumVal];
}

Component::Component() : readableName("blank componant")
{
}

Component::Component(std::string name) : readableName(name)
{
}


Component::~Component()
{
	std::cout << "dcon: " << readableName.c_str() << std::endl;
}

