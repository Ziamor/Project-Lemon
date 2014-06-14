#include "RenderSystem.h"

RenderSystem::RenderSystem()
{

}


RenderSystem::~RenderSystem()
{
}

bool RenderSystem::execute(){
	// Gets all regions that are currently visable
	std::vector<Region*> *active_regions = &MapManager::active_regions;
	if (renderer_ == nullptr || active_regions == nullptr)
		return false;
	//Loop through each visable region
	for (size_t r = 0; r < active_regions->size(); r++){
		Region *region = (*active_regions)[r];
		//Get a list of all entites inside the region that have a texture component
		std::vector<int> list = region->getEntityListOfComponents(Component::getNameFromEnum(Component::TEXTURE));
		for (size_t i = 0; i < list.size(); i++)
		{
			int entityID = list[i];
			//get the position and texture components
			PositionComponent *positionComp = Game::componentManager.getPositionComponent(entityID, *region);
			TextureComponent *textureComp = Game::componentManager.getTextureComponent(entityID, *region);
			//check if the entity has valid components for rendering
			if (positionComp != nullptr && textureComp != nullptr)
			{
				//set up the destination rectangle
				SDL_Rect destRect;
				destRect.x = positionComp->x + MapManager::get_view_x() * -16;
				destRect.y = positionComp->y + MapManager::get_view_y() * -16;
				destRect.w = textureComp->width;
				destRect.h = textureComp->height;

				//try to see if the entity is a map Tile by checking if it has a Tile Component
				TileComponent *tileComp = Game::componentManager.getTileComponent(entityID, *region);
				if (tileComp != nullptr)
				{
					//Seeing as it is a Tile we need to get the tile from the texture so we set up a source rectangle
					SDL_Rect srcRect = tileComp->srcrect;
					destRect.w = tileComp->tileSize;
					destRect.h = tileComp->tileSize;

					//Get the  tilesheet texture
					SDL_Texture *tex = *(&textureComp->tex);

					//If we have an elevation comp, add a tint to it give depth to the mountins
					ElevationComponent *elevationComp = Game::componentManager.getElevationComponent(entityID, *region);
					if (elevationComp != nullptr){
						int color = int(elevationComp->elevation * 128 + 128);
						SDL_SetTextureColorMod(tex, color, color, color);
					}
					//Render the tile
					SDL_RenderCopy(renderer_, tex, &srcRect, &destRect);
				}
				else
					//Render the texture
					SDL_RenderCopy(renderer_, textureComp->tex, NULL, &destRect);
			}
		}
	}
	return true;
}

void RenderSystem::onNotify(const int entityID, Observer::event_type event)
{

}
//Sets the renderer
void RenderSystem::setSDL_Renderer(SDL_Renderer *ren)
{
	renderer_ = ren;
}