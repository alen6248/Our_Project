//#pragma once

#ifndef _TILE_H
#define _TILE_H
//#include "Tile_Option_Button.h"
#include "LButton.h"
extern const int TILE_WIDTH ;

class Tile {
public:


	Tile( int x_tile_location, int y_tile_location); //constructor
	~Tile(); //destructor
	void load(); //load button texture
	void render(); //render button texture

	//button
	LButton* get_tile_button();

	//position
	void set_x_tile_location(int _x_tile);
	void set_y_tile_location(int _y_tile);
	void set_x_pixel_location(int _x_pixel);
	void set_y_pixel_location(int _y_pixel);

	int get_x_tile_location() const;
	int get_y_tile_location() const;
	int get_x_pixel_location() const;
	int get_y_pixel_location() const;



private:
	LButton* tile_button;


	int x_tile_location;
	int y_tile_location;
	int x_pixel_location;
	int y_pixel_location;


};
Tile::Tile(int _x_tile_location,int _y_tile_location)
{
	x_tile_location = _x_tile_location;
	y_tile_location = _y_tile_location;
	x_pixel_location = _x_tile_location*TILE_WIDTH;
	y_pixel_location = _y_tile_location*TILE_WIDTH;


	tile_button= new LButton("", x_pixel_location, y_pixel_location, TILE_WIDTH, TILE_WIDTH);
	load();
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




#endif // !_TILE_H
