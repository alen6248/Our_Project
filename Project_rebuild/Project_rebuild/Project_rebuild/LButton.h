#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"
//#include "Tile_Option_Button.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int TILE_WIDTH;
extern const int WIDTH_TILE_NUMBER;
extern const int HEIGHT_TILE_NUMBER;

const int TILE_BUTTON_WIDTH = TILE_WIDTH;
const int TILE_BUTTON_HEIGHT = TILE_WIDTH;
//const int BUILD_OPTOPN_BUTTON_WIDTH = ;
//const int BUILD_OPTOIN_BUTTON_HEIGHT = ;




//The mouse button
class LButton
{
public:
	enum ButtonState
	{
		BUTTON_CAN_NOT_USE,
		BUTTON_MOUSE_OUT ,
		BUTTON_MOUSE_OVER ,
		BUTTON_MOUSE_DOWN ,
		BUTTON_TOTLE_STATE 
	};

	LButton(string _button_state_image_path, int x_pixel, int y_pixel, 
			int _button_width, int _button_height);
	//LButton(LButton&);  //there is no pointer member
	~LButton();

	//position 
	void set_x_pixel_location(int x_pixel);
	void set_y_pixel_location(int y_pixel);
	int get_x_pixel_location() const;
	int get_y_pixel_location() const;

	//dimension
	void set_button_width(int _width);
	void set_button_height(int _height);
	int get_button_width() const;
	int get_button_height() const;

	//texture
	void load_button_state_texture();
	LTexture& get_button_state_texture() ;
	string get_button_state_image_path() const;
	void render();

	//clip
	void set_button_state_image_clip_list();
	vector<SDL_Rect*>& get_button_state_image_clip_list();

	//button state
	void set_button_state(ButtonState _new_state);
	ButtonState get_button_state() const;
	
	//detect
	void detect_mouse_Event(SDL_Event*e);
	bool inside_button(); //need?
	
private:
	//Top left position
	int x_pixel_location;
	int y_pixel_location;
	int button_width;
	int button_height;

	vector<SDL_Rect*> button_state_image_clip_list;  //not static member!! 

	//texture
	LTexture button_state_texture;
	string button_state_image_path;

	//button state
	ButtonState button_state;
};

//LButton::LButton() {}
LButton::LButton(string _button_state_image_path,int x_pixel,int y_pixel,int _button_width,int _button_height):
		x_pixel_location(x_pixel),y_pixel_location(y_pixel),
		button_width(_button_width),button_height(_button_height),
		button_state_image_path(_button_state_image_path)
{
	button_state = BUTTON_MOUSE_OUT;
	set_button_state_image_clip_list();
	load_button_state_texture();
}
LButton::~LButton() {}
//position
void LButton::set_x_pixel_location(int x_pixel) {
	x_pixel_location = x_pixel;
}
void LButton::set_y_pixel_location(int y_pixel) {
	y_pixel_location = y_pixel;
}
int LButton::get_x_pixel_location() const {
	return x_pixel_location;
}
int LButton::get_y_pixel_location() const {
	return y_pixel_location;

}
void LButton::set_button_width(int _width) {
	button_width = _width;
}
void LButton::set_button_height(int _height) {
	button_height = _height;
}
int LButton::get_button_width() const {
	return button_width;
}
int LButton::get_button_height() const {
	return button_height;
}

//texture
void LButton::load_button_state_texture() {
	button_state_texture.loadFromFile(button_state_image_path);
	button_state_texture.setBlendMode(SDL_BLENDMODE_BLEND);
	button_state_texture.setAlpha(255);
}
LTexture& LButton::get_button_state_texture()  {
	return button_state_texture;
}
string LButton::get_button_state_image_path() const {
	return button_state_image_path;
}
void LButton::render()
{
	//Show current button sprite
	button_state_texture.render(x_pixel_location, y_pixel_location,
		button_state_image_clip_list[(int)button_state]);

	//gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, &gSpriteClips[mCurrentSprite]);
}
void LButton::set_button_state_image_clip_list() {
	button_state_image_clip_list.resize(BUTTON_TOTLE_STATE);

	for (int i = 0; i < (int)BUTTON_TOTLE_STATE; i++) {
		button_state_image_clip_list[i] = new SDL_Rect;
		button_state_image_clip_list[i]->x = i*button_width;
		button_state_image_clip_list[i]->y = 0;
		button_state_image_clip_list[i]->w = button_width;
		button_state_image_clip_list[i]->h = button_height;
	}

}
vector<SDL_Rect*>& LButton::get_button_state_image_clip_list(){
	return button_state_image_clip_list;
}

//state
void LButton::set_button_state(ButtonState _new_state) {
	button_state = _new_state;
}
LButton::ButtonState LButton::get_button_state() const {
	return button_state;
}



//void LButton::detect_mouse_Event(SDL_Event* e) {
//	switch (e->type)
//	{
//	case SDL_MOUSEMOTION:
//		button_state = BUTTON_MOUSE_OVER;
//		break;
//
//	case SDL_MOUSEBUTTONDOWN:
//		button_state = BUTTON_MOUSE_DOWN;
//		break;
//
//		/*case SDL_MOUSEBUTTONUP:
//		mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
//		break;*/
//	}
//}
//detect mouse event
void LButton::detect_mouse_Event(SDL_Event* e)
{
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || 
		e->type == SDL_MOUSEBUTTONDOWN || 
		e->type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		if (button_state == BUTTON_CAN_NOT_USE) {} //if Button can not use -> do nothing 
		else {
			//Check if mouse is in button
			bool inside = true;

			//Mouse is left of the button
			if (x < x_pixel_location)
			{
				inside = false;
			}
			//Mouse is right of the button
			else if (x > x_pixel_location + button_width)
			{
				inside = false;
			}
			//Mouse above the button
			else if (y < y_pixel_location)
			{
				inside = false;
			}
			//Mouse below the button
			else if (y > y_pixel_location + button_height)
			{
				inside = false;
			}

			//Mouse is outside button
			if (!inside)
			{
				button_state = BUTTON_MOUSE_OUT;
			}
			//Mouse is inside button
			else
			{
				//Set mouse over sprite
				switch (e->type)
				{
				case SDL_MOUSEMOTION:
					button_state = BUTTON_MOUSE_OVER;
					break;

				case SDL_MOUSEBUTTONDOWN:
					button_state = BUTTON_MOUSE_DOWN;
					break;

					/*case SDL_MOUSEBUTTONUP:
						mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
						break;*/
				}
			}//end of else
		}// !(button_state==BUTTON_CAN_NOT_USE)
	}// end of "If mouse event happened"
}//end function declare
bool LButton::inside_button() {
	//Get mouse position
	int x, y;
	SDL_GetMouseState(&x, &y);


	//Check if mouse is in button
	bool inside = true;

	//Mouse is left of the button
	if (x < x_pixel_location)
	{
		inside = false;
	}
	//Mouse is right of the button
	else if (x > x_pixel_location + button_width)
	{
		inside = false;
	}
	//Mouse above the button
	else if (y < y_pixel_location)
	{
		inside = false;
	}
	//Mouse below the button
	else if (y > y_pixel_location + button_height)
	{
		inside = false;
	}
	return inside;

}



//
//class TileButton :public LButton {
//	TileButton() {};
//	void detect_mouse_Event(SDL_Event* e);
//};
//void TileButton::detect_mouse_Event(SDL_Event* e) {
//	switch (e->type)
//	{
//	case SDL_MOUSEMOTION:
//		set_button_state(BUTTON_MOUSE_OVER);
//		break;
//
//	case SDL_MOUSEBUTTONDOWN:
//		set_button_state(BUTTON_MOUSE_DOWN);
//		break;
//
//		/*case SDL_MOUSEBUTTONUP:
//		mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
//		break;*/
//	}
//}
