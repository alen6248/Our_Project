//#pragma once
#ifndef _INPUT_INTERFACE_H
#define _INPUT_INTERFACE_H

#include "Tile.h"
#include "Abstract_Tower.h"
#include "FireTower.h"
#include "IceTower.h"
#include "PoisonTower.h"
#include "Option_Interface.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

extern SDL_Event e;
extern const int TILE_WIDTH;
extern const int MAP_WIDTH;
extern const int MAP_HEIGHT;


extern const string BUTTON_DIR_PATH ;
//const string LEVEL_UP_BUTTON = "level_up.png";
//const string LEVEL_DOWN_BUTTON = "level_down.png";
//const string DESTROY_BUTTON = "destroy.png";
//const string FIRE_TOWER_BUTTON = "fire_tower_button.png";
//const string ICE_TOWER_BUTTON = "ice_tower_button.png";
//const string POISON_TOWER_BUTTON = "poison_tower_button.png";
//const string EXECUTE_BUTTON = "execute_button.png";

const string START_BUTTON = "start_button.png";
const string TILE_DIR_PATH = "F:\\Project_resourses\\tile\\";
const string TILE_DATA = "tile_data.txt";


class Input_Interface{
public:

	void Input_Interface_Core(); //Core_function

	Input_Interface();
	~Input_Interface();
	void terminate_input_interface();
	void init_Tiles();
	//void init_option_button(); //call Option_Interface constructor
	void init_two_dynamic_tiles();
	//void init_Towers(); //un_needed, wait the player to creat towers

	//option_interface do work
	void execute_build_fire_tower();
	void execute_build_ice_tower();
	void execute_build_poison_tower();
	void execute_destroy_tower();
	void execute_level_up_tower();
	void execute_level_down_tower();

	bool player_require_build_fire_tower();
	bool player_require_build_ice_tower();
	bool player_require_build_poison_tower();
	bool player_require_level_up();
	bool player_require_level_down();
	bool player_require_destroy();

	void option_button_response();

	//render
	void render(); //render everything
	void render_tiles();
	void render_towers();
	//map is rendered by another renderer!!

	// tile opem option button interface
	void tile_open_option_interface();


	void draw();

	//mouse
	void detect_mouse_position();
	bool mouse_in_map();
	bool mouse_in_option_interface();


private:
	//Tile
	vector<vector<Tile*>> Tiles; //Two dimension containor
	//dynamic tiles
	Tile* selected_tile; //used to control Tiles
	Tile* moving_tile; //used to control Tiles

	//LButton start_button; 
	//Start button
	//Start_Button* start_button; //creat another class??

	//Option button
	Option_Interface* option_interface;

	//start button
	LButton start_button;

	//Towers
	vector<Abstract_Tower*> Towers;

	//mouse position
	mutable int mouse_x;
	mutable int mouse_y;
};
void Input_Interface::Input_Interface_Core() {//core input loop

	Map map(SCREEN_WIDTH, SCREEN_HEIGHT); //暫時

	//!! modify: detect start_button event
	while (!(start_button.get_button_state()==LButton::ButtonState::BUTTON_MOUSE_DOWN)) { 
		while (SDL_PollEvent(&e) != 0) { //use while or if ??


			detect_mouse_position();
			if (mouse_in_map()) {
				if (moving_tile != NULL) {
					if (moving_tile->get_tile_state() != LButton::ButtonState::BUTTON_CAN_NOT_USE) {
						moving_tile->set_tile_state(LButton::ButtonState::BUTTON_MOUSE_OUT);
					}
				}
				//moving_tile
				//int x_tile_location = ((int)(mouse_x / TILE_WIDTH)==24)?((int)(mouse_x / TILE_WIDTH)):23; //排除18的情況(超出vector可用範圍)
				//int y_tile_location = ((int)(mouse_y / TILE_WIDTH) == 18) ? ((int)(mouse_y / TILE_WIDTH)) : 17; //排除18的情況(超出vector可用範圍)
				
				int x_tile_location = (int)(mouse_x / TILE_WIDTH);
				int y_tile_location = (int)(mouse_y / TILE_WIDTH);
				if (x_tile_location == 24) { x_tile_location = 23; }
				if (y_tile_location == 18) { y_tile_location = 17; }
				moving_tile = Tiles[x_tile_location][y_tile_location];
				
				if (moving_tile->get_tile_state() != LButton::ButtonState::BUTTON_CAN_NOT_USE) {
					moving_tile->set_tile_state(LButton::ButtonState::BUTTON_MOUSE_OVER);
				}
				moving_tile->get_tile_button()->detect_mouse_Event(&e); //detect mouse event

				//selected_tile
				if (moving_tile->get_tile_button()->get_button_state() == LButton::ButtonState::BUTTON_MOUSE_DOWN) {
					//if (selected_tile != NULL) {
					//	selected_tile->set_tile_state(LButton::ButtonState::BUTTON_MOUSE_OUT);//previous select tile
					//}
					selected_tile = moving_tile; //pointer copy
					
					tile_open_option_interface();
				}
			}
			else if (mouse_in_option_interface()) {
				option_interface->accept_event(e); //detect event
				option_button_response();//do button function  
			}
			map.get_map_texture()->render(0, 0, NULL); //tentatively put it here
			render(); //render every thing in the interface
			draw(); //present Renderer
		}//end of while SDL_PollEvent(&e) != 0
	}//end of !start_gmae
}//end of core input loop

Input_Interface::Input_Interface():selected_tile(NULL), moving_tile(NULL), start_button(BUTTON_DIR_PATH+START_BUTTON,980,680,160,40){
	init_Tiles();
	init_two_dynamic_tiles();
	option_interface = new Option_Interface; //call Option_Interface constructor

	//init_Towers();

}
Input_Interface::~Input_Interface() {

	//clear Tiles
	for (int x_tile = 0; x_tile < 24; x_tile++) {
		Tiles[x_tile].clear();
	}
	Tiles.clear();
	delete selected_tile;
	delete moving_tile;
	

	delete option_interface;

	Towers.clear();
	
}
void Input_Interface::init_Tiles(){
	Tiles.resize(24);
	for (int i = 0; i < 24; i++) {
		Tiles[i].resize(18);
	}

	fstream tile_data;
	tile_data.open(TILE_DIR_PATH + TILE_DATA, ios::in);

	for (int y_tile = 0; y_tile < 18; y_tile++) {
		for (int x_tile = 0; x_tile < 24; x_tile++) {
			Tiles[x_tile][y_tile] = new Tile(x_tile, y_tile); //call Tile constructor, load image texture

			//read tile data
			int can_set_tower;
			char comma;
			tile_data >> can_set_tower;
			tile_data >> comma;
			if (can_set_tower==1) {
				Tiles[x_tile][y_tile]->set_tile_state(LButton::ButtonState::BUTTON_MOUSE_OUT);
			}
			else if(can_set_tower==0){
				Tiles[x_tile][y_tile]->set_tile_state(LButton::ButtonState::BUTTON_CAN_NOT_USE);
			}
			else { cout << "tile_data load error" << endl; }
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

bool Input_Interface::player_require_build_fire_tower() {
	return (option_interface->opiton_buttons_select(Option_Interface::Option::BUILD_FIRE_TOWER));
}
bool Input_Interface::player_require_build_ice_tower() {
	return (option_interface->opiton_buttons_select(Option_Interface::Option::BUILD_ICE_TOWER));
}
bool Input_Interface::player_require_build_poison_tower() {
	return (option_interface->opiton_buttons_select(Option_Interface::Option::BUILD_POISON_TOWER));
}

bool Input_Interface::player_require_level_up() {
	return (option_interface->opiton_buttons_select(Option_Interface::Option::LEVEL_UP));
}
bool Input_Interface::player_require_level_down() {
	return (option_interface->opiton_buttons_select(Option_Interface::Option::LEVEL_DOWN));
}
bool Input_Interface::player_require_destroy() {
	return (option_interface->opiton_buttons_select(Option_Interface::Option::DESTROY_TOWER));
}

void Input_Interface::execute_build_fire_tower(){
	int tower_num = Towers.size();
	Towers.resize(tower_num + 1);
	Towers[tower_num] = new FireTower(1, selected_tile->get_x_tile_location(), selected_tile->get_y_tile_location());
	selected_tile->set_tower_lebel(tower_num); //lebel is used to refind the tower
}
void Input_Interface::execute_build_ice_tower() {
	int tower_num = Towers.size();
	Towers.resize(tower_num + 1);
	Towers[tower_num] = new IceTower(1, selected_tile->get_x_tile_location(), selected_tile->get_y_tile_location());
	selected_tile->set_tower_lebel(tower_num); //lebel is used to refind the tower
}
void Input_Interface::execute_build_poison_tower() {
	int tower_num = Towers.size();
	Towers.resize(tower_num + 1);
	Towers[tower_num] = new PoisonTower(1, selected_tile->get_x_tile_location(), selected_tile->get_y_tile_location());
	selected_tile->set_tower_lebel(tower_num); //lebel is used to refind the tower
}
void Input_Interface::execute_destroy_tower() {
	int tower_lebel = selected_tile->get_tower_lebel();
	int tower_num = Towers.size();
	if (tower_lebel == (tower_num - 1)) { //destroy the last tower
		delete Towers[tower_lebel];
		Towers.resize(tower_num - 1);
	}
	else {
		delete Towers[tower_lebel];
	}
	selected_tile->set_tower_lebel(-1); //0 is the first built tower 
}
void Input_Interface::execute_level_up_tower() {
	int previous_level = Towers[selected_tile->get_tower_lebel()]->get_tower_level();
	if (previous_level >= 1 && previous_level <= 3) {
		Towers[selected_tile->get_tower_lebel()]->set_tower_level(previous_level + 1);
	}
	//update the corresponding value
}
void Input_Interface::execute_level_down_tower() {
	int previous_level = Towers[selected_tile->get_tower_lebel()]->get_tower_level();
	if (previous_level >= 2 && previous_level <= 4) {
		Towers[selected_tile->get_tower_lebel()]->set_tower_level(previous_level - 1);
		//update the corresponding value
	}
}
void Input_Interface::option_button_response() {
	if (selected_tile != NULL) {
		if (player_require_build_fire_tower()) {
			execute_build_fire_tower();
		}
		else if (player_require_build_ice_tower()) {
			execute_build_ice_tower();
		}
		else if (player_require_build_poison_tower()) {
			execute_build_poison_tower();
		}
		else if (player_require_level_up()) {
			execute_level_up_tower();
		}
		else if (player_require_level_up()) {
			execute_level_down_tower();
		}
		else if (player_require_destroy()) {
			execute_destroy_tower();
		}
	}
}

void Input_Interface::render() {
	SDL_RenderClear(gRenderer);
	option_interface->render();
	render_tiles();
	render_towers();
	start_button.render();
}
void Input_Interface::render_tiles() {
	for (int x_tile = 0; x_tile < 24; x_tile++) {
		for (int y_tile = 0; y_tile < 18; y_tile++) {
			Tiles[x_tile][y_tile]->render();
		}
	}
}
void Input_Interface::render_towers() {
	for (int i = 0; i < Towers.size(); i++) {
		if (Towers[i] != NULL) {
			Towers[i]->render(); //call virtual funciton
		}
	}
}
//mouse
bool Input_Interface::mouse_in_map() {
	//Check if mouse is in map
	bool inside = true;

	//Mouse is left of the map
	if (mouse_x < 0)
	{
		inside = false;
	}
	//Mouse is right of the map
	else if (mouse_x > MAP_WIDTH)
	{
		inside = false;
	}
	//Mouse above the map
	else if (mouse_y < 0)
	{
		inside = false;
	}
	//Mouse below the map
	else if (mouse_y > MAP_HEIGHT)
	{
		inside = false;
	}
	return inside;
}
bool Input_Interface::mouse_in_option_interface() { //need to modify!!
	return !mouse_in_map();
}

void Input_Interface::draw() {
	SDL_RenderPresent(gRenderer);
}

void Input_Interface::tile_open_option_interface() {
	int tower_lebel = selected_tile->get_tower_lebel();

	if (tower_lebel == -1) {//no tower
		option_interface->get_option_buttons()[Option_Interface::Option::BUILD_FIRE_TOWER]->
			set_button_state(LButton::ButtonState::BUTTON_MOUSE_OUT);
		option_interface->get_option_buttons()[Option_Interface::Option::BUILD_ICE_TOWER]->
			set_button_state(LButton::ButtonState::BUTTON_MOUSE_OUT);
		option_interface->get_option_buttons()[Option_Interface::Option::BUILD_POISON_TOWER]->
			set_button_state(LButton::ButtonState::BUTTON_MOUSE_OUT);
		option_interface->get_option_buttons()[Option_Interface::Option::LEVEL_UP]->
			set_button_state(LButton::ButtonState::BUTTON_CAN_NOT_USE);
		option_interface->get_option_buttons()[Option_Interface::Option::LEVEL_DOWN]->
			set_button_state(LButton::ButtonState::BUTTON_CAN_NOT_USE);
		option_interface->get_option_buttons()[Option_Interface::Option::DESTROY_TOWER]->
			set_button_state(LButton::ButtonState::BUTTON_CAN_NOT_USE);
	}
	else {//there is a tower    //note:tower level 1,2,3,4
		int tower_level = Towers[tower_lebel]->get_tower_level();
		//Level up
		if (tower_level == 4) {
			option_interface->get_option_buttons()[Option_Interface::Option::LEVEL_UP]->
				set_button_state(LButton::ButtonState::BUTTON_CAN_NOT_USE);
		}
		else {
			option_interface->get_option_buttons()[Option_Interface::Option::LEVEL_UP]->
				set_button_state(LButton::ButtonState::BUTTON_MOUSE_OUT);
		}
		
		//Level down
		if (tower_level == 1) {
			option_interface->get_option_buttons()[Option_Interface::Option::LEVEL_DOWN]->
				set_button_state(LButton::ButtonState::BUTTON_CAN_NOT_USE);
		}
		else {
			option_interface->get_option_buttons()[Option_Interface::Option::LEVEL_DOWN]->
				set_button_state(LButton::ButtonState::BUTTON_MOUSE_OUT);
		}

		//destroy tower
		option_interface->get_option_buttons()[Option_Interface::Option::DESTROY_TOWER]->
			set_button_state(LButton::ButtonState::BUTTON_MOUSE_OUT);
		
	}

}
#endif // !_INPUT_INTERFACE_H
