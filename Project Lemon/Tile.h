#pragma once
#include "Component.h"
#include "SDL.h"

struct TileComponent :
	public Component
{
public:
	enum TileID
	{
		GRASS, WATER, LAVA
	};

	TileComponent();
	TileComponent(TileID tileID, int tileSize);
	~TileComponent();
	SDL_Rect srcrect;;
	TileID tileID;
	static int tileSize;
	static int tilesPerRow;
	static int tilesPerCol;
};

