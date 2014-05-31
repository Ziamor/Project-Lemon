#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <assert.h>
#include  <vector>
#include <string>
#include "RenderSystem.h"
#include "MapSystem.h"
#include "Component.h"
#include "ComponentManager.h"
#include "Position.h"
#include "Texture.h"
#include "PerlinNoise.h"

class Game
{
public:
	Game();
	~Game();

	static ComponentManager componentManager;
	static const int SCREEN_WIDTH;
	static const int SCREEN_HEIGHT;
private:
	void Game::gameLoop();
	bool running_ = true;
	SDL_Window *window_;
	SDL_Renderer *renderer_;
	SDL_Texture *tileSheet_;

	TextureManager textureManager;
};

