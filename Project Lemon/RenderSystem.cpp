#include "RenderSystem.h"

RenderSystem::RenderSystem()
{

}


RenderSystem::~RenderSystem()
{
}

bool RenderSystem::execute(){
	std::vector<Region*> *active_regions = &MapManager::active_regions;
	if (renderer_ == nullptr || active_regions == nullptr)
		return false;

	for (size_t r = 0; r < active_regions->size(); r++){
		if (r == 1)
			std::cout << "";
		Region *region = (*active_regions)[r];
		std::vector<int> list = region->getEntityListOfComponents(Component::getNameFromEnum(Component::TEXTURE));
		for (size_t i = 0; i < list.size(); i++)
		{
			int entityID = list[i];
			PositionComponent *positionComp = Game::componentManager.getPositionComponent(entityID, *region);
			TextureComponent *textureComp = Game::componentManager.getTextureComponent(entityID, *region);
			if (positionComp != nullptr && textureComp != nullptr)
			{
				SDL_Rect destRect;
				destRect.x = positionComp->x + MapManager::get_view_x() * -16;
				destRect.y = positionComp->y + MapManager::get_view_y() * -16;
				destRect.w = textureComp->width;
				destRect.h = textureComp->height;
				TileComponent *tileComp = Game::componentManager.getTileComponent(entityID, *region);
				if (tileComp != nullptr)
				{
					SDL_Rect srcRect = tileComp->srcrect;
					destRect.w = tileComp->tileSize;
					destRect.h = tileComp->tileSize;
					SDL_Texture *tex = *(&textureComp->tex);
					SDL_Texture* auxtexture = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 500, 500);
					int color = int(Game::componentManager.getElevationComponent(entityID, *region)->elevation * 128 + 128);
					SDL_SetTextureColorMod(tex, color, color, color);
					SDL_RenderCopy(renderer_, tex, &srcRect, &destRect);
				}
				else
					SDL_RenderCopy(renderer_, textureComp->tex, NULL, &destRect);
			}
		}
	}
	return true;
}

void RenderSystem::onNotify(const int entityID, Observer::event_type event)
{

}
void RenderSystem::setSDL_Renderer(SDL_Renderer *ren)
{
	renderer_ = ren;
}