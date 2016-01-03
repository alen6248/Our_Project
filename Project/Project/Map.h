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
#include <cassert>

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
		int width_pixel_location;
		int height_pixel_location;
		enum TowerType { _map, None_Tower, FireTower, IceTower, PoisonTower } tower_type;
		Tower* tower; //used by virtual function
	};

	//Tiles
	void loadTiles(); //load Tiles data from file
	void set_tiles_file_path(string path); 
	const string& get_tiles_file_path() const;
	const vector<unit_Tile*>& get_tile_tower_list()const;

	//Image
	bool  loadImageFile();  //Load map to map_image
	void set_mapImage_Loaded(string path);
	const string& get_mapImage_Loaded() const;
	SDL_Surface* get_map_image() const;

	
	//vector set and get function define later!!
	
	vector<unit_Tile*> tile_tower_list; //container: store tile data
private:
	SDL_Surface* map_image;
	string tiles_file_path;  //tile data file path
	string  mapImage_Loaded;  //map file path

	//map size (pixels)
	int  sizeX;
	int  sizeY;

	
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

	//error!! the other tiles don't render images!!
	//for (int i = 0; i < WIDTH_TILE_NUMBER*HEIGHT_TILE_NUMBER; i++) {
	//	//Render texture to Renderer
	//	SDL_RenderCopy(gRenderer, tile_tower_list[i]->tower->get_tower_texture_ptr()->get_mTexture_ptr(), NULL, NULL);
	//}  

	SDL_RenderCopy(gRenderer, tile_tower_list[260]->tower->get_tower_texture_ptr()->get_mTexture_ptr(), NULL, NULL);

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



	if (!tiles_file) {
		cerr << "can't open file" << endl;
		exit(1);
	}
	else {
		int count_num = 0; //index of vector
		tile_tower_list.resize( HEIGHT_TILE_NUMBER * WIDTH_TILE_NUMBER ); //set the vector size
		for (int i = 1; i <= HEIGHT_TILE_NUMBER; i++) {
			for (int j = 1; j <= WIDTH_TILE_NUMBER; j++) {
#ifdef DEBUG
				assert(!tiles_file.eof());
#endif // DEBUG
					//unit_Tile loading_tile;
					char comma;  //used to read comma
					int read=NULL; //used to read TowerType
					tile_tower_list[count_num] = new unit_Tile;
					tile_tower_list[count_num]->width_tile_location = j-1; //set width_tile_location
					tile_tower_list[count_num]->height_tile_location = i-1; //set height_tile_location
					tiles_file  >>setw(1)>> read;
					(tile_tower_list[count_num])->tower_type = (unit_Tile::TowerType)(read );//assign read value
					tiles_file >> setw(1) >> comma;
					tile_tower_list[count_num]->width_pixel_location = (tile_tower_list[count_num]->width_tile_location)*TILE_WIDTH;
					tile_tower_list[count_num]->height_pixel_location = (tile_tower_list[count_num]->height_tile_location)*TILE_WIDTH;
#ifdef DEBUG
					cout << (tile_tower_list[count_num])->tower_type << comma;
#endif // DEBUG
					count_num++;
#ifdef DEBUG		
					if (count_num % WIDTH_TILE_NUMBER == 0) { cout << endl; }
#endif // DEBUG
			}//end of for of j
		}//end of for of i
	}//end of else
}//end of loadTile
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

const vector<Map::unit_Tile*>& Map::get_tile_tower_list()const {
	return tile_tower_list;
}