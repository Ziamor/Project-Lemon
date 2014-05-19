#include "Texture.h"

TextureComponent::TextureComponent() : Component("texture")
{
}

TextureComponent::TextureComponent(SDL_Texture *tex) : tex(tex), Component("texture")
{
	SDL_QueryTexture(tex, NULL, NULL, &width, &height);
}


TextureComponent::~TextureComponent()
{
}
