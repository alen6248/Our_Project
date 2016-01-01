// Project.cpp : 定義主控台應用程式的進入點。
//


//==========================設計===================================
//程式大部分重疊的塔與敵人大多設計為reference (&)  而非pointer



//=================================================================




/**************************問題***********************************/


/*****************************************************************/

//修改
//2015.12.29   改掉main



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


//void MouseInput();
void close();




int main()
{
#ifdef DEBUG
	cout << "Enter main" << endl;
#endif // DEBUG

	

	init();
	SDL_Delay(2000);
	
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