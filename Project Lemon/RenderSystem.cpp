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
		int entityID = list[i];
		PositionComponent *positionComp = Game::componentManager.getPositionComponent(entityID);
		TextureComponent *textureComp = Game::componentManager.getTextureComponent(entityID);
		if (positionComp != nullptr && textureComp != nullptr)
		{
			SDL_Rect destRect;
			destRect.x = positionComp->x;
			destRect.y = positionComp->y;
			destRect.w = textureComp->width;
			destRect.h = textureComp->height;
			TileComponent *tileComp = Game::componentManager.getTileComponent(entityID);
			if (tileComp != nullptr)
			{
				SDL_Rect srcRect = tileComp->srcrect;
				destRect.w = tileComp->tileSize;
				destRect.h = tileComp->tileSize;
				SDL_Texture *tex = *(&textureComp->tex);
				SDL_Texture* auxtexture = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 500, 500);
				int color = Game::componentManager.getElevationComponent(entityID)->elevation * 128 + 128;
				SDL_SetTextureColorMod(tex, color, color, color);
				SDL_RenderCopy(renderer_, tex, &srcRect, &destRect);
			}
			else
				SDL_RenderCopy(renderer_, textureComp->tex, NULL, &destRect);
		}	
	}
	return true;
}

void RenderSystem::onNotify(const int entityID, System::event_type event)
{
	
}
void RenderSystem::setSDL_Renderer(SDL_Renderer *ren)
{
	renderer_ = ren;
}