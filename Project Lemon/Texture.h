#pragma once
#include "Component.h"
#include "SDL.h"
struct TextureComponent :
	public Component
{
public:
	TextureComponent();
	TextureComponent(SDL_Texture *tex);
	~TextureComponent();
	SDL_Texture *tex;
	int width;
	int height;
};

