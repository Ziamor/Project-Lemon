#pragma once
#include "SDL.h"
#include <map>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();
	void TextureManager::AddTexture(std::string name, SDL_Texture *tex);
	SDL_Texture* TextureManager::GetTexture(std::string name);
private:
	static std::map<std::string, SDL_Texture* > textures;
};

