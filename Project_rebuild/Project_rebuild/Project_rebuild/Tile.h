//#pragma once

#ifndef _TILE_H
#define _TILE_H
#include "LButton.h"

extern const int TILE_WIDTH ;

class Tile {
public:
	Tile(string path, int x_tile_location, int y_tile_location); //constructor
	~Tile(); //destructor
	LTexture* get_tile_texture();
	void load_tile_texture();
	void render();

	struct unit_Tile {
		//int tower_level;
		int width_tile_location;
		int height_tile_location;
		int width_pixel_location;
		int height_pixel_location;
		int tile_width;
	
		LButton* button;

		//enum TowerType { _map, None_Tower, FireTower, IceTower, PoisonTower } tower_type;
		//Tower* tower; //used by virtual function
	};
	

private:
	unit_Tile unit_tile;
	LTexture* tile_texture;
	string tile_image_path;

	//vector<unit_Tile*> tile_tower_list; //container: store tile data

};
Tile::Tile(string path,int x_tile_location,int y_tile_location): tile_image_path(path)
{
	unit_tile.width_tile_location = x_tile_location;
	unit_tile.height_tile_location = y_tile_location;
	unit_tile.width_pixel_location = unit_tile.width_tile_location*TILE_WIDTH;
	unit_tile.height_pixel_location = unit_tile.height_tile_location*TILE_WIDTH;

	unit_tile.button = new LButton;
	tile_texture = new LTexture;
	load_tile_texture();

}
Tile::~Tile() {

}
void Tile::load_tile_texture() {
	tile_texture->loadFromFile(tile_image_path.c_str());
}
void Tile::render() {
	tile_texture->render(unit_tile.width_pixel_location, unit_tile.height_pixel_location, NULL);
}
LTexture* Tile::get_tile_texture() {
	return tile_texture;
}





#endif // !_TILE_H
