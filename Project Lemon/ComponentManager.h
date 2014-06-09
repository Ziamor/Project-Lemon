#pragma once
#include <vector>
#include <map>
#include "SDL.h"
#include "Region.h"
#include "TextureManager.h"
#include "Component.h"
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

	void ComponentManager::addPositionComponent(int entityID, int x, int y);
	PositionComponent* ComponentManager::getPositionComponent(int entity);

	void ComponentManager::addVelocityComponent(int entityID, int dx, int dy);
	VelocityComponent* ComponentManager::getVelocityComponent(int entity);

	void ComponentManager::addTextureComponent(int entityID, SDL_Texture *tex);
	TextureComponent* ComponentManager::getTextureComponent(int entity);

	void ComponentManager::addTileComponent(int entityID, TileComponent::TileID tileID);
	TileComponent* ComponentManager::getTileComponent(int entity);

	void ComponentManager::addElevationComponent(int entityID, double elevation);
	ElevationComponent* ComponentManager::getElevationComponent(int entity);

	Component* ComponentManager::getComponent(int entity, std::string readableName);

	std::vector<int> ComponentManager::getEntityListOfComponents(std::string componentType);
	void addComponentToList(int entityID, Component *component);
	int ComponentManager::createNewEntity();

	int ComponentManager::createNewTileEntity(TileComponent::TileID tileID, int x, int y, double elevation);
	int ComponentManager::createNewPlayerEntity(SDL_Texture *tex, int x, int y);

	void ComponentManager::addTexture(SDL_Texture *tex, std::string name);

private:
	TextureManager textureManager;
	int nextEntityID_;
	std::vector<Component*> components_;
	int componentsCount_;

	std::vector<int> entitiesLookup_;

	std::map<std::string, std::vector<int>> componantsLookupList_;

	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, Region*> regions;
};
