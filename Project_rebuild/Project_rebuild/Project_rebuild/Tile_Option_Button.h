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
		LEVEL_UP ,
		LEVEL_DOWN ,
		DESTROY_TOWER ,
		BUILD_FIRE_TOWER ,
		BUILD_ICE_TOWER ,
		BUILD_POISON_TOWER ,
		TOTAL_OPTIONS 
	};

	//ButtonState detect_button_event(SDL_Event* e);
	void button_reponse();
	void render();
	void load_buttons_texture();
	void accept_event(SDL_Event &e);




private:
	LButton execute_button;
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

Tile_Option_Button::Tile_Option_Button() {


}
Tile_Option_Button::~Tile_Option_Button() {

}

void Tile_Option_Button::load_buttons_texture() {
	execute_button.load_button_state_texture();

	option_buttons.resize(TOTAL_OPTIONS);
	for (int _option = LEVEL_UP; _option < TOTAL_OPTIONS; _option++) {
		option_buttons[_option].load_button_state_texture();
	}
}
void Tile_Option_Button::render() {
	execute_button.render();

	for (int _option = LEVEL_UP; _option < TOTAL_OPTIONS; _option++) {
		option_buttons[_option].render();
	}
}

void Tile_Option_Button::accept_event(SDL_Event &e) {
	execute_button.detect_mouse_Event(&e);

	for (int _option = LEVEL_UP; _option < TOTAL_OPTIONS; _option++) {
		option_buttons[_option].detect_mouse_Event(&e);
	}


}

void Tile_Option_Button::button_reponse() {

	//tile_button
	if (execute_button.get_button_state() == LButton::ButtonState::BUTTON_MOUSE_OUT) {

	}
	else if(execute_button.get_button_state() == LButton::ButtonState::BUTTON_MOUSE_OVER) {

	}
	else if (execute_button.get_button_state() == LButton::ButtonState::BUTTON_MOUSE_DOWN) {

	}


	//LEVEL UP
	if (option_buttons[LEVEL_UP].get_button_state() == LButton::ButtonState::BUTTON_MOUSE_OUT) {

	}
	else if (option_buttons[LEVEL_UP].get_button_state() == LButton::ButtonState::BUTTON_MOUSE_OUT) {

	}
	else if (option_buttons[LEVEL_UP].get_button_state() == LButton::ButtonState::BUTTON_MOUSE_OUT) {

	}

	//LEVEL DOWN
	if (option_buttons[LEVEL_DOWN].get_button_state() == LButton::ButtonState::BUTTON_MOUSE_OUT) {

	}
	else if (option_buttons[LEVEL_DOWN].get_button_state() == LButton::ButtonState::BUTTON_MOUSE_OUT) {

	}
	else if (option_buttons[LEVEL_DOWN].get_button_state() == LButton::ButtonState::BUTTON_MOUSE_OUT) {

	}

	//DESTROY TOWER
	if (option_buttons[DESTROY_TOWER].get_button_state() == LButton::ButtonState::BUTTON_MOUSE_OUT) {

	}
	else if (option_buttons[DESTROY_TOWER].get_button_state() == LButton::ButtonState::BUTTON_MOUSE_OUT) {

	}
	else if (option_buttons[DESTROY_TOWER].get_button_state() == LButton::ButtonState::BUTTON_MOUSE_OUT) {

	}

	//BUILD FIRETOWER
	if (option_buttons[BUILD_FIRE_TOWER].get_button_state() == LButton::ButtonState::BUTTON_MOUSE_OUT) {

	}
	else if (option_buttons[BUILD_FIRE_TOWER].get_button_state() == LButton::ButtonState::BUTTON_MOUSE_OUT) {

	}
	else if (option_buttons[BUILD_FIRE_TOWER].get_button_state() == LButton::ButtonState::BUTTON_MOUSE_OUT) {

	}

	//BUILD ICE_TOWER
	if (option_buttons[BUILD_ICE_TOWER].get_button_state() == LButton::ButtonState::BUTTON_MOUSE_OUT) {

	}
	else if (option_buttons[BUILD_ICE_TOWER].get_button_state() == LButton::ButtonState::BUTTON_MOUSE_OUT) {

	}
	else if (option_buttons[BUILD_ICE_TOWER].get_button_state() == LButton::ButtonState::BUTTON_MOUSE_OUT) {

	}


	//BUILD POISON_TOWER
	if (option_buttons[BUILD_POISON_TOWER].get_button_state() == LButton::ButtonState::BUTTON_MOUSE_OUT) {

	}
	else if (option_buttons[BUILD_POISON_TOWER].get_button_state() == LButton::ButtonState::BUTTON_MOUSE_OUT) {

	}
	else if (option_buttons[BUILD_POISON_TOWER].get_button_state() == LButton::ButtonState::BUTTON_MOUSE_OUT) {

	}



}






#endif // !TILE_OPTION_BUTTON
