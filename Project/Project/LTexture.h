#pragma once

#ifndef _LTexture_H
#define _LTexture_H

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <string>
#include "SDL_ttf.h"
//#include "LButton.h"
#include "Map.h"


using namespace std;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int TILE_WIDTH;
extern const int WIDTH_TILE_NUMBER;
extern const int HEIGHT_TILE_NUMBER;

extern SDL_Surface* gScreenSurface;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

//Texture wrapper class
class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	void load_tower(string path,int width_number,int height_number,SDL_Rect*clip,SDL_BlendMode blending,Uint8 alpha);
	//Loads image at specified path
	bool loadFromFile(std::string path);

#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

	//Deallocates texture
	void free();

	//Set color modulation
	//void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL);

	//Gets image dimensions
	int getWidth();
	int getHeight();

	static vector<SDL_Rect*> tower_image_clip_list;  //–眎瓜Τtowerぃ单妓
	static void set_tower_image_clip();

	friend class Map;  //惠эΘ秨场だㄧ计
	friend class Tower; //惠эΘ秨场だㄧ计
	friend class FireTower;
	friend class IceTower;
	friend class PoisonTower;
private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
	
};


#endif // !_LTexture_H



LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

void LTexture::load_tower(string path, int width_number, int height_number, SDL_Rect*clip, SDL_BlendMode blending, Uint8 alpha) {
	loadFromFile(path);
	render(width_number*TILE_WIDTH, height_number*TILE_WIDTH, clip);
	setBlendMode(blending);
	setAlpha(alpha);
}

void LTexture::set_tower_image_clip() {  //set static member
	tower_image_clip_list.resize(5); //单1,2,3,4,ぃ1 
#ifdef DEBUG
	cout << "enter LTexture::set clip(), set static member" << endl;
	chip_list[0] = new SDL_Rect;

#endif // DEBUG

	for (int i = 1; i < 5; i++) { //眖1秨﹍
		tower_image_clip_list[i] = new SDL_Rect;
		tower_image_clip_list[i]->x = (i-1)*TILE_WIDTH;
		tower_image_clip_list[i]->y = 0;
		tower_image_clip_list[i]->w = TILE_WIDTH;
		tower_image_clip_list[i]->h = TILE_WIDTH;
	}
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect * clip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}


/*
#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return mTexture != NULL;
}
#endif
*/