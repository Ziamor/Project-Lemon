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

	gameSubject.addObserver(&renderSystem_);
	gameSubject.addObserver(&mapSystem);
	while (running_)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type) {
			case SDL_QUIT:
				break;
			case SDL_KEYUP:
				break;
			case SDL_KEYDOWN:
				if (e.key.keysym.scancode == SDL_SCANCODE_UP)
					gameSubject.notify(-1, System::event_type::KEY_UP);
				else if (e.key.keysym.scancode == SDL_SCANCODE_DOWN)
					gameSubject.notify(-1, System::event_type::KEY_DOWN);
				else if (e.key.keysym.scancode == SDL_SCANCODE_LEFT)
					gameSubject.notify(-1, System::event_type::KEY_LEFT);
				else if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT)
					gameSubject.notify(-1, System::event_type::KEY_RIGHT);
				break;
			default:
				break;
			}

		}
		SDL_RenderClear(renderer_);
		renderSystem_.execute();
		SDL_RenderPresent(renderer_);
	}
}