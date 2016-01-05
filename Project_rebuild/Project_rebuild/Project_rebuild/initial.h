//#pragma once
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
//�ϥ�tile? Yes
//draw �ݦA�[�Jtile

/*****************************************************************/

#ifndef _INITIAL_H
#define _INITIAL_H



#include"SDL.h"
//#include"Setting.h"
//#include"Map.h"
#include <stdio.h>
#include <iostream>
#include "AbstractEnemy.h"

//extern SDL_Surface* gScreenSurface;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

extern const int SCREEN_WIDTH ;
extern const int SCREEN_HEIGHT ;
extern const int TILE_WIDTH;
extern const int WIDTH_TILE_NUMBER;
extern const int HEIGHT_TILE_NUMBER;

bool SDL_init();

using namespace std;

void init() {
#ifdef DEBUG
	cout << "enter init()" << endl;
#endif // DEBUG
	Abstract_Enemy::set_tower_image_clip(); //initialize static class member
	SDL_init();
}
/*
bool SDL_init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("TowerDefence", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);

		}
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer == NULL) {
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {

			////Initialize renderer color
			//SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

			////Initialize PNG loading
			//int imgFlags = IMG_INIT_PNG;
			//if (!(IMG_Init(imgFlags) & imgFlags))
			//{
			//	printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			//	success = false;
		}
	}

	return success;
}
*/




bool SDL_init() {

#ifdef DEBUG
	cout << "enter SDL_init()" << endl;
#endif // DEBUG

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
		gWindow = SDL_CreateWindow("Tower Defence", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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


			}
		}
	}



	return success;
}


#endif // !_INITIAL_H