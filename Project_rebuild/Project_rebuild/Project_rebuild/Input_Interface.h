//#pragma once
#ifndef _INPUT_INTERFACE_H
#define _INPUT_INTERFACE_H

#include "Tile.h"
#include "Abstract_Tower.h"
#include "FireTower.h"
#include "Tile_Option_Button.h"
#include <iostream>
#include <vector>


class Input_Interface{
public:
	Input_Interface();
	~Input_Interface();





private:

	vector<vector<Tile*>> Tiles;
	vector<Abstract_Tower*> Towers;




};

Input_Interface::Input_Interface() {

	Tiles.resize(24);
	for (int i = 0; i < 24; i++) {
		Tiles[i].resize(18);
	}
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 18; j++) {
			Tiles[i][j] = new Tile;
		}
	}

}















#endif // !_INPUT_INTERFACE_H
