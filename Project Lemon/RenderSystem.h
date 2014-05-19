#pragma once
#include "System.h"
#include "Game.h"

class RenderSystem :
	public System
{
public:
	RenderSystem();
	~RenderSystem();
	bool RenderSystem::execute();
};

