// Project_rebuild.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "SDL.h"
#include "SDL_image.h"
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
#include "Screen_Player.h"


//#include "Attack_Calculator.h"

using namespace std;
SDL_Event e;
SDL_Window* gWindow = NULL;
//SDL_Renderer* MapRenderer = NULL; //creat another renderer for map
SDL_Renderer* gRenderer = NULL;  
SDL_Surface* gScreenSurface = NULL;


const int SCREEN_WIDTH = 1160;
const int SCREEN_HEIGHT = 800;
const int MAP_WIDTH = 960;
const int MAP_HEIGHT = 720;
const int TILE_WIDTH = 40;
const int TIME_PER_FRAM = 100; 

////declare static member of class
vector<vector<vector<SDL_Rect*>>> Abstract_Enemy::enemy_image_clip_list; //static class member of Abstract_Enemy
//vector<vector<vector<SDL_Rect*>>> BossEnemy::boss_enemy_image_clip_list;
vector<SDL_Rect*> Abstract_Tower::tower_image_clip_list;
int Abstract_Tower::tower_number; 
vector<Enemy_Path> Abstract_Enemy::path;


void close();



int main()
{
	init();
	//Map map(SCREEN_WIDTH, SCREEN_HEIGHT); 
	Input_Interface input_interface;
	LTimer timer;


	
	Attack_Calculator attack_calculator(input_interface);
	Screen_Player screen_player(input_interface.get_Towers(),timer,input_interface);

	
	input_interface.Input_Interface_Core();
	attack_calculator.Attack_Calculator_Core();
	screen_player.Screen_Player_Core();

	system("PAUSE");
	close();
    return 0;
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