// Project_rebuild.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "initial.h"
#include "Map.h"
#include "LButton.h"
#include "Tile.h"
using namespace std;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Surface* gScreenSurface = NULL;

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 720;
const int TILE_WIDTH = 40;
const int ENEMY_IMAGE_WIDTH = 80;

bool LButton::tile_botton_open;

void draw();
void close();


int main()
{
	init();

	Map map(SCREEN_WIDTH, SCREEN_HEIGHT,
		"F:\\Project_resourses\\map\\map_image.png"
		); //invoke Map Constructor

	Tile tile_test("F:\\Project_resourses\\tower\\defalut_tile.png",0,0);
	tile_test.render();

	draw();
	system("PAUSE");
	close();
    return 0;
}




void draw() {
	SDL_RenderPresent(gRenderer);
}

void close() {
	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}