#pragma once
#include <iostream>

struct Component
{
public:
	enum ComponentNames{
		POSITION,
		TEXTURE,
		VELOCITY,
		TILE,
		ELEVATION
	};
	std::string readableName; // Name of the component type
	Component::Component();
	Component(std::string name);
	virtual ~Component();
	static const std::string EnumStrings[];
	static std::string Component::getNameFromEnum(int enumVal);
};

