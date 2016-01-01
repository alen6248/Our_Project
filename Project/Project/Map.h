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
#define DEBUG 
using namespace std;

extern SDL_Surface* gScreenSurface;
extern SDL_Window* gWindow;

class Map {
public:
	Map(int map_x, int map_y,string path);
	~Map();
	void draw(SDL_Window* gWindow, SDL_Surface *gScreenSurface);
	bool  loadImageFile();  //Load map to game.
	//void  setTile(int type, int x, int y); 
	void free_map_image();
	//vector< int >  getEnvironment(int position); //Get tile - type in all four direction.
	//bool  mouseOver(int x, int y);  //Check if mouse is over the map or outside map.
		
	//static std::string  getImage(int type);


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

	//SDL_Surface *  imageStartPoint;  
	//SDL_Surface *  imageEndPoint;
};



Map::Map(int map_x , int map_y ,string path) :sizeX(map_x), sizeY(map_y), mapImage_Loaded(path)
{
	//字串錯誤
	//"F:\\Project_resourses\\map\\hello_world.bmp";
	
	loadImageFile();
}

Map::~Map() //free other member
{
	free_map_image();
}

void Map::draw(SDL_Window* gWindow, SDL_Surface * gScreenSurface)
{
	//Apply the image
	SDL_BlitSurface(map_image, NULL, gScreenSurface, NULL);

	//Update the surface
	SDL_UpdateWindowSurface(gWindow);

}

bool Map::loadImageFile()
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
