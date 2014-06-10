#pragma once
#include <vector>
#include <map>
#include "Component.h"
class Region
{
public:
	Region();
	Region(int x, int y);
	~Region();
	static const int regionSize;
	void Region::add_entity_to_region(int entityID);
	void Region::add_component_to_region(int entityID, Component *component);
	void Region::remove_entity_from_region(int entityID);
	bool Region::region_contains_entity(int entityID);
	bool Region::is_inside_region(int x, int y);
	int Region::get_x();
	int Region::get_y();
	int Region::get_entity_index(int entityID);
	int Region::get_component_index(int entityID, std::string readableName);
	std::vector<int> Region::getEntityListOfComponents(std::string readableName);
	std::vector<Component*> components_;
	std::map<std::string, std::vector<int>> componantsLookupList_;
	std::vector<int> entitiesStartIndexLookup_;
	std::vector<int> entitiesIDLookup_;
	void dataDump();
private:
	int region_x, region_y;
};

