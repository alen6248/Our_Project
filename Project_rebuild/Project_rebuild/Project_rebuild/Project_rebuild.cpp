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


int main()
{
	init();

	Map map(SCREEN_WIDTH, SCREEN_HEIGHT,
		"F:\\Project_resourses\\map\\map_image.png",
		"F:\\Project_resourses\\map\\tiles_data.txt"); //invoke Map Constructor

	Tile tile_test("F:\\Project_resourses\\tower\\defalut_tile.png",0,0);
	tile_test.render();

	draw();
	system("PAUSE");
    return 0;
}

//void 


void draw() {
	SDL_RenderPresent(gRenderer);
}