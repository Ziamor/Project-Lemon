#include "Texture.h"


TextureComponent::TextureComponent(SDL_Texture *tex) : tex(tex), Component("texture")
{
}


TextureComponent::~TextureComponent()
{
}
