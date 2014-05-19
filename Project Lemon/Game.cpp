#include "Game.h"

Game::Game()
{
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

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

	gameLoop();
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void Game::gameLoop(){
	ComponentManager componentManager;
	componentManager.createNewTileEntity(tileSheet_, 50, 80);
	componentManager.createNewPlayerEntity(tileSheet_, 50, 80);
	componentManager.dataDump();
	//std::cout << componentManager.getPositionComponent(2)->x << std::endl;
	//std::cout << componentManager.getTextureComponent(2)->tex << std::endl;
	//std::cout << componentManager.getVelocityComponent(2)->dx << std::endl;
	/*for (int i = 2; i < 10; i++){
		componentManager.createNewPlayerEntity(tileSheet_, 50, 80);
		if (componentManager.getPositionComponent(i) == nullptr)
			std::cout << "Not a valid pointer";
		else
			std::cout << componentManager.getPositionComponent(i)->x;
	}*/
	while (running_)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				running_ = false;
		}
	}
}