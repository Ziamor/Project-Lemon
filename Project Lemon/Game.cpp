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

	gameLoop(); // Start the game loop
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void Game::gameLoop(){
	clock_t tStart = clock();

	// Set up the systems/managers
	MapManager map_manager;
	RenderSystem render_system;

	render_system.setSDL_Renderer(renderer_); // Give the render system access to the sdl renderer
	gameSubject.addObserver(&render_system); // Register the render system to listen to Game
	gameSubject.addObserver(&map_manager); // Register the map manager to listen to Game

	//Loop begins
	while (running_)
	{
		tStart = clock();
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type) {
			case SDL_QUIT:
				running_ = false;
				break;
			case SDL_KEYUP:
				break;
			case SDL_KEYDOWN:
				// Notify any observer that is listening for keyboard events
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
		render_system.execute(); //execute the render system
		SDL_RenderPresent(renderer_);

		std::this_thread::sleep_for(std::chrono::milliseconds(tStart + 17 - clock())); //Sleep so that each frame is ~17 milliseconds long
	}
}