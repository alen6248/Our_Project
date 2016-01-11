// Project_rebuild.cpp : �w�q�D���x���ε{�����i�J�I�C
//

#include "stdafx.h"
#include "SDL.h"
//#include "SDL_ttf.h"
#include "SDL_image.h"
//#include "SDL_mixer.h"
#include "initial.h"
#include "Map.h"
#include "LButton.h"
#include "Tile.h"
#include "Abstract_Enemy.h"
#include "StrongEnemy.h"
#include "FastEnemy.h"
#include "BossEnemy.h"
#include "LTimer.h"
#include "Abstract_Tower.h"
#include "FireTower.h"
#include "IceTower.h"
#include "PoisonTower.h"
#include "Attack_Calculator.h"
#include "Input_Interface.h"


//#include "Attack_Calculator.h"

using namespace std;
SDL_Event e;
SDL_Window* gWindow = NULL;
SDL_Renderer* MapRenderer = NULL; //creat another renderer for map
SDL_Renderer* gRenderer = NULL;  
SDL_Surface* gScreenSurface = NULL;


const int SCREEN_WIDTH = 1160;
const int SCREEN_HEIGHT = 800;
const int MAP_WIDTH = 960;
const int MAP_HEIGHT = 720;
const int TILE_WIDTH = 40;
const int TIME_PER_FRAM = 100; 

////declare static member of class
//bool LButton::tile_botton_open; //static class member of LButton
vector<vector<vector<SDL_Rect*>>> Abstract_Enemy::enemy_image_clip_list; //static class member of Abstract_Enemy
//vector<vector<vector<SDL_Rect*>>> BossEnemy::boss_enemy_image_clip_list;
vector<SDL_Rect*> Abstract_Tower::tower_image_clip_list;
int Abstract_Tower::tower_number; 
vector<Enemy_Path> Abstract_Enemy::path;

void draw();
void close();



int main()
{
	init();
	Input_Interface input_interface;
	//Map map(SCREEN_WIDTH, SCREEN_HEIGHT); //invoke Map Constructor
	LTimer timer;

	//F:\\Project_resourses\\tower\\defalut_tile.png
	//Tile tile_test(0,0);
	
	
	Attack_Calculator attack_calculator(input_interface);

	//tentatively test
	BossEnemy boss_enemy_test(1, 100, 10);
	StrongEnemy strong_enemy_test(1, 100, 7);
	FastEnemy fast_enemy_test(1, 100, 20);
	//vector<Abstract_Tower*> Towers_main;
	
	input_interface.Input_Interface_Core();
	attack_calculator.Attack_Calculator_Core();


	for (int i = 0; i < 1000; i++) {
		
		timer.start();
		//LButton start_button;
		//Clear screen
		//SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		//SDL_RenderClear(gRenderer);

		//render map and tile
		//map.get_map_texture()->render(0, 0, NULL);

		boss_enemy_test.go_forward();
		boss_enemy_test.render();

		strong_enemy_test.go_forward();
		strong_enemy_test.render();

		fast_enemy_test.go_forward();
		fast_enemy_test.render();
		draw();

		SDL_Delay(75 - timer.getTicks());
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