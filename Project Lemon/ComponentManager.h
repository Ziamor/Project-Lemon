#pragma once
#include <vector>
#include <map>
#include "SDL.h"
#include "Component.h"
#include "Region.h"
#include "TextureManager.h"
#include "Position.h"
#include "Texture.h"
#include "Velocity.h"
#include "Tile.h"
#include "Elevation.h"

class ComponentManager
{
public:
	ComponentManager();
	~ComponentManager();

	void ComponentManager::addPositionComponent(int entityID, int x, int y, Region &region);
	PositionComponent* ComponentManager::getPositionComponent(int entity, Region &region);

	void ComponentManager::addVelocityComponent(int entityID, int dx, int dy, Region &region);
	VelocityComponent* ComponentManager::getVelocityComponent(int entity, Region &region);

	void ComponentManager::addTextureComponent(int entityID, SDL_Texture *tex, Region &region);
	TextureComponent* ComponentManager::getTextureComponent(int entity, Region &region);

	void ComponentManager::addTileComponent(int entityID, TileComponent::TileID tileID, Region &region);
	TileComponent* ComponentManager::getTileComponent(int entity, Region &region);

	void ComponentManager::addElevationComponent(int entityID, double elevation, Region &region);
	ElevationComponent* ComponentManager::getElevationComponent(int entity, Region &region);

	Component* ComponentManager::getComponent(int entity, std::string readableName, Region &region);

	int ComponentManager::createNewEntity(Region &region);

	int ComponentManager::createNewTileEntity(TileComponent::TileID tileID, int x, int y, double elevation, Region &region);
	int ComponentManager::createNewPlayerEntity(SDL_Texture *tex, int x, int y, Region &region);

	void ComponentManager::addTexture(SDL_Texture *tex, std::string name);

private:
	TextureManager textureManager;
	int nextEntityID_;

	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, Region*> regions;
};
