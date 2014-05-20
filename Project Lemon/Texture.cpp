#include "Texture.h"

TextureComponent::TextureComponent()
{
}

TextureComponent::TextureComponent(SDL_Texture *tex) : tex(tex)
{
	SDL_QueryTexture(tex, NULL, NULL, &width, &height);
}


TextureComponent::~TextureComponent()
{
}

std::string Component<TextureComponent>::componentType = "Texture";