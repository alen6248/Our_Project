//#pragma once

#ifndef _TILE_H
#define _TILE_H
//#include "Tile_Option_Button.h"
#include "LButton.h"

extern const int TILE_WIDTH ;

const string TILE_DIR = "F:\\Project_resourses\\tile\\";
const string TILE_BUTTON_IMAGE = "tile_button.png";

class Tile {
public:

	//Tile() {}
	Tile( int x_tile_location, int y_tile_location); //constructor
	//use default copy constructor
	//use default operator =
	~Tile(); //destructor
	void load(); //load button texture
	void render(); //render button texture

	//button
	LButton* get_tile_button(); /*//change to the derived class TileButton*/

	//set Tile_state
	void set_tile_state(LButton::ButtonState _new_state);
	LButton::ButtonState get_tile_state()const;

	//position
	void set_x_tile_location(int _x_tile);
	void set_y_tile_location(int _y_tile);
	void set_x_pixel_location(int _x_pixel);
	void set_y_pixel_location(int _y_pixel);

	int get_x_tile_location() const;
	int get_y_tile_location() const;
	int get_x_pixel_location() const;
	int get_y_pixel_location() const;

	//tower_lebel
	int get_tower_lebel()const;
	void set_tower_lebel(int new_lebel);

private:
	LButton* tile_button;

	int x_tile_location;
	int y_tile_location;
	int x_pixel_location;
	int y_pixel_location;

	int tower_lebel; //lebel is used to refind the tower
};

Tile::Tile(int _x_tile_location,int _y_tile_location)
{
	x_tile_location = _x_tile_location;
	y_tile_location = _y_tile_location;
	x_pixel_location = _x_tile_location*TILE_WIDTH;
	y_pixel_location = _y_tile_location*TILE_WIDTH;
	tower_lebel = -1; //no tower: -1

	tile_button= new LButton(TILE_DIR+ TILE_BUTTON_IMAGE, x_pixel_location, y_pixel_location, TILE_WIDTH, TILE_WIDTH);
	//load(); //load in LButton constructor
}
Tile::~Tile() {
	delete tile_button;
}


void Tile::load() {
	tile_button->load_button_state_texture();
}

void Tile::render() {
	tile_button->render();
}
//button
LButton* Tile::get_tile_button() {
	return tile_button;
}

//position
void Tile::set_x_tile_location(int _x_tile) {
	x_tile_location = _x_tile;
}
void Tile::set_y_tile_location(int _y_tile) {
	y_tile_location = _y_tile;
}
void Tile::set_x_pixel_location(int _x_pixel) {
	x_pixel_location = _x_pixel;
}
void Tile::set_y_pixel_location(int _y_pixel) {
	y_pixel_location = _y_pixel;
}
int Tile::get_x_tile_location() const {
	return x_tile_location;
}
int Tile::get_y_tile_location() const {
	return y_tile_location;
}
int Tile::get_x_pixel_location() const {
	return x_pixel_location;
}
int Tile::get_y_pixel_location() const {
	return y_pixel_location;
}

//tower_lebel
int Tile::get_tower_lebel()const{
	return tower_lebel;
}
void Tile::set_tower_lebel(int new_lebel) {
	tower_lebel = new_lebel;
}

//button state
void Tile::set_tile_state(LButton::ButtonState _new_state) {
	tile_button->set_button_state(_new_state);
}
LButton::ButtonState Tile::get_tile_state()const {
	return tile_button->get_button_state();
}
#endif // !_TILE_H
