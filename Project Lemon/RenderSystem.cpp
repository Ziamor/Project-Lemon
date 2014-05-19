#include "RenderSystem.h"
#include "Position.h"
#include "Texture.h"

RenderSystem::RenderSystem()
{

}


RenderSystem::~RenderSystem()
{
}

bool RenderSystem::execute(){
	std::vector<int> list = Game::componentManager.getEntityListOfPositionComponents();
	for (int i = 0; i < list.size(); i++)
	{
		PositionComponent *positionComp = Game::componentManager.getPositionComponent(list[i]);
		TextureComponent *textureComp = Game::componentManager.getTextureComponent(list[i]);
		if (positionComp != nullptr && textureComp != nullptr)
			std::cout << "Draw";
	}
	return true;
}