// Project.cpp : 定義主控台應用程式的進入點。
//


//==========================設計===================================
//程式大部分重疊的塔與敵人大多設計為reference (&)  而非pointer



//=================================================================




/**************************問題***********************************/
//1.將tile 改造成tower ? 
//2.加上地圖外圍介面，需擴大視窗
/*****************************************************************/




#include "stdafx.h"
#include <iostream>
#include "SDL.h"
#include "initial.h"
#include "Map.h"
#include <stdio.h>
#define DEBUG 

vector<SDL_Rect*> LTexture::tower_image_clip_list;

using namespace std;

SDL_Surface* gScreenSurface = NULL;
SDL_Window* gWindow=NULL;
SDL_Renderer* gRenderer = NULL;

//Screen dimension constants
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 720;
const int TILE_WIDTH = 40;
const int WIDTH_TILE_NUMBER = SCREEN_WIDTH / TILE_WIDTH;
const int HEIGHT_TILE_NUMBER = SCREEN_HEIGHT / TILE_WIDTH;

extern const string TOWER_DIR_PATH;
extern const string FIRE_TOWER_IMAGE;
extern const string ICE_TOWER_IMAGE;
extern const string POISON_TOWER_IMAGE;

void close();

int main()
{
#ifdef DEBUG
	cout << "Enter main" << endl;
#endif // DEBUG

	init();
	Map map(SCREEN_WIDTH, SCREEN_HEIGHT, 
		"F:\\Project_resourses\\map\\map_image.png", 
		"F:\\Project_resourses\\map\\tiles_data.txt"); //invoke Map Constructor

	//simulate a player build a fire_tower
	FireTower* firetower_test = new FireTower(1,map.tile_tower_list[260]->width_tile_location ,
		map.tile_tower_list[260]->height_tile_location);

#ifdef DEBUG
	cout << "value of firetower_test pointer" << firetower_test << endl;
	//cout << firetower_test->get_tower_width_pixel_location;
#endif // DEBUG
	/*
	//modify !! argument order non-needed
	firetower_test->load_tower_texture(1, 260, map.tile_tower_list[260]->width_tile_location,
		map.tile_tower_list[260]->height_tile_location, SDL_BLENDMODE_BLEND, 255);
		*/
	firetower_test->tower_texture->load_tower(TOWER_DIR_PATH + FIRE_TOWER_IMAGE, map.tile_tower_list[260]->width_tile_location,
		map.tile_tower_list[260]->height_tile_location, LTexture::get_tower_image_clip_list()[1], SDL_BLENDMODE_BLEND, 255);


	/*for (int i = 0; i < WIDTH_TILE_NUMBER*HEIGHT_TILE_NUMBER && (i != 260); i++) {
		firetower_test->tower_texture->load_tower(TOWER_DIR_PATH + FIRE_TOWER_IMAGE, map.tile_tower_list[260]->width_tile_location,
			map.tile_tower_list[260]->height_tile_location, LTexture::get_tower_image_clip_list()[1], SDL_BLENDMODE_BLEND, 255);
	}*/

	firetower_test->get_tower_texture_ptr()->render(firetower_test->get_tower_width_pixel_location(), 
		firetower_test->get_tower_height_pixel_location(), LTexture::get_tower_image_clip_list()[firetower_test->get_tower_level()]);

	map.tile_tower_list[260]->tower = firetower_test; //used by virtual function
	
#ifdef DEBUG
	cout << "value of firetower_test->tower_texture pointer"<<firetower_test->tower_texture << endl;
	cout << "value of firetower_test->tower_texture->mTexture pointer" << firetower_test->tower_texture->mTexture << endl;
	cout << "value of map.map_image pointer" << map.get_map_image() << endl;
#endif // DEBUG






	map.draw(gWindow, gScreenSurface);


	
	//while (!quitGame && mainEvent->type != SDL_QUIT) { //game_loop
	//	int round = 0;  //回合數
	//	bool game_over = false;

	//	for (round = 1; game_over != true; round++) {  //round_loop
	//		input_interface(); //input 玩家介面
	//		deploy();  //玩家開始佈署
	//		game_over=calculate(); //計算結果 
	//		show_result();  //映出已經計算完成的遊戲畫面給玩家

	//	}//end of round_loop

	//}//end of game_loop
	system("PAUSE");
	close();
	
    return 0;
}//end of main 




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