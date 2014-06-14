#include "MapManager.h"

int MapManager::view_x = 0;
int MapManager::view_y = 0;
std::vector<Region*> MapManager::active_regions;

int MapManager::get_view_x()
{
	return view_x;
}

int MapManager::get_view_y()
{
	return view_y;
}

MapManager::MapManager()
{
	map_seed = 852527;
	num_regions_view_x = Game::SCREEN_WIDTH / TileComponent::tileSize;
	num_regions_view_x = ceil(num_regions_view_x / Region::regionSize);
	num_regions_view_y = Game::SCREEN_HEIGHT / TileComponent::tileSize;
	num_regions_view_y = ceil(num_regions_view_y / Region::regionSize);

	view_changed();
}


MapManager::~MapManager()
{
}
//Move the camera view around the screen
void MapManager::onNotify(const int entityID, Observer::event_type event)
{
	if (event == System::event_type::KEY_UP)
	{
		std::cout << "Key_up" << std::endl;
		view_y--;
	}
	else if (event == System::event_type::KEY_DOWN)
	{
		std::cout << "Key_down" << std::endl;
		view_y++;
	}
	else if (event == System::event_type::KEY_LEFT)
	{
		std::cout << "Key_left" << std::endl;
		view_x--;
	}
	else if (event == System::event_type::KEY_RIGHT)
	{
		std::cout << "Key_right" << std::endl;
		view_x++;
	}
	view_changed();
}
//Returns the coordinate of the region that the world coordinate resides in.
//eg. If the world cord of world_x = 9 and region size is 8 then world_x resides 
//inside of region_x = 1;
int MapManager::world_coord_to_region_coord(double n)
{
	double coord = n / Region::regionSize;
	coord = floor(coord);
	return coord;
}
//returns the region that the x and y cord respond to
Region* MapManager::get_region(int x, int y)
{
	for (size_t i = 0; i < regions.size(); i++)
	{
		if (regions[i]->get_x() == x && regions[i]->get_y() == y)
		{
			return regions[i]; // Region already loaded
		}
	}

	//No region found load region
	Region *region = new Region(x, y);
	load_region_components(*region);
	regions.push_back(region);
	return region;
}

//returns the region that the world x and y cord exist in
Region* MapManager::get_region_with_world_cord(int x_world, int y_world)
{
	//convert to region cord. 
	//eg. Region size is 8, world(19,53) = region(2,6)
	int x = world_coord_to_region_coord(x_world);
	int y = world_coord_to_region_coord(y_world);

	return get_region(x, y);
}
//Loads the region into memory
void MapManager::load_region_components(Region &region)
{
	int region_total_tiles = Region::regionSize*Region::regionSize;
	PerlinNoise perlinNoise = PerlinNoise(map_seed, 0.75, 6);
	for (int i = 0; i < region_total_tiles; i++)
	{
		int local_x = i % Region::regionSize; // get the local x and y cord of the region
		int local_y = i / Region::regionSize;
		int x = local_x + Region::regionSize*region.get_x(); // translate the local x and y cords to world cord
		int y = local_y + Region::regionSize*region.get_y();

		double elevation = perlinNoise.getPerlinNoise(x, y, 25); // get the elevation data for the x and y cord
		int entityID = -1;
		if (elevation >= 0)
			entityID = Game::componentManager.createNewTileEntity(TileComponent::GRASS, x * TileComponent::tileSize, y * TileComponent::tileSize, elevation, region);
		else if (elevation < 0)
			entityID = Game::componentManager.createNewTileEntity(TileComponent::WATER, x * TileComponent::tileSize, y * TileComponent::tileSize, elevation , region);
	}
}

// Get all visable regions
void MapManager::view_changed()
{
	int first_region_x = world_coord_to_region_coord(view_x);
	int first_region_y = world_coord_to_region_coord(view_y);
	std::cout << std::endl;
	std::cout << first_region_x << " " << first_region_y << std::endl;
	active_regions = std::vector<Region*>();
	//we start at -1 and end the loop at view size + 1 so that we have one tile preloaded around the border of the view screen
	for (int x = -1; x < num_regions_view_x + 1; x++)
	{
		for (int y = -1; y < num_regions_view_y + 1; y++)
		{
			active_regions.push_back(get_region(x + first_region_x, y + first_region_y));
		}
	}
}