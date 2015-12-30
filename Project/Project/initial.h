#pragma once
//==========================�]�p===================================

//��l�Ƶ���
//��l�Ƶ����e��
//��l�Ʒƹ�
//��l����L
//��l�Ʀa��
//��l�ƼĤH���u
//��l�ƪ��a�]�w
//��l�ƥi��m�𪺦�m
//��l�ƶ�B�ĤH
//=================================================================




/**************************���D***********************************/
//�ϥ�tile?

/*****************************************************************/



#include"SDL.h"
#include"Setting.h"
#include"Map.h"

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 720;

bool SDL_init();

void init() {
	
	SDL_init();








	Setting setting; //�I�sSetting Constructor
	Map map(SCREEN_WIDTH, SCREEN_HEIGHT); //�I�s Map Constructor
	

}


bool SDL_init() {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}



	return success;
}


