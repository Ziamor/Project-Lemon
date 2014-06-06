#include "ComponentManager.h"

ComponentManager::ComponentManager() :nextEntityID_(1), entitiesLookupCount_(1), componentsCount_(0)
{
}


ComponentManager::~ComponentManager()
{
}
#pragma region

void ComponentManager::addPositionComponent(int entityID, int x, int y) {
	PositionComponent *position = new PositionComponent(x, y);
	addComponentToList(entityID, position);
}

PositionComponent* ComponentManager::getPositionComponent(int entityID) {
	PositionComponent* postionComponent;
	Component *comp = getComponent(entityID, Component::getNameFromEnum(Component::POSITION));
	postionComponent = dynamic_cast<PositionComponent*>(comp);

	if (postionComponent != nullptr)
		return postionComponent;
	return nullptr;
}

std::vector<int> ComponentManager::getEntityListOfComponents(std::string readableName)
{
	std::vector<int> entitiesIdWithComp;
	if (componantsLookupListCount_.find(readableName) == componantsLookupListCount_.end())
		return entitiesIdWithComp;
	for (int i = 0; i <= componantsLookupListCount_[readableName]; i++)
	{
		if (componantsLookupList_[readableName][i] >= 0)
			entitiesIdWithComp.push_back(i);
	}
	return entitiesIdWithComp;
}
#pragma endregion Position Components

#pragma region

void ComponentManager::addVelocityComponent(int entityID, int dx, int dy) {
	VelocityComponent *velocity = new VelocityComponent(dx, dy);
	addComponentToList(entityID, velocity);
}

VelocityComponent* ComponentManager::getVelocityComponent(int entityID) {
	VelocityComponent* velocityComponent;
	Component *comp = getComponent(entityID, Component::getNameFromEnum(Component::VELOCITY));
	velocityComponent = dynamic_cast<VelocityComponent*>(comp);

	if (velocityComponent != nullptr)
		return velocityComponent;
	return nullptr;
}

#pragma endregion Velocity Components

#pragma region

void ComponentManager::addTextureComponent(int entityID, SDL_Texture *tex) {
	TextureComponent *texture = new TextureComponent(tex);
	addComponentToList(entityID, texture);
}

TextureComponent* ComponentManager::getTextureComponent(int entityID) {
	TextureComponent* texComp;
	Component *comp = getComponent(entityID, Component::getNameFromEnum(Component::TEXTURE));
	texComp = dynamic_cast<TextureComponent*>(comp);

	if (texComp != nullptr)
		return texComp;
	return nullptr;
}
#pragma endregion Texture Components

#pragma region

void ComponentManager::addTileComponent(int entityID, TileComponent::TileID tileID) {
	TileComponent *tile = new TileComponent(tileID, 16);
	addComponentToList(entityID, tile);
}

TileComponent* ComponentManager::getTileComponent(int entityID) {
	TileComponent* tileComp;
	Component *comp = getComponent(entityID, Component::getNameFromEnum(Component::TILE));
	tileComp = dynamic_cast<TileComponent*>(comp);

	if (tileComp != nullptr)
		return tileComp;
	return nullptr;
}
#pragma endregion Texture Components

#pragma region

void ComponentManager::addElevationComponent(int entityID, double elevation) {
	ElevationComponent *elevationComp = new ElevationComponent(elevation);
	addComponentToList(entityID, elevationComp);
}

ElevationComponent* ComponentManager::getElevationComponent(int entityID) {
	ElevationComponent* elevationComp;
	Component *comp = getComponent(entityID, Component::getNameFromEnum(Component::ELEVATION));
	elevationComp = dynamic_cast<ElevationComponent*>(comp);

	if (elevationComp != nullptr)
		return elevationComp;
	return nullptr;
}
#pragma endregion Texture Components

Component* ComponentManager::getComponent(int entityID, std::string readableName)
{
	//get the index of the component in the componats list by getting the entities start index
	//and adding the offset value stored in the related list of the component type.
	//Eg. We are looking for a position component which is stored in index 32. entitiesLookup_ 
	//gives 24 so the components start at index 24 of the components list. componantsLookupList_ 
	//gives us 8 so its offset by 8. 24 + 8 = 32 which is the correct index.
	int index = entitiesLookup_[entityID] + componantsLookupList_[readableName][entityID];

	Component *comp = components_[index];

	if (comp != nullptr)
		return comp;
	return nullptr;
}

void ComponentManager::addComponentToList(int entityID, Component *component)
{
	std::string componantReadableName = component->readableName;
	std::vector<int> *list = &componantsLookupList_[componantReadableName];
	int *listCount = &componantsLookupListCount_[componantReadableName];

	int offset = 0;
	components_.push_back(component);
	offset = componentsCount_++;
	offset -= entitiesLookup_[entityID];

	if (list->size() <= entityID)
	{
		int oldEndIndex = list->size();
		list->resize(list->size() + 100);
		for (int i = oldEndIndex; i < oldEndIndex + 100; i++)
			(*list)[i] = -1;
	}

	(*list)[entityID] = offset;
	(*listCount)++;
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

int ComponentManager::createNewTileEntity(TileComponent::TileID tileID, int x, int y, double elevation)
{
	int entityID = createNewEntity();
	SDL_Texture *tex = textureManager.GetTexture("tilesheet");
	addPositionComponent(entityID, x, y);
	addTextureComponent(entityID, tex);
	addTileComponent(entityID, tileID);
	addElevationComponent(entityID, elevation);
	return entityID;
}

int ComponentManager::createNewPlayerEntity(SDL_Texture *tex, int x, int y)
{
	int entityID = createNewEntity();

	addPositionComponent(entityID, x, y);
	addTextureComponent(entityID, tex);
	addVelocityComponent(entityID, 0, 0);;
	return entityID;
}

void ComponentManager::addTexture(SDL_Texture *tex, std::string name)
{
	if (tex != nullptr)
		textures[name] = tex;
}
#pragma region
void ComponentManager::dataDump()
{

	std::cout << "Entity Lookup Table" << std::endl;
	for (int i = 0; i < entitiesLookupCount_; i++)
	{
		if (entitiesLookup_[i] >= 0)
			std::cout << "Entity: " << i << " start index: " << entitiesLookup_[i] << std::endl;
	}
	std::cout << std::endl;
	typedef std::map<std::string, std::vector<int>>::iterator it_type;
	for (it_type iterator = componantsLookupList_.begin(); iterator != componantsLookupList_.end(); iterator++) {
		std::string key = iterator->first;
		std::vector<int> lookupTable = iterator->second;
		int lookupTableCount = componantsLookupListCount_[key];

		std::cout << key.c_str() << " Lookup Table" << std::endl;
		for (int i = 1; i <= lookupTableCount; i++)
		if (lookupTable[i] >= 0)
			std::cout << "Entity: " << i << " offset: " << lookupTable[i] << std::endl;
		std::cout << std::endl;
	}
	std::cout << std::endl << "Components Table" << std::endl;
	for (int i = 0; i < componentsCount_; i++)
	{
		std::cout << "Component: " << components_[i]->readableName.c_str() << std::endl;
	}
#pragma endregion Data Dump
}

