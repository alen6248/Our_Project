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
#include "Abstract_Enemy.h"
#include "StrongEnemy.h"
#include "LTimer.h"
#include "Abstract_Tower.h"
#include "FireTower.h"

using namespace std;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Surface* gScreenSurface = NULL;

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 720;
const int TILE_WIDTH = 40;
const int TIME_PER_FRAM = 100; 


bool LButton::tile_botton_open; //static class member of LButton
vector<SDL_Rect*> Abstract_Enemy::enemy_image_clip_list; //static class member of Abstract_Enemy
vector<SDL_Rect*> Abstract_Tower::tower_image_clip_list;
int Abstract_Tower::tower_number; 

void draw();
void close();


int main()
{
	init();

	Map map(SCREEN_WIDTH, SCREEN_HEIGHT,
		"F:\\Project_resourses\\map\\map_image.png"
		); //invoke Map Constructor
	LTimer timer;

	Tile tile_test("F:\\Project_resourses\\tower\\defalut_tile.png",0,0);
	
	//tentatively test
	StrongEnemy strong_enemy_test(1, 100, 10);
	FireTower fire_tower_test(1,12,12);

	for (int i = 0; i < 200; i++) {

		timer.start();

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		//render map and tile
		map.get_map_texture()->render(0, 0, NULL);
		tile_test.render();
		fire_tower_test.render();

		strong_enemy_test.go_forward();
		strong_enemy_test.render();
		draw();

		SDL_Delay(100 - timer.getTicks());
		timer.stop();
		
	}


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