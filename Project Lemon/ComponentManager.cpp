#include "ComponentManager.h"

ComponentManager::ComponentManager() :nextEntityID_(0)
{
}


ComponentManager::~ComponentManager()
{
}
#pragma region

void ComponentManager::addPositionComponent(int entityID, int x, int y, Region &region) {
	PositionComponent *position = new PositionComponent(x, y);
	region.add_component_to_region(entityID, position);
}

PositionComponent* ComponentManager::getPositionComponent(int entityID, Region &region) {
	PositionComponent* postionComponent;
	Component *comp = getComponent(entityID, Component::getNameFromEnum(Component::POSITION), region);
	postionComponent = dynamic_cast<PositionComponent*>(comp);
	
	return postionComponent;
}

#pragma endregion Position Components

#pragma region

void ComponentManager::addVelocityComponent(int entityID, int dx, int dy, Region &region) {
	VelocityComponent *velocity = new VelocityComponent(dx, dy);
	region.add_component_to_region(entityID, velocity);
}

VelocityComponent* ComponentManager::getVelocityComponent(int entityID, Region &region) {
	VelocityComponent* velocityComponent;
	Component *comp = getComponent(entityID, Component::getNameFromEnum(Component::VELOCITY), region);
	velocityComponent = dynamic_cast<VelocityComponent*>(comp);

	return velocityComponent;
}

#pragma endregion Velocity Components

#pragma region

void ComponentManager::addTextureComponent(int entityID, SDL_Texture *tex, Region &region) {
	TextureComponent *texture = new TextureComponent(tex);
	region.add_component_to_region(entityID, texture);
}

TextureComponent* ComponentManager::getTextureComponent(int entityID, Region &region) {
	TextureComponent* texComp;
	Component *comp = getComponent(entityID, Component::getNameFromEnum(Component::TEXTURE), region);
	texComp = dynamic_cast<TextureComponent*>(comp);

	return texComp;
}
#pragma endregion Texture Components

#pragma region

void ComponentManager::addTileComponent(int entityID, TileComponent::TileID tileID, Region &region) {
	TileComponent *tile = new TileComponent(tileID, 16);
	region.add_component_to_region(entityID, tile);
}

TileComponent* ComponentManager::getTileComponent(int entityID, Region &region) {
	TileComponent* tileComp;
	Component *comp = getComponent(entityID, Component::getNameFromEnum(Component::TILE), region);
	tileComp = dynamic_cast<TileComponent*>(comp);

	return tileComp;
}
#pragma endregion Tile Components

#pragma region

void ComponentManager::addElevationComponent(int entityID, double elevation, Region &region) {
	ElevationComponent *elevationComp = new ElevationComponent(elevation);
	region.add_component_to_region(entityID, elevationComp);
}

ElevationComponent* ComponentManager::getElevationComponent(int entityID, Region &region) {
	ElevationComponent* elevationComp;
	Component *comp = getComponent(entityID, Component::getNameFromEnum(Component::ELEVATION), region);
	elevationComp = dynamic_cast<ElevationComponent*>(comp);

	return elevationComp;
}
#pragma endregion Elevation Components

Component* ComponentManager::getComponent(int entityID, std::string readableName, Region &region)
{
	int index = region.get_component_index(entityID, readableName);

	Component *comp = region.components_[index];
	return comp;
}

int ComponentManager::createNewEntity(Region &region)
{
	//Get the nex entity ID
	int entityID = nextEntityID_++;
	region.add_entity_to_region(entityID);

	return entityID;
}

int ComponentManager::createNewTileEntity(TileComponent::TileID tileID, int x, int y, double elevation, Region &region)
{
	int entityID = createNewEntity(region);
	textureManager = TextureManager();
	SDL_Texture *tex = textureManager.GetTexture("tilesheet");
	addPositionComponent(entityID, x, y, region);
	addTextureComponent(entityID, tex, region);
	addTileComponent(entityID, tileID, region);
	addElevationComponent(entityID, elevation, region);
	return entityID;
}

int ComponentManager::createNewPlayerEntity(SDL_Texture *tex, int x, int y, Region &region)
{
	int entityID = createNewEntity(region);

	addPositionComponent(entityID, x, y, region);
	addTextureComponent(entityID, tex, region);
	addVelocityComponent(entityID, 0, 0, region);;
	return entityID;
}

void ComponentManager::addTexture(SDL_Texture *tex, std::string name)
{
	if (tex != nullptr)
		textures[name] = tex;
}

