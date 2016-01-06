//#pragma once
#ifndef _INPUT_INTERFACE_H
#define _INPUT_INTERFACE_H

#include "Tile.h"
#include "Abstract_Tower.h"
#include "FireTower.h"
#include "Option_Button.h"
#include <iostream>
#include <vector>


class Input_Interface{
public:

	void Input_Interface_Core(); //Core_function

	Input_Interface();
	~Input_Interface();

	void init_Tiles();
	//void init_option_button(); //call Option_Button constructor
	void init_two_dynamic_tiles();
	//void init_Towers(); //un_needed, wait the player to creat towers

	void player_build_tower();
	void player_destroy_tower();
	void player_level_up_tower();
	void player_level_down_tower();

	//mouse
	void detect_mouse_position();
	bool mouse_in_map();
	bool mouse_in_option_button();


private:
	//Tile
	vector<vector<Tile*>> Tiles; //Two dimension containor
	//dynamic tiles
	Tile* selected_tile; //used to control Tiles
	Tile* moving_tile; //used to control Tiles

	//Start button
	//Start_Button* start_button; //creat another class??

	//Option button
	Option_Button* option_button;

	//Towers
	vector<Abstract_Tower*> Towers;

	//mouse position
	mutable int mouse_x;
	mutable int mouse_y;
};
void Input_Interface::Input_Interface_Core() {
	while (!start_button->start) {
		detect_mouse_position();
		if (mouse_in_map()) {
			//moving_tile
			moving_tile = Tiles[mouse_x][mouse_y];
			moving_tile->get_tile_button()->detect_mouse_Event(&e);

			//selected_tile
			if (moving_tile->get_tile_button()->get_button_state() == LButton::ButtonState::BUTTON_MOUSE_DOWN) {
				selected_tile= Tiles[mouse_x][mouse_y];
				!!open option button!!
			}
		


		}
		else if (mouse_in_option_button()) {
			option_button->accept_event(&e);
			option_button_response();//打開option說明文件 或是execute  
		}
		render(); //render every thing in the interface
		draw(); //present Renderer
	}
}

Input_Interface::Input_Interface() {
	init_Tiles();
	init_two_dynamic_tiles();
	option_button = new Option_Button; //call Option_Button constructor
	//init_Towers();

}
void Input_Interface::init_Tiles(){
	Tiles.resize(24);
	for (int i = 0; i < 24; i++) {
		Tiles[i].resize(18);
	}
	for (int x_tile = 0; x_tile < 24; x_tile++) {
		for (int y_tile = 0; y_tile < 18; y_tile++) {
			Tiles[x_tile][y_tile] = new Tile(x_tile, y_tile);
		}
	}
}
void Input_Interface::init_two_dynamic_tiles() {
	selected_tile = new Tile(0,0);
	moving_tile = new Tile(0,0);
}
void Input_Interface::detect_mouse_position() {
	SDL_GetMouseState(&mouse_x, &mouse_y);
}








#endif // !_INPUT_INTERFACE_H
