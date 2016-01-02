#pragma once


//==========================設計===================================


//=================================================================




/**************************問題***********************************/
//使用tile?

/*****************************************************************/


#include <iostream>
#include <vector>
#include <stdio.h>  //exit() 
#include <fstream> //read files
#include <iomanip> //setw()

#include "SDL.h"
#include "SDL_image.h"
#include "Tower.h"
#include "LTexture.h"

#define DEBUG 

using namespace std;

extern SDL_Surface* gScreenSurface;
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
	Map(int map_x, int map_y,string map_img_path,string input_tiles_file_path); //constructor
	~Map(); //destructor
	void draw(SDL_Window* gWindow, SDL_Surface* gScreenSurface);  //Build surface and render texture to screen
	void free_map_image(); //delocate map_image
	
	//struct: unit_Tile definition
	struct unit_Tile {
		//int tower_level;
		int width_tile_location;
		int height_tile_location;
		enum TowerType { _map, None_Tower, FireTower, IceTower, PoisonTower } tower_type;
		Tower* tower; //used by virtual function
	};

	//Tiles
	void loadTiles(); //load Tiles data from file
	void set_tiles_file_path(string path); 
	const string& get_tiles_file_path() const;
	vector<unit_Tile*> get_tile_tower_list()const;

	//Image
	bool  loadImageFile();  //Load map to map_image
	void set_mapImage_Loaded(string path);
	const string& get_mapImage_Loaded() const;
	SDL_Surface* get_map_image() const;

		
	

	//vector set and get function define later!!
	

private:
	SDL_Surface* map_image;
	string tiles_file_path;  //tile data file path
	string  mapImage_Loaded;  //map file path

	//map size (pixels)
	int  sizeX;
	int  sizeY;

	vector<unit_Tile*> tile_tower_list; //container: store tile data
};



Map::Map(const int map_x,const int map_y, string map_img_path, string input_tiles_file_path) :
	sizeX(map_x), sizeY(map_y), mapImage_Loaded(map_img_path), tiles_file_path(input_tiles_file_path)
{
	loadImageFile();
	LTexture::set_tower_image_clip(); //set static member
	loadTiles();
}

Map::~Map() //free other member
{
	free_map_image();
}

void Map::draw(SDL_Window* gWindow, SDL_Surface * gScreenSurface)
{
	//Apply the image
	SDL_BlitSurface(map_image, NULL, gScreenSurface, NULL);

	//Clear screen
	SDL_RenderClear(gRenderer);

	for (int i = 0; i < WIDTH_TILE_NUMBER*HEIGHT_TILE_NUMBER; i++) {
		//Render texture to Renderer
		SDL_RenderCopy(gRenderer, tile_tower_list[i]->tower->get_tower_texture_ptr(), NULL, NULL);
	}
	//Update screen
	SDL_RenderPresent(gRenderer);

	//Update the surface
	SDL_UpdateWindowSurface(gWindow);

}

bool Map::loadImageFile() 
{
#ifdef DEBUD
	cout << "Enter loadImageFile function" << endl;
#endif
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Loading success flag
	bool success = true;

	//Load splash image
	map_image = IMG_Load(mapImage_Loaded.c_str());
	
	if (map_image == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", mapImage_Loaded.c_str(), SDL_GetError());
		success = false;
	}
	else {
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(map_image, gScreenSurface->format, NULL);
		if (optimizedSurface == NULL){
			printf("Unable to optimize image %s! SDL Error: %s\n", mapImage_Loaded.c_str(), SDL_GetError());
			success = false;
		}
		else {
			//Get rid of old loaded surface
			SDL_FreeSurface(map_image);
			map_image = optimizedSurface;
		}
	}
	
	return success;
}  

void Map::free_map_image()
{
	if (map_image != NULL) {
		SDL_FreeSurface(gScreenSurface);
	}
	gScreenSurface = NULL;
}

void Map::loadTiles(){

	fstream tiles_file; //tiles_file to read
	tiles_file.open(tiles_file_path.c_str(), ios::in); //open file, read only

#ifdef DEBUG
	int num = 0;
	cout << endl;
#endif // DEBUG

	if (!tiles_file) {
		cerr << "can't open file" << endl;
		exit(1);
	}
	else {
		for (int i = 0; i < HEIGHT_TILE_NUMBER; i++) {
			for (int j = 0; j < WIDTH_TILE_NUMBER; j++) {
				while (!tiles_file.eof()) {
					//unit_Tile loading_tile;
					char comma;  //used to read comma
					int read=NULL; //used to read TowerType
					tile_tower_list.resize(tile_tower_list.size() + 1); //vector size++
					tile_tower_list[(i + 1)*(j + 1)-1] = new unit_Tile;
					tile_tower_list[(i + 1)*(j + 1)-1]->width_tile_location = j; //set width_tile_location
					tile_tower_list[(i + 1)*(j + 1)-1]->height_tile_location = i; //set height_tile_location
					tiles_file  >>setw(1)>> read;
					(tile_tower_list[(i + 1)*(j + 1) - 1])->tower_type = (unit_Tile::TowerType)(read );//assign read value
					tiles_file >> setw(1) >> comma;
#ifdef DEBUG
					cout << (tile_tower_list[(i + 1)*(j + 1) - 1])->tower_type << comma;
					num++;
					if (num % WIDTH_TILE_NUMBER == 0) { cout << endl; }
#endif // DEBUG
				}
			}
		}
	}
}
void Map::set_tiles_file_path(string path) {
	tiles_file_path = path;
}

const string& Map::get_tiles_file_path() const {
	return tiles_file_path;
}

void Map::set_mapImage_Loaded(string path) {
	mapImage_Loaded = path;
}

const string& Map::get_mapImage_Loaded() const {
	return mapImage_Loaded;
}

SDL_Surface* Map::get_map_image() const {
	return map_image;
}

vector<Map::unit_Tile*> Map::get_tile_tower_list()const {
	return tile_tower_list;
}