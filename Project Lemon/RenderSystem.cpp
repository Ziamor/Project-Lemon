#include "RenderSystem.h"

RenderSystem::RenderSystem()
{

}


RenderSystem::~RenderSystem()
{
}

bool RenderSystem::execute(){
	if (renderer_ == nullptr)
		return false;
	std::vector<int> list = Game::componentManager.getEntityListOfComponents(Component::getNameFromEnum(Component::POSITION));
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
			TileComponent *tileComp = Game::componentManager.getTileComponent(list[i]);
			if (tileComp != nullptr)
			{
				SDL_Rect srcRect = tileComp->srcrect;
				destRect.w = tileComp->tileSize;
				destRect.h = tileComp->tileSize;
				SDL_RenderCopy(renderer_, textureComp->tex, &srcRect, &destRect);
			}
			else
				SDL_RenderCopy(renderer_, textureComp->tex, NULL, &destRect);
		}	
	}
	return true;
}

void RenderSystem::setSDL_Renderer(SDL_Renderer *ren)
{
	renderer_ = ren;
}