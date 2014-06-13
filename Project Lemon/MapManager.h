#pragma once
#include "System.h"
#include "Observer.h"
#include "PerlinNoise.h"
#include <vector>
#include <iostream>
#include "Region.h"
#include <math.h>
#include "Game.h"

class MapManager :
	public Observer
{
public:
	MapManager();
	~MapManager();
	void MapManager::onNotify(int entityID, Observer::event_type event);
	static int MapManager::get_view_x();
	static int MapManager::get_view_y();
	Region* MapManager::get_region(int x_world, int y_world);
	Region* MapManager::get_region_with_world_cord(int x_world, int y_world);
	int MapManager::world_cord_to_region_cord(double n);
	static std::vector<Region*> MapManager::get_active_regions();
	static std::vector<Region*> active_regions;
private:
	static int view_x, view_y;	
	double num_regions_view_x, num_regions_view_y;
	void MapManager::load_region_components(Region &region);
	void MapManager::view_changed();
	std::vector<int> map;
	std::vector<Region*> regions;
	int map_seed;
	int map_width;
	int map_height;
	int map_total_tiles;
};

