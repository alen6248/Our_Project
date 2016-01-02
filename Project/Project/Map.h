#pragma once


//==========================設計===================================


//=================================================================




/**************************問題***********************************/
//使用tile?

/*****************************************************************/

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include "LTexture.h"
#include <fstream>
#include <iomanip>
#include "Tower.h"
#define DEBUG 
using namespace std;

extern SDL_Surface* gScreenSurface;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

extern const int SCREEN_WIDTH ;
extern const int SCREEN_HEIGHT ;
extern const int TILE_WIDTH ;
extern const int WIDTH_TILE_NUMBER ;
extern const int HEIGHT_TILE_NUMBER ;

const int TOWER_IMAGE_WIDTH = 160;
const int TOWER_IMAGE_HEIGHT = 40;


class Map {
public:
	Map(int map_x, int map_y,string map_img_path,string input_tiles_file_path);
	~Map();
	void draw(SDL_Window* gWindow, SDL_Surface* gScreenSurface); 
	bool  loadImageFile();  //Load map to game.
	//void  setTile(int type, int x, int y); 
	void free_map_image();
	//vector< int >  getEnvironment(int position); //Get tile - type in all four direction.
	//bool  mouseOver(int x, int y);  //Check if mouse is over the map or outside map.
		
	//static std::string  getImage(int type);

	//set tower function



	//從其他檔案輸進Tiles資料
	void loadTiles();
	void load_tower_image(int level,int tower_order);
	string tiles_file_path;
	string  mapImage_Loaded;  //map檔案名
	//int  mousePosition;
	int  sizeX;  //畫面size
	int  sizeY;	
	SDL_Surface* map_image;
	//int  startPoint; //??
	//int  endPoint; //??
	//int  squareSize;
	//vector< SDL_Texture * >  tower_stage; //可放置塔,按鈕，按下跳出選單
									//放置敵人路徑?
	struct unit_Tile {
		int width_tile_location;
		int height_tile_location;
		enum TowerType{_map,None_Tower,FireTower,IceTower,PoisonTower} tower_type;
		//int tower_level;
		//LTexture* tile_texture;
		Tower* tower; //used by virtual function
	};
	vector<unit_Tile*> tile_tower_list;

	//SDL_Surface *  imageStartPoint;  
	//SDL_Surface *  imageEndPoint;
};



Map::Map(const int map_x,const int map_y, string map_img_path, string input_tiles_file_path) :sizeX(map_x), sizeY(map_y), mapImage_Loaded(map_img_path), tiles_file_path(input_tiles_file_path)
{
	//字串錯誤
	//"F:\\Project_resourses\\map\\hello_world.bmp";
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
		//Render texture to screen
		SDL_RenderCopy(gRenderer, tile_tower_list[i]->tower->get_tower_texture_ptr(), NULL, NULL);
	}
	//Update screen
	SDL_RenderPresent(gRenderer);


	//Update the surface
	SDL_UpdateWindowSurface(gWindow);

}

bool Map::loadImageFile() //need to optimize image
{
#ifdef DEBUD
	cout << "Enter loadImageFile function" << endl;
#endif
	//The final optimized image
	//SDL_Surface* optimizedSurface = NULL;


	//Loading success flag
	bool success = true;

	//Load splash image
	map_image = IMG_Load(mapImage_Loaded.c_str());

	if (map_image == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", mapImage_Loaded.c_str(), SDL_GetError());
		success = false;
	}
	/*
	else {
	//Convert surface to screen format
	optimizedSurface = SDL_ConvertSurface(map_image, gScreenSurface->format, NULL);
	if (optimizedSurface == NULL)
	{
	printf("Unable to optimize image %s! SDL Error: %s\n", mapImage_Loaded.c_str(), SDL_GetError());
	success = false;
	}
	else {
	//Get rid of old loaded surface
	SDL_FreeSurface(map_image);
	map_image = optimizedSurface;
	}
	}
	*/
	return success;
}  

void Map::free_map_image()
{
	if (map_image != NULL) {
		SDL_FreeSurface(gScreenSurface);
	}
	gScreenSurface = NULL;
}


/*****load_tower_texture function is declared in class Tower*/
////modifying
//void Map::load_tower_image(int level,int tile_order ) {   //level argument needed
//	//for (int i = 0; i < WIDTH_TILE_NUMBER*HEIGHT_TILE_NUMBER; i++) {
//		tiles[tile_order]->tile_texture = new LTexture;
//		if (tiles[tile_order]->tower_type>1) {
//			switch (tiles[tile_order]->tower_type) {
//			case Map::unit_Tile::TowerType::FireTower:
//				tiles[tile_order]->tile_texture->load_tower("F:\\Project_resourses\\tower\\fire_tower.png", tiles[tile_order]->width_tile_location, tiles[tile_order]->height_tile_location,
//					LTexture::clip_list[level], SDL_BLENDMODE_BLEND, 255/*non_transparant*/);
//				break;
//			case Map::unit_Tile::TowerType::IceTower:
//				tiles[tile_order]->tile_texture->load_tower("F:\\Project_resourses\\tower\\ice_tower.png", tiles[tile_order]->width_tile_location, tiles[tile_order]->height_tile_location,
//					LTexture::clip_list[level], SDL_BLENDMODE_BLEND, 255/*non_transparant*/);
//				break;
//			case Map::unit_Tile::TowerType::PoisonTower:
//				tiles[tile_order]->tile_texture->load_tower("F:\\Project_resourses\\tower\\poison_tower.png", tiles[tile_order]->width_tile_location, tiles[tile_order]->height_tile_location,
//					LTexture::clip_list[level], SDL_BLENDMODE_BLEND, 255/*non_transparant*/);
//				break;
//			default: break;
//			}
//		}
//		else {
//			tiles[tile_order]->tile_texture->load_tower("F:\\Project_resourses\\tower\\default_tile.png", tiles[tile_order]->width_tile_location, tiles[tile_order]->height_tile_location,
//				NULL, SDL_BLENDMODE_BLEND, 0/*透明*/);
//		}
//	//}//endl of for
//}
void Map::loadTiles(){
	fstream tiles_file;
	tiles_file.open(tiles_file_path.c_str(), ios::in);

#if 0
	tiles.resize(tiles.size() + 1);
	tiles[0] = new unit_Tile;
	tiles[0]->width_tile_location = unit_Tile::TowerType::None_Tower;
	cout << tiles[0]->width_tile_location;

#endif 


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
					char comma;
				
					int read=NULL;
					tile_tower_list.resize(tile_tower_list.size() + 1);
					tile_tower_list[(i + 1)*(j + 1)-1] = new unit_Tile;
					//tile_tower_list[(i + 1)*(j + 1) - 1]->tower = new Tower(0,j,i);
					tile_tower_list[(i + 1)*(j + 1)-1]->width_tile_location = j;
					tile_tower_list[(i + 1)*(j + 1)-1]->height_tile_location = i;
					tiles_file  >>setw(1)>> read;
					(tile_tower_list[(i + 1)*(j + 1) - 1])->tower_type = (unit_Tile::TowerType)(read );
					tiles_file >> setw(1) >> comma;

					//set tiles[n]->tile_level
					//tile_tower_list[(i + 1)*(j + 1) - 1]->tower->level = 0; //沒有蓋塔，設為0

					//set Tower Texture mWidth and mHeight
					/*tiles[(i + 1)*(j + 1) - 1]->tower->mWidth = TOWER_IMAGE_WIDTH;
					tiles[(i + 1)*(j + 1) - 1]->tile_texture->mWidth = TOWER_IMAGE_HEIGHT;*/


					
					/*  改成由tile_tower_list使用virtual function 來完成  */
					//load tile image
					//load_tower_image(tiles[(i + 1)*(j + 1) - 1]->tower_level, (i + 1)*(j + 1) - 1);

#ifdef DEBUG
					cout << (tile_tower_list[(i + 1)*(j + 1) - 1])->tower_type << comma;
					num++;
					if (num % 24 == 0) { cout << endl; }
#endif // DEBUG
					


				}
			}
		}
	}
}