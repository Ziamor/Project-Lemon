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
	void RenderSystem::setSDL_Renderer(SDL_Renderer *ren);
private:
	SDL_Renderer *renderer_;
};

