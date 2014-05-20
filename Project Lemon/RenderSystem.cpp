#include "RenderSystem.h"
#include "Position.h"
#include "Texture.h"

RenderSystem::RenderSystem()
{

}


RenderSystem::~RenderSystem()
{
}

bool RenderSystem::execute(){
	/*if (renderer_ == nullptr)
		return false;
	std::vector<int> list = Game::componentManager.getEntityListOfPositionComponents();
	for (int i = 0; i < list.size(); i++)
	{
		PositionComponent *positionComp = Game::componentManager.getPositionComponent(list[i]);
		TextureComponent *textureComp = Game::componentManager.getTextureComponent(list[i]);
		if (positionComp != nullptr && textureComp != nullptr)
		{
			SDL_Rect destRect;
			destRect.x = positionComp->x;
			destRect.y = positionComp->y;
			destRect.w = textureComp->width;
			destRect.h = textureComp->height;
			SDL_RenderCopy(renderer_, textureComp->tex, NULL, &destRect);
		}
	}*/
	return true;
}

void RenderSystem::setSDL_Renderer(SDL_Renderer *ren)
{
	renderer_ = ren;
}