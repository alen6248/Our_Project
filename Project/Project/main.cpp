// Project.cpp : �w�q�D���x���ε{�����i�J�I�C
//


//==========================�]�p===================================
//�{���j�������|����P�ĤH�j�h�]�p��reference (&)  �ӫDpointer



//=================================================================




/**************************���D***********************************/
//1.�Ntile ��y��tower ? 

/*****************************************************************/

//�ק�
//2015.12.29   �ﱼmain



#include "stdafx.h"
#include <iostream>
#include "SDL.h"
#include "initial.h"
#include "Map.h"
#include <stdio.h>
#define DEBUG 

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

//void MouseInput();
void close();




int main()
{
#ifdef DEBUG
	cout << "Enter main" << endl;
#endif // DEBUG

	

	init();
	Map map(SCREEN_WIDTH, SCREEN_HEIGHT, "F:\\Project_resourses\\map\\map_image.png", "F:\\Project_resourses\\map\\tiles_data.txt"); //invoke Map Constructor
	
	//need to redefine set tower_function
	map.tiles[260]->tower_type = Map::unit_Tile::TowerType::FireTower; //���a�H�K�]�w�@��

	//map.load_all_tower_image();

	map.draw(gWindow, gScreenSurface);


	
	//while (!quitGame && mainEvent->type != SDL_QUIT) { //game_loop
	//	int round = 0;  //�^�X��
	//	bool game_over = false;

	//	for (round = 1; game_over != true; round++) {  //round_loop
	//		input_interface(); //input ���a����
	//		deploy();  //���a�}�l�G�p
	//		game_over=calculate(); //�p�⵲�G 
	//		show_result();  //�M�X�w�g�p�⧹�����C���e�������a

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