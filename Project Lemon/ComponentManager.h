#pragma once
#include <vector>
#include <map>
#include "SDL.h"
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

	void ComponentManager::addTileComponent(int entityID, int offset);
	TileComponent* ComponentManager::getTileComponent(int entity);

	Component* ComponentManager::getComponent(int entity, std::string readableName);

	std::vector<int> ComponentManager::getEntityListOfComponents(std::string componentType);
	void addComponentToList(int entityID, int offset, Component *component);
	int ComponentManager::createNewEntity();

	void ComponentManager::createNewTileEntity(SDL_Texture *tex, int x, int y);
	void ComponentManager::createNewPlayerEntity(SDL_Texture *tex, int x, int y);

	void ComponentManager::dataDump();
private:
	int nextEntityID_;
	std::vector<Component*> components_;
	int componentsCount_;

	std::vector<int> entitiesLookup_;
	int entitiesLookupCount_;

	std::map<std::string, std::vector<int>> componantsLookupList_;
	std::map<std::string, int> componantsLookupListCount_;

	/*std::vector<int> positionComponentsLookup_;
	int positionComponentsLookupCount_;

	std::vector<int> velocityComponentsLookup_;
	int velocityComponentsLookupCount_;

	std::vector<int> textureComponentsLookup_;
	int textureComponentsLookupCount_;*/
};
