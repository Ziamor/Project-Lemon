#pragma once
#include "System.h"
class RenderSystem :
	public System
{
public:
	RenderSystem();
	~RenderSystem();
	bool RenderSystem::execute();
};

