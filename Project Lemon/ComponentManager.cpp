#include "ComponentManager.h"


ComponentManager::ComponentManager() :nextEntityID_(1), entitiesLookupCount_(1), componentsCount_(0)
{
}


ComponentManager::~ComponentManager()
{
}
#pragma region
void ComponentManager::addPositionComponentToEntity(int entityID, PositionComponent &comp) {

}

void ComponentManager::addPositionComponent(int entityID, int offset, int x, int y) {
	PositionComponent *position = new PositionComponent(x, y);
	addComponentToList(entityID, offset, position, componantsLookupList_[position->readableName], componantsLookupListCount_[position->readableName]);
}

PositionComponent* ComponentManager::getPositionComponent(int entityID) {
	int offset = componantsLookupList_["position"][entityID];//<---change this!

	int index = entitiesLookup_[entityID] + offset;

	Component *comp = components_[index];
	PositionComponent* postionComponent = dynamic_cast<PositionComponent*>(comp);

	if (postionComponent != nullptr)
		return postionComponent;
	return nullptr;
}

std::vector<int> ComponentManager::getEntityListOfPositionComponents()
{
	std::vector<int> entitiesIdWithComp;
	for (int i = 0; i < componantsLookupListCount_["position"]; i++)
	{
		if (componantsLookupList_["position"][i] >= 0)
			entitiesIdWithComp.push_back(i);
	}
	return entitiesIdWithComp;
}
#pragma endregion Position Components

#pragma region
void ComponentManager::addVelocityComponentToEntity(int entityID, VelocityComponent &comp) {

}

void ComponentManager::addVelocityComponent(int entityID, int offset, int dx, int dy) {
	VelocityComponent *velocity = new VelocityComponent(dx, dy);
	addComponentToList(entityID, offset, velocity, velocityComponentsLookup_, velocityComponentsLookupCount_);
}

VelocityComponent* ComponentManager::getVelocityComponent(int entityID) {
	int index = entitiesLookup_[entityID] + velocityComponentsLookup_[entityID];

	Component *comp = components_[index];
	VelocityComponent* velocityComponent = dynamic_cast<VelocityComponent*>(comp);

	if (velocityComponent != nullptr)
		return velocityComponent;
	return nullptr;
}

#pragma endregion Velocity Components

#pragma region
void ComponentManager::addTextureComponentToEntity(int entityID, TextureComponent &comp) {
}

void ComponentManager::addTextureComponent(int entityID, int offset, SDL_Texture *tex) {
	TextureComponent *texture = new TextureComponent(tex);
	addComponentToList(entityID, offset, texture, textureComponentsLookup_, textureComponentsLookupCount_);
}

TextureComponent* ComponentManager::getTextureComponent(int entityID) {
	int index = entitiesLookup_[entityID] + textureComponentsLookup_[entityID];

	Component *comp = components_[index];
	TextureComponent* textureComponent = dynamic_cast<TextureComponent*>(comp);

	if (textureComponent != nullptr)
		return textureComponent;
	return nullptr;
}
#pragma endregion Texture Components

#pragma region
/*
void ComponentManager::addTileComponentToEntity(int entityID, PositionComponent &comp) {

}

void ComponentManager::addTileComponent(int entityID, int offset, int x, int y) {
PositionComponent *position = new PositionComponent(x, y);
addComponentToList(entityID, offset, position, positionComponentsLookup_, positionComponentsLookupCount_);
}

PositionComponent* ComponentManager::getTileComponent(int entityID) {
int index = entitiesLookup_[entityID] + positionComponentsLookup_[entityID];

Component *comp = components_[index];
PositionComponent* postionComponent = dynamic_cast<PositionComponent*>(comp);

if (postionComponent != nullptr)
return postionComponent;
return nullptr;
}

std::vector<int> ComponentManager::getEntityListOfTileComponents()
{
std::vector<int> entitiesIdWithComp;
for (int i = 0; i < positionComponentsLookupCount_; i++)
{
if (positionComponentsLookup_[i] >= 0)
entitiesIdWithComp.push_back(i);
}
return entitiesIdWithComp;
}*/
#pragma endregion Tile Components

bool ComponentManager::registerNewComponentType(std::string componantReadableName)
{
	if (componantsLookupList_.find(componantReadableName) == componantsLookupList_.end()) {
		std::vector<int> componentsLookup_;
		componantsLookupList_[componantReadableName] = componentsLookup_;
		componantsLookupListCount_[componantReadableName] = 0;
		return true;
	}
	else {
		return false;
	}
}
void ComponentManager::addComponentToList(int entityID, int offset, Component *component, std::vector<int> &list, int &listCount)
{
	components_.push_back(component);
	componentsCount_++;

	if (list.size() <= entityID)
	{
		int oldEndIndex = list.size();
		list.resize(list.size() + 100);
		for (int i = oldEndIndex; i < oldEndIndex + 100; i++)
			list[i] = -1;
	}
	list[entityID] = offset;
	listCount++;
}

int ComponentManager::createNewEntity()
{
	int entityID = nextEntityID_++;
	int startIndex = componentsCount_;

	if (entitiesLookup_.size() <= entityID)
	{
		int oldEndIndex = entitiesLookup_.size();
		entitiesLookup_.resize(entitiesLookup_.size() + 100);
		for (int i = oldEndIndex; i < oldEndIndex + 100; i++)
			entitiesLookup_[i] = -1;
	}
	entitiesLookup_[entityID] = startIndex;
	entitiesLookupCount_++;

	return entityID;
}

void ComponentManager::createNewTileEntity(SDL_Texture *tex, int x, int y)
{
	int entityID = createNewEntity();
	int offset = 0;

	addPositionComponent(entityID, offset++, x, y);
	addTextureComponent(entityID, offset++, tex);
}

void ComponentManager::createNewPlayerEntity(SDL_Texture *tex, int x, int y)
{
	int entityID = createNewEntity();
	int offset = 0;

	addPositionComponent(entityID, offset++, x, y);
	addTextureComponent(entityID, offset++, tex);
	addVelocityComponent(entityID, offset++, 0, 0);;
}

void ComponentManager::dataDump()
{
	std::cout << "Entity Lookup Table" << std::endl;
	for (int i = 0; i < entitiesLookupCount_; i++)
	{
		if (entitiesLookup_[i] >= 0)
			std::cout << "Entity: " << i << " start index: " << entitiesLookup_[i] << std::endl;
	}
	std::cout << std::endl << "Position Lookup Table" << std::endl;
	for (int i = 0; i < entitiesLookupCount_; i++)
	{
		if (componantsLookupList_["position"][i] >= 0)
			std::cout << "Entity: " << i << " offset: " << componantsLookupList_["position"][i] << std::endl;
	}
	std::cout << std::endl << "Texture Lookup Table" << std::endl;
	for (int i = 0; i < entitiesLookupCount_; i++)
	{
		if (textureComponentsLookup_[i] >= 0)
			std::cout << "Entity: " << i << " offset: " << textureComponentsLookup_[i] << std::endl;
	}
	std::cout << std::endl << "Velocity Lookup Table" << std::endl;
	for (int i = 0; i < entitiesLookupCount_; i++)
	{
		if (velocityComponentsLookup_[i] >= 0)
			std::cout << "Entity: " << i << " offset: " << velocityComponentsLookup_[i] << std::endl;
	}
	std::cout << std::endl << "Components Table" << std::endl;
	for (int i = 0; i < componentsCount_; i++)
	{
		std::cout << "Component: " << components_[i]->readableName.c_str() << std::endl;
	}
}