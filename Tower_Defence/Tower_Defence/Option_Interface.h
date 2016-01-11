#pragma once
//#ifndef _OPTION_INTERFACE_H
//#define _OPTION_INTERFACE_H

#include "LButton.h"
#include "LTexture.h"


const string BUTTON_DIR_PATH = "..\\Project_resourses\\button\\";
const string FIRE_TOWER_BUTTON = "fire_tower_button.png";
const string ICE_TOWER_BUTTON = "ice_tower_button.png";
const string POISON_TOWER_BUTTON = "poison_tower_button.png";
const string LEVEL_UP_BUTTON = "level_up_button.png";
const string LEVEL_DOWN_BUTTON = "level_down_button.png";
const string DESTROY_BUTTON = "destroy_button.png";
const string EXPLAIN_TEXT = "explain_text.png";

//const string EXECUTE_BUTTON = "execute_button.png";

//rename the class as Option_Interface is better
class Option_Interface {
public:

	Option_Interface();
	~Option_Interface();

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
	//void button_reponse(); //打開option說明文件 或是execute
	void render(); //render all buttons
	//void load_buttons_texture(); //load in constructor
	void accept_event(SDL_Event &e); //LButton::detect_mouse_Event for each button
	bool opiton_buttons_select(Option _option);
	vector<OptionButton*>& get_option_buttons();
	void set_explain_text_texture_clip_list();

	//load texture??
	

private:
	//OptionButton* execute_button;
	vector<OptionButton*> option_buttons;  //option_button[option]
									 //ButtonState tile_button_state;
	LTexture* explain_text_texture;
	vector<SDL_Rect*> explain_text_texture_clip_list;
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

Option_Interface::Option_Interface(){
	set_explain_text_texture_clip_list();

	explain_text_texture = new LTexture;
	explain_text_texture->loadFromFile(BUTTON_DIR_PATH + EXPLAIN_TEXT);

	option_buttons.resize(TOTAL_OPTIONS);
	option_buttons[LEVEL_UP] = new OptionButton(BUTTON_DIR_PATH + LEVEL_UP_BUTTON, 0, 760, 160, 40);
	option_buttons[LEVEL_DOWN] = new OptionButton(BUTTON_DIR_PATH + LEVEL_DOWN_BUTTON, 160, 760, 160, 40);
	option_buttons[DESTROY_TOWER] = new OptionButton(BUTTON_DIR_PATH + DESTROY_BUTTON, 320, 760, 160, 40);
	option_buttons[BUILD_FIRE_TOWER] = new OptionButton(BUTTON_DIR_PATH + FIRE_TOWER_BUTTON, 0, 720, 160, 40);
	option_buttons[BUILD_ICE_TOWER] = new OptionButton(BUTTON_DIR_PATH + ICE_TOWER_BUTTON, 160, 720, 160, 40);
	option_buttons[BUILD_POISON_TOWER] = new OptionButton(BUTTON_DIR_PATH + POISON_TOWER_BUTTON, 320, 720, 160, 40);

}
Option_Interface::~Option_Interface() {

}

//void Option_Button::load_buttons_texture() {
//	execute_button->load_button_state_texture();
//
//	option_buttons.resize(TOTAL_OPTIONS);
//	for (int _option = LEVEL_UP; _option < TOTAL_OPTIONS; _option++) {
//		option_buttons[_option]->load_button_state_texture();
//	}
//}
void Option_Interface::render() {
	//execute_button->render();

	for (int _option = (int)LEVEL_UP; _option < (int)TOTAL_OPTIONS; _option++) {
		option_buttons[_option]->render();
	}

	//說明文件
	for (int _option = (int)LEVEL_UP; _option < (int)TOTAL_OPTIONS; _option++) {
		if (option_buttons[_option]->get_button_state() == LButton::ButtonState::BUTTON_MOUSE_OVER ||
			option_buttons[_option]->get_button_state() == LButton::ButtonState::BUTTON_MOUSE_DOWN) {
			explain_text_texture->render(480, 720, explain_text_texture_clip_list[_option]);
		}
	}
}

void Option_Interface::accept_event(SDL_Event &e) {
	//execute_button->detect_mouse_Event(&e);

	for (int _option = (int)LEVEL_UP; _option < (int)TOTAL_OPTIONS; _option++) {
		option_buttons[_option]->detect_mouse_Event(&e);
	}


}

bool Option_Interface::opiton_buttons_select(Option _option) {
	return option_buttons[_option]->get_button_state() == LButton::ButtonState::BUTTON_MOUSE_DOWN;
}

vector<OptionButton*>& Option_Interface::get_option_buttons() {
	return option_buttons;
}

void Option_Interface::set_explain_text_texture_clip_list() {
	explain_text_texture_clip_list.resize((int)TOTAL_OPTIONS);


	for (int _option = 0; _option < (int)TOTAL_OPTIONS; _option++) {
		explain_text_texture_clip_list[_option] = new SDL_Rect;
		explain_text_texture_clip_list[_option]->x = _option*520;
		explain_text_texture_clip_list[_option]->y = 0;
		explain_text_texture_clip_list[_option]->w = 520;
		explain_text_texture_clip_list[_option]->h = 80;
	}


}
//#endif // !_OPTION_INTERFACE_H
