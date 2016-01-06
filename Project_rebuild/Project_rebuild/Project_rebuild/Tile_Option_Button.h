//#pragma once
#ifndef _TILE_OPTION_BUTTON_H
#define _TILE_OPTION_BUTTON_H

#include "LButton.h"


class Tile_Option_Button {
public:

	Tile_Option_Button();
	~Tile_Option_Button();

	//enum ButtonState
	//{
	//	BUTTON_MOUSE_OUT = 0,
	//	BUTTON_MOUSE_OVER = 1,
	//	BUTTON_MOUSE_DOWM = 2,
	//	BUTTON_MOUSE_OPEN_TILE = 3,
	//	//OPTION_BUTTON_LEVEL_UP = 3,
	//	//OPTION_BUTTON_LEVEL_DOWN = 4,
	//	//OPTION_BUTTON_DESTROY_TOWER = 5,
	//	//OPTION_BUTTON_BUILT_FIRE_TOWER = 6,
	//	//OPTION_BUTTON_BUILT_ICE_TOWER = 7,
	//	//OPTION_BUTTON_BUILT_POISON_TOWER = 8,
	//	//BUTTON_TOTLE = 9
	//};

	enum Option {
		NONE = 0,
		LEVEL_UP=1,
		LEVEL_DOWN=2,
		DESTROY_TOWER=3,
		BUILT_FIRE_TOWER=4,
		BUILT_ICE_TOWER =5,
		BUILT_POISON_TOWER =6,
		TOTAL_OPTIONS=7
	};

	//ButtonState detect_button_event(SDL_Event* e);
	void button_reponse();

private:
	LButton tile_button;
	vector<LButton> option_buttons;  //option_button[option]
	//ButtonState tile_button_state;

};

//Tile_Option_Button::ButtonState Tile_Option_Button::detect_button_event(SDL_Event* e) {
//	//If mouse event happened
//	if (e->type == SDL_MOUSEMOTION ||
//		e->type == SDL_MOUSEBUTTONDOWN ||
//		e->type == SDL_MOUSEBUTTONUP) {
//		if (!button.inside_button()) {
//
//		}
//	}
//}









#endif // !TILE_OPTION_BUTTON
