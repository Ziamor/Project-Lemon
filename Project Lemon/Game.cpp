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
	RenderSystem render_system;
	render_system.setSDL_Renderer(renderer_);
	MapManager map_manager;

	/////////
	clock_t tStart = clock();
	clock_t tEnd = clock();
	std::ofstream myfile;
	myfile.open("output.txt");
	////////////////////////////////////
	/*std::ofstream myfile;
	myfile.open("output.txt");
	clock_t tStart = clock();
	clock_t tEnd = clock();
	for (int i = 0; i < 100; i++){
	tStart = clock();
	MapManager map_manager(i);
	render_system.execute();
	tEnd = clock();
	myfile << (double)(tEnd - tStart) / CLOCKS_PER_SEC << std::endl;
	//printf("Time taken: %.2fs\n", (double)(tStart) / CLOCKS_PER_SEC);
	}
	myfile.close();
	////////////////////////////////////
	*/
	gameSubject.addObserver(&render_system);
	gameSubject.addObserver(&map_manager);

	//Region region;
	//componentManager.createNewPlayerEntity(tileSheet_, 20, 40, region);
	//componentManager.createNewTileEntity(TileComponent::GRASS, 50, 50, 0.5, region);
	//region.dataDump();
	while (running_)
	{
		clock_t tStart = clock();
		//printf("Time taken: %.2fs\n", (double)(tStart) / CLOCKS_PER_SEC);
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

		tStart = clock();
		render_system.execute();
		tEnd = clock();
		myfile << (double)(tEnd - tStart) / CLOCKS_PER_SEC << std::endl;
		SDL_RenderPresent(renderer_);

		std::this_thread::sleep_for(std::chrono::milliseconds(tStart + 17 - clock()));
	}
	myfile.close();
}