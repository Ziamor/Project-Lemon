#pragma once
#include <vector>
class Region
{
public:
	Region();
	Region(int x, int y);
	~Region();
	static const int regionSize;
	void Region::add_entity_to_region(int entityID);
	void Region::remove_entity_from_region(int entityID);
	bool Region::region_contains_entity(int entityID);
	bool Region::is_inside_region(int x, int y);
	int Region::get_x();
	int Region::get_y();
private:
	std::vector<int> entitiesInRegion;
	int region_x, region_y;
};

