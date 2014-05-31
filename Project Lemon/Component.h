#pragma once
#include <iostream>

struct Component
{
public:
	enum ComponentNames{
		POSITION,
		TEXTURE,
		VELOCITY,
		TILE
	};
	std::string readableName;
	Component::Component();
	Component(std::string name);
	virtual ~Component();
	static const std::string EnumStrings[];
	static std::string Component::getNameFromEnum(int enumVal);
};

