#pragma once



#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <string>
//#include "SDL_ttf.h"
//#include "LButton.h"
#include "Map.h"





extern SDL_Surface* gScreenSurface;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Renderer* MapRenderer;
//Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int TILE_WIDTH;
extern const int WIDTH_TILE_NUMBER;
//extern const int HEIGHT_TILE_NUMBER;
//extern const int ENEMY_IMAGE_WIDTH;
using namespace std;

//Texture wrapper class
class LTexture
{
public:
	LTexture(); //Initializes variables
	~LTexture(); //Deallocates memory

	bool loadFromFile(std::string path); //Loads image at specified path
	void free();//Deallocates texture
	//void setColor(Uint8 red, Uint8 green, Uint8 blue);  //Set color modulation

	void setBlendMode(SDL_BlendMode blending); //Set blending
	void setAlpha(Uint8 alpha); //Set alpha modulation
	void render(int x, int y, SDL_Rect* clip = NULL); //Renders texture at given point

	//Gets image dimensions
	int getWidth() const;
	int getHeight() const;

	//need to modify!! less access!!
	//friend class Map;  
	SDL_Texture* get_mTexture_ptr();
protected:

	SDL_Texture* mTexture; //The actual hardware texture

	//Image dimensions
	int mWidth;
	int mHeight;

}; //end of class LTexture declaration





//need other constructors??
LTexture::LTexture(): mWidth (0), mHeight(0)
{
	mTexture = NULL;
}
LTexture::~LTexture()
{
	//Deallocate
	free();
}
//need color key?
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
		//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

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
int LTexture::getWidth()const
{
	return mWidth;
}
int LTexture::getHeight()const
{
	return mHeight;
}
SDL_Texture* LTexture::get_mTexture_ptr() {
	return mTexture;
}




//class MapTexture :public LTexture {
//public:
//	void render(int x, int y, SDL_Rect * clip);
//
//};
//void MapTexture::render(int x, int y, SDL_Rect * clip) {
//	//Set rendering space and render to screen
//	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
//
//	//Set clip rendering dimensions
//	if (clip != NULL)
//	{
//		renderQuad.w = clip->w;
//		renderQuad.h = clip->h;
//	}
//
//	//Render to screen
//	SDL_RenderCopy(MapRenderer, mTexture, clip, &renderQuad);
//}

