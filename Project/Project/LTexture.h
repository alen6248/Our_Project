//#pragma once

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

#define DEBUG



extern SDL_Surface* gScreenSurface;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

//Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int TILE_WIDTH;
extern const int WIDTH_TILE_NUMBER;
extern const int HEIGHT_TILE_NUMBER;
extern const int ENEMY_IMAGE_WIDTH;
using namespace std;

//Texture wrapper class
class LTexture
{
public:
	LTexture(); //Initializes variables
	~LTexture(); //Deallocates memory

	//load
		
	void load_tower(string path,int width_tile_location,int height_tile_location,
		SDL_Rect*clip,SDL_BlendMode blending,Uint8 alpha);
	void load_enemy(string path, int width_pixel_location, int height_pixel_location,
		SDL_Rect*clip, SDL_BlendMode blending, Uint8 alpha);
	bool loadFromFile(std::string path); //Loads image at specified path
	

#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif
	void free();//Deallocates texture

	//Set color modulation
	//void setColor(Uint8 red, Uint8 green, Uint8 blue);

	void setBlendMode(SDL_BlendMode blending); //Set blending
	void setAlpha(Uint8 alpha); //Set alpha modulation
	void render(int x, int y, SDL_Rect* clip = NULL); //Renders texture at given point

	//Gets image dimensions
	int getWidth() const;
	int getHeight() const;

	//tower_image_clip_list
	static vector<SDL_Rect*>& get_tower_image_clip_list();
	static void set_tower_image_clip();
	//enemy_image_clip_list
	static vector<SDL_Rect*>& get_enemy_image_clip_list();
	static void set_enemy_image_clip();

	//need to modify!! less access!!
	friend class Map;  
	friend class Tower; 
	friend class FireTower;
	friend class IceTower;
	friend class PoisonTower;
	SDL_Texture* get_mTexture_ptr();
	SDL_Texture* mTexture; //The actual hardware texture  /*¼È®É*/
private:
	//SDL_Texture* mTexture; //The actual hardware texture

	//Image dimensions
	int mWidth;
	int mHeight;

	//store the clip data of towers image in different levels
	static vector<SDL_Rect*> tower_image_clip_list;  
	static vector<SDL_Rect*> enemy_image_clip_list;
}; //end of class LTexture declaration


#endif // !_LTexture_H


//need other constructors??
LTexture::LTexture():/*mTexture(NULL),*/ mWidth (0), mHeight(0)
{
	mTexture = NULL;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

void LTexture::load_tower(string path, int width_tile_location, int height_tile_location, 
						SDL_Rect*clip, SDL_BlendMode blending= SDL_BLENDMODE_BLEND, Uint8 alpha=255) {
	loadFromFile(path);
	render(width_tile_location*TILE_WIDTH, height_tile_location*TILE_WIDTH, clip);
	setBlendMode(blending);
	setAlpha(alpha);
}
void LTexture::load_enemy(string path, int width_pixel_location, int height_pixel_location,
						SDL_Rect*clip, SDL_BlendMode blending= SDL_BLENDMODE_BLEND, Uint8 alpha=255) {
						loadFromFile(path);
						render(width_pixel_location, height_pixel_location, clip);
						setBlendMode(blending);
						setAlpha(alpha);
					}
void LTexture::set_tower_image_clip() {  //set static member
	tower_image_clip_list.resize(5); //level:1,2,3,4, exclusive of 0

	for (int i = 1; i < 5; i++) { //start from 1
		tower_image_clip_list[i] = new SDL_Rect;
		tower_image_clip_list[i]->x = (i-1)*TILE_WIDTH;
		tower_image_clip_list[i]->y = 0;
		tower_image_clip_list[i]->w = TILE_WIDTH;
		tower_image_clip_list[i]->h = TILE_WIDTH;
	}
}
void LTexture::set_enemy_image_clip() {//set static member
	enemy_image_clip_list.resize(5);//level:1,2,3,4, exclusive of 0

	for (int i = 1; i < 5; i++) {
		enemy_image_clip_list[i] = new SDL_Rect;
		enemy_image_clip_list[i]->x = (i - 1)*ENEMY_IMAGE_WIDTH;
		enemy_image_clip_list[i]->y = 0;
		enemy_image_clip_list[i]->w = ENEMY_IMAGE_WIDTH;
		enemy_image_clip_list[i]->h = ENEMY_IMAGE_WIDTH;
	}
}
//need color key?
bool LTexture::loadFromFile(std::string path)
{
#ifdef DEBUG
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return false;
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
		mTexture = newTexture;
		return true;
	}
	
	

#endif // DEBUG




#ifndef DEBUG
	//Get rid of preexisting texture
	//free();  //comment out tentatively!!

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
#endif
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
int LTexture::getWidth()const
{
	return mWidth;
}
int LTexture::getHeight()const
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
vector<SDL_Rect*>& LTexture::get_tower_image_clip_list() {
	return tower_image_clip_list;
}
vector<SDL_Rect*>& LTexture::get_enemy_image_clip_list() {
	return enemy_image_clip_list;
}
SDL_Texture* LTexture::get_mTexture_ptr() {
	return mTexture;
}