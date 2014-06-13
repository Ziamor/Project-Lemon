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
	int startIndex = components_.size();
	//Check for an empty spot in array
	for (size_t i = 0; i < entitiesIDLookup_.size(); i++)
	{
		//if an empty spot was found
		if (entitiesIDLookup_[i] == -1)
		{
			entitiesIDLookup_[i] = entityID;
			entitiesStartIndexLookup_[i] = startIndex;
			return;
		}
	}
	entitiesIDLookup_.push_back(entityID);
	entitiesStartIndexLookup_.push_back(startIndex);
}

void Region::add_component_to_region(int entityID, Component *component)
{
	//Get the components types readable name to identify which list to us.
	std::string componantReadableName = component->readableName;
	std::vector<int> *list = &componantsLookupList_[componantReadableName];

	//calculate the offset by getting the total component count and subtracting
	//the start index of the entity from entitiesLookup_
	int entityIndex = get_entity_index(entityID);

	if (entityIndex == -1) //No entity with that id found
		return;
	int offset = 0;
	components_.push_back(component);
	offset = components_.size() - 1;
	offset -= entitiesStartIndexLookup_[entityIndex];
	//set the correct coresponding component list to equal the offset
	(*list).push_back(offset);
}

void Region::remove_entity_from_region(int entityID){
	for (size_t i = 0; i < entitiesIDLookup_.size(); i++){
		if (entitiesIDLookup_[i] == entityID)
			entitiesIDLookup_[i] = -1;
	}
}

bool Region::region_contains_entity(int entityID){
	for (size_t i = 0; i < entitiesIDLookup_.size(); i++)
	{
		if (entitiesIDLookup_[i] == entityID)
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

int Region::get_entity_index(int entityID)
{
	int entityIndex = -1;
	//get the index where the entities are stored
	for (size_t i = 0; i < entitiesIDLookup_.size(); i++)
	{
		if (entitiesIDLookup_[i] == entityID)
		{
			entityIndex = i;
			return entityIndex;
		}
	}
	return entityIndex;
}

int Region::get_component_index(int entityID, std::string readableName)
{
	//get the index of the component in the components list by getting the entities start index
	//and adding the offset value stored in the related list of the component type.
	//Eg. We are looking for a position component which is stored in index 32. entitiesLookup_ 
	//gives 24 so the components start at index 24 of the components list. componantsLookupList_ 
	//gives us 8 so its offset by 8. 24 + 8 = 32 which is the correct index.

	//the start index of the entity from entitiesLookup_
	int entityIndex = get_entity_index(entityID);
	int index = entitiesStartIndexLookup_[entityIndex] + componantsLookupList_[readableName][entityIndex];

	return index;
}

//Returns a list of entity IDs that contain the component type
std::vector<int> Region::getEntityListOfComponents(std::string readableName)
{
	std::vector<int> entitiesIdWithComp;
	std::vector<int> *list;
	//Check if the list for that component type exists. If not that means no components of that type exist yet
	//so return an empty list.
	if (componantsLookupList_.find(readableName) == componantsLookupList_.end())
		return entitiesIdWithComp;
	else
		list = &componantsLookupList_[readableName];
	//Loop through all entities. If the entity has a valid value(not -1) then add the id to the list
	for (size_t i = 0; i < list->size(); i++)
	{
		if ((*list)[i] >= 0)
		{
			int entityID = entitiesIDLookup_[i];
			entitiesIdWithComp.push_back(entityID);
		}
	}
	return entitiesIdWithComp;
}

void Region::dataDump()
{
	using namespace std;
	cout << "EntID:" << endl;
	for (int i = 0; i < entitiesIDLookup_.size(); i++)
	{
		cout << i << "\t" << entitiesIDLookup_[i] << endl;
	}
	cout << endl;

	cout << "EntStart:" << endl;
	for (int i = 0; i < entitiesStartIndexLookup_.size(); i++)
	{
		cout << i << "\t" << entitiesStartIndexLookup_[i] << endl;
	}
	cout << endl;

	cout << "Components:" << endl;
	for (int i = 0; i < components_.size(); i++)
	{
		cout << i << "\t" << components_[i]->readableName.c_str() << endl;
	}
	cout << endl;

	typedef std::map<std::string, std::vector<int>>::iterator it_type;
	for (it_type iterator = componantsLookupList_.begin(); iterator != componantsLookupList_.end(); iterator++) {
		std::string key = iterator->first;
		std::vector<int> lookupTable = iterator->second;
		int lookupTableCount = componantsLookupList_[key].size();
		
			std::cout << key.c_str() << " Lookup Table" << std::endl;
		for (int i = 0; i < lookupTableCount; i++)
			 if (lookupTable[i] >= 0)
			 std::cout << "Entity: " << i << "\t offset: " << lookupTable[i] << std::endl;
		std::cout << std::endl;
	}
	cout << endl;
}