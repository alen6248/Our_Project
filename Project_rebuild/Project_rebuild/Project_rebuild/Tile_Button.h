#pragma once
//decarded !!
#ifndef _TILE_BUTTON_H
#define _TILE_BUTTON_H

#include "LButton.h"

class Tile_Button {

public:
	Tile_Button();
	~Tile_Button();

	void button_reponse();
	void render();
	void load_buttons_texture();
	void accept_event(SDL_Event &e);


private:
	LButton selected_button;
	LButton moving_button;

};






#endif // !_TILE_BUTTON_H
