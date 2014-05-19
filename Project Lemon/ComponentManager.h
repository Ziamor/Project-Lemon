#pragma once
#include <vector>
#include "SDL.h"
#include "Component.h"
#include "Position.h"
#include "Texture.h"
#include "VelocityComponent.h"
#include <memory>
class ComponentManager
{
public:
	ComponentManager();
	~ComponentManager();
	void ComponentManager::addPositionComponentToEntity(int entityID, PositionComponent &comp);
	void ComponentManager::addPositionComponent(int entityID, int offset, int x, int y);
	PositionComponent* ComponentManager::getPositionComponent(int entity);

	void ComponentManager::addVelocityComponentToEntity(int entityID, VelocityComponent &comp);
	void ComponentManager::addVelocityComponent(int entityID, int offset, int dx, int dy);
	VelocityComponent* ComponentManager::getVelocityComponent(int entity);

	void ComponentManager::addTextureComponentToEntity(int entityID, TextureComponent &comp);
	void ComponentManager::addTextureComponent(int entityID, int offset, SDL_Texture *tex);
	TextureComponent* ComponentManager::getTextureComponent(int entity);

	void ComponentManager::addComponentToList(int entityID, int offset, Component *component, std::vector<int> &list, int &listCount);
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

	std::vector<int> positionComponentsLookup_;
	int positionComponentsLookupCount_;

	std::vector<int> velocityComponentsLookup_;
	int velocityComponentsLookupCount_;

	std::vector<int> textureComponentsLookup_;
	int textureComponentsLookupCount_;
};

