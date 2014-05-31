#pragma once
#include <vector>
#include <map>
#include "SDL.h"
#include "TextureManager.h"
#include "Component.h"
#include "Position.h"
#include "Texture.h"
#include "Velocity.h"
#include "Tile.h"



class ComponentManager
{
public:
	ComponentManager();
	~ComponentManager();

	void ComponentManager::addPositionComponent(int entityID, int offset, int x, int y);
	PositionComponent* ComponentManager::getPositionComponent(int entity);

	void ComponentManager::addVelocityComponent(int entityID, int offset, int dx, int dy);
	VelocityComponent* ComponentManager::getVelocityComponent(int entity);

	void ComponentManager::addTextureComponent(int entityID, int offset, SDL_Texture *tex);
	TextureComponent* ComponentManager::getTextureComponent(int entity);

	void ComponentManager::addTileComponent(int entityID, int offset, TileComponent::TileID tileID);
	TileComponent* ComponentManager::getTileComponent(int entity);

	Component* ComponentManager::getComponent(int entity, std::string readableName);

	std::vector<int> ComponentManager::getEntityListOfComponents(std::string componentType);
	void addComponentToList(int entityID, int offset, Component *component);
	int ComponentManager::createNewEntity();

	void ComponentManager::createNewTileEntity(TileComponent::TileID tileID, int x, int y);
	void ComponentManager::createNewPlayerEntity(SDL_Texture *tex, int x, int y);

	void ComponentManager::addTexture(SDL_Texture *tex, std::string name);

	void ComponentManager::dataDump();
private:
	TextureManager textureManager;
	int nextEntityID_;
	std::vector<Component*> components_;
	int componentsCount_;

	std::vector<int> entitiesLookup_;
	int entitiesLookupCount_;

	std::map<std::string, std::vector<int>> componantsLookupList_;
	std::map<std::string, int> componantsLookupListCount_;

	std::map<std::string, SDL_Texture*> textures;
};
