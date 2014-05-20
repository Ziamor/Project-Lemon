#include "Game.h"
ComponentManager Game::componentManager;

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

	PositionComponent posComp;
	Game::componentManager.registerNewComponentType(posComp.readableName);

	TextureComponent texComp;
	Game::componentManager.registerNewComponentType(texComp.readableName);

	VelocityComponent velComp;
	Game::componentManager.registerNewComponentType(velComp.readableName);

	TileComponent tileComp;
	Game::componentManager.registerNewComponentType(tileComp.readableName);

	NewComponent<newPositionComponent> test;
	
	//test
	std::cout << newPositionComponent::componentType << std::endl;
	std::cout << newVelocityComponent::componentType << std::endl;
	std::cout << newPositionComponent::componentType << std::endl;
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

	Game::componentManager.createNewTileEntity(tileSheet_, 50, 80);
	Game::componentManager.createNewPlayerEntity(tileSheet_, 50, 80);
	Game::componentManager.dataDump();
	//std::cout << Game::componentManager.getPositionComponent(2)->x << std::endl;
	//std::cout << Game::componentManager.getTextureComponent(2)->tex << std::endl;
	//std::cout << Game::componentManager.getVelocityComponent(2)->dx << std::endl;
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
		SDL_RenderClear(renderer_);
		renderSystem_.execute();
		SDL_RenderPresent(renderer_);
	}
}