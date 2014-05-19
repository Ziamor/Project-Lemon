#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <assert.h>
#include  <vector>
#include <string>
#include "RenderSystem.h"
#include "Component.h"
#include "ComponentManager.h"
#include "Position.h"
#include "Texture.h"

class Game
{
public:
	Game();
	~Game();

	static ComponentManager componentManager;
private:
	void Game::gameLoop();
	bool running_ = true;	
	SDL_Window *window_;
	SDL_Renderer *renderer_;
	SDL_Texture *tileSheet_;	
};

