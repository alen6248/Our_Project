#pragma once


//這裡用ifndef會有錯誤  找不出原因@@

#include <iostream>
#include <vector>
#include <cassert>
#include "SDL.h"
#include "SDL_image.h"
#include "LTexture.h"



using namespace std;


extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
//extern SDL_Renderer* MapRenderer;
//extern SDL_Renderer* MapRenderer;
//Screen dimension constants
extern const int SCREEN_WIDTH ;
extern const int SCREEN_HEIGHT ;
extern const int TILE_WIDTH ;
extern const int WIDTH_TILE_NUMBER ;
extern const int HEIGHT_TILE_NUMBER ;

const int TOWER_IMAGE_WIDTH = 160;
const int TOWER_IMAGE_HEIGHT = 40;
//const string MAP_IMAGE_PATH = "F:\\Project_resourses\\map\\map_image.png";
const string MAP_IMAGE_PATH = "..\\Project_resourses\\map\\map_image.png";

class Map {
public:
	Map(int map_x, int map_y); //constructor
	~Map(); //destructor

	//Image
	void  load_map_texture(string map_path);  //Load map to map_image
	void render();
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

Map::Map(const int map_x,const int map_y) :
	sizeX(map_x), sizeY(map_y)
{
	map_texture = new LTexture;
	load_map_texture(MAP_IMAGE_PATH);
	//map_texture->render(0, 0, NULL);

}
Map::~Map() //free other member
{
	free_map_image();
}
void Map::render() {
	map_texture->render(0, 0, NULL);	
}

void Map::load_map_texture(string _map_path)
{
	map_image_path = _map_path;
	map_texture->loadFromFile(map_image_path);
	//map_texture->setBlendMode(SDL_BLENDMODE_BLEND);
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


