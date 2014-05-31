#pragma once
#include "System.h"
#include "Game.h"
#include "Position.h"
#include "Texture.h"
#include "Tile.h"
#include "Component.h"

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

