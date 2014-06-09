#include "Region.h"

const int Region::regionSize = 8;

Region::Region() : region_x(-1), region_y(-1)
{
}

Region::Region(int x, int y) : region_x(x), region_y(y)
{

}

Region::~Region()
{
}

void Region::add_entity_to_region(int entityID){
	for (size_t i = 0; i < entitiesInRegion.size(); i++)
	{
		if (entitiesInRegion[i] = -1)
		{
			entitiesInRegion[i] = entityID;
			return;
		}
	}
	entitiesInRegion.push_back(entityID);
}

void Region::remove_entity_from_region(int entityID){
	for (size_t i = 0; i < entitiesInRegion.size(); i++){
		if (entitiesInRegion[i] = entityID)
			entitiesInRegion[i] = -1;
	}
}

bool Region::region_contains_entity(int entityID){
	for (size_t i = 0; i < entitiesInRegion.size(); i++)
		{
			if (entitiesInRegion[i] = entityID)
			return true;
		}
		return false;
}
bool Region::is_inside_region(int x, int y)
{
	if (x >= region_x && x <= region_x + regionSize)
	{
		if (y >= region_y && x <= region_y + regionSize)
		{
			return true;
		}
	}
	return false;
}
int Region::get_x()
{
	return region_x;
}
int Region::get_y(){
	return region_y;
}