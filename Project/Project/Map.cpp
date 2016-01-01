#include "Map.h"
#include "stdafx.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#define DEBUG 
using namespace std;

extern SDL_Surface* gScreenSurface;
extern SDL_Window* gWindow;



Map::Map(int map_x, int map_y, string path) :sizeX(map_x), sizeY(map_y), mapImage_Loaded(path)
{
	//¦r¦ê¿ù»~
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