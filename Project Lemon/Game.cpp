#include "Game.h"
ComponentManager Game::componentManager;
const int Game::SCREEN_WIDTH = 640;
const int Game::SCREEN_HEIGHT = 480;
Game::Game()
{
	assert(SDL_Init(SDL_INIT_EVERYTHING) == 0);

	window_ = SDL_CreateWindow("Project Lemon", 100, 100, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	assert(window_ != nullptr);

	renderer_ = SDL_CreateRenderer(window_, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	assert(renderer_ != nullptr);

	std::string tileSheetPath = "res/textures/tilesheet.png";
	tileSheet_ = IMG_LoadTexture(renderer_, tileSheetPath.c_str());
	assert(tileSheet_ != nullptr);

	textureManager.AddTexture("tilesheet", tileSheet_);

	gameLoop();
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void Game::gameLoop(){
	RenderSystem renderSystem_;
	renderSystem_.setSDL_Renderer(renderer_);

	MapSystem mapSystem;

//	Game::componentManager.createNewTileEntity(tileSheet_, 50, 80);
//	Game::componentManager.createNewPlayerEntity(tileSheet_, 50, 80);
//	Game::componentManager.dataDump();
	
	while (running_)
	{		
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				running_ = false;
		}			
		SDL_RenderClear(renderer_);
		renderSystem_.execute();
		SDL_RenderPresent(renderer_);
	}
}