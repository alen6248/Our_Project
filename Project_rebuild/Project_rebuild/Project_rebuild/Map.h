//#pragma once
#ifndef _MAP_H
#define _MAP_H

#include <iostream>
#include <vector>
//#include <stdio.h>  //exit() 
//#include <fstream> //read files
//#include <iomanip> //setw()
#include <cassert>

#include "SDL.h"
#include "SDL_image.h"
#include "LTexture.h"



using namespace std;

//extern SDL_Surface* gScreenSurface;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

//Screen dimension constants
extern const int SCREEN_WIDTH ;
extern const int SCREEN_HEIGHT ;
extern const int TILE_WIDTH ;
extern const int WIDTH_TILE_NUMBER ;
extern const int HEIGHT_TILE_NUMBER ;

const int TOWER_IMAGE_WIDTH = 160;
const int TOWER_IMAGE_HEIGHT = 40;


class Map {
public:
	Map(int map_x, int map_y,string map_img_path); //constructor
	~Map(); //destructor

	//Image
	void  load_map_texture();  //Load map to map_image
	void render_map_texture();
	void set_map_image_path(string path);
	const string& get_mapImage_Loaded() const;
	LTexture* get_map_texture() const;
	void free_map_image(); //delocate map_image

private:
	LTexture* map_texture;
	string  map_image_path;  //map file path

	//map size (pixels)
	int  sizeX;
	int  sizeY;

	
};

Map::Map(const int map_x,const int map_y, string map_img_path) :
	sizeX(map_x), sizeY(map_y), map_image_path(map_img_path)
{
	map_texture = new LTexture;
	load_map_texture();
	//map_texture->render(0, 0, NULL);

}
Map::~Map() //free other member
{
	free_map_image();
}
void Map::render_map_texture() {
	map_texture->render(0, 0, NULL);	
}

void Map::load_map_texture()
{
	map_texture->loadFromFile(map_image_path);
	map_texture->setBlendMode(SDL_BLENDMODE_BLEND);
	map_texture->setAlpha(255); //Alpha number??
}  
void Map::free_map_image()
{
	if (map_texture != NULL) {
		SDL_FreeSurface(gScreenSurface);
	}
	gScreenSurface = NULL;
}

void Map::set_map_image_path(string path) {
	map_image_path = path;
}
const string& Map::get_mapImage_Loaded() const {
	return map_image_path;
}
LTexture* Map::get_map_texture() const {
	return map_texture;
}


#endif // !_MAP_H