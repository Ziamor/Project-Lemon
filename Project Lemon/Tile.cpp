#include "Tile.h"

int TileComponent::tileSize = 16;
int TileComponent::tilesPerRow = 8;
int TileComponent::tilesPerCol = 8;
TileComponent::TileComponent() : Component("tile")
{
}

TileComponent::TileComponent(TileID tileID, int tileSize) : tileID(tileID), Component("tile") {
	srcrect.x = (tileID % tilesPerRow) * tileSize;
	srcrect.y = (tileID / tilesPerRow) * tileSize;
	srcrect.w = tileSize;
	srcrect.h = tileSize;
}

TileComponent::~TileComponent()
{
}