#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int TILE_WIDTH;
extern const int WIDTH_TILE_NUMBER;
extern const int HEIGHT_TILE_NUMBER;

const int TILE_BUTTON_WIDTH = TILE_WIDTH;
const int TILE_BUTTON_HEIGHT = TILE_WIDTH;
//const int BUILD_OPTOPN_BUTTON_WIDTH = ;
//const int BUILD_OPTOIN_BUTTON_HEIGHT = ;


enum LButtonSprite
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1,
	BUTTON_MOUSE_OPEN_TILE = 2,
	subBUTTON_LEVEL_UP = 3,
	subBUTTON_LEVEL_DOWN = 4,
	subBUTTON_DESTROY_TOWER = 5,
	subBUTTON_BUILT_FIRE_TOWER=6,
	subBUTTON_BUILT_ICE_TOWER=7,
	subBUTTON_BUILT_POISON_TOWER=8,
	BUTTON_TOTLE=9
};


//The mouse button
class LButton
{
public:
	//Initializes internal variables
	LButton();

	//Sets top left position
	void setPosition(int x, int y);

	//Handles mouse event
	void detect_mouse_Event(SDL_Event* e,int BUTTON_WIDTH, int BUTTON_HEIGHT);
	//void detect_tower_Event(SDL_Event*e);

	//Shows button sprite
	void render();
	void button_response();

	//open the tile botton?
	static bool tile_botton_open;

private:
	//Top left position
	SDL_Point mPosition;
	
	//Currently used global sprite
	LButtonSprite mCurrentSprite;
};


LButton::LButton() //Constructor
{
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentSprite = BUTTON_MOUSE_OUT;
}

void LButton::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::detect_mouse_Event(SDL_Event* e,int BUTTON_WIDTH,int BUTTON_HEIGHT)
{
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);


		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if (x < mPosition.x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (x > mPosition.x + BUTTON_WIDTH)
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < mPosition.y)
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > mPosition.y + BUTTON_HEIGHT)
		{
			inside = false;
		}

		//Mouse is outside button
		if (!inside)
		{
			mCurrentSprite = BUTTON_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_MOUSE_OVER;
				break;

			case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_MOUSE_OPEN_TILE;
				break;

			/*case SDL_MOUSEBUTTONUP:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
				break;*/
			}
		}
	}
}

//void LButton::detect_tower_Event(SDL_Event*e) {

//}



void LButton::button_response() {
	if(!tile_botton_open){
		switch(mCurrentSprite)
		{
		case BUTTON_MOUSE_OVER:
		case BUTTON_MOUSE_OPEN_TILE:
		default:
			break;
		}
	}
	else {
		switch (mCurrentSprite)
		{
		case subBUTTON_LEVEL_UP:
		case subBUTTON_LEVEL_DOWN:
		case subBUTTON_DESTROY_TOWER:
		case subBUTTON_BUILT_FIRE_TOWER:
		case subBUTTON_BUILT_ICE_TOWER:
		case subBUTTON_BUILT_POISON_TOWER:
		default:
			break;
		}
	}
}




void LButton::render()
{
	//Show current button sprite
	//gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, &gSpriteClips[mCurrentSprite]);
}