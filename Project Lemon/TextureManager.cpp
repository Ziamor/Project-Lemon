#include "TextureManager.h"

std::map<std::string, SDL_Texture* > TextureManager::textures;

TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}
//Cache a texture
void TextureManager::AddTexture(std::string name, SDL_Texture *tex){
	if (tex != nullptr && textures.count(name) == 0)
		textures[name] = tex;
}
SDL_Texture* TextureManager::GetTexture(std::string name){
	if (textures.count(name) > 0)
		return textures[name];
	else
		return nullptr;
}
