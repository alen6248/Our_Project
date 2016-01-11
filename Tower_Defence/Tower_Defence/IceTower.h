//#pragma once
#ifndef _ICE_TOWER_H
#define _ICE_TOWER_H

#include <vector>
#include <iostream>
#include <cstring>
#include "LTexture.h"
#include "Abstract_Tower.h"

extern const string TOWER_DIR_PATH;
extern const string ICE_TOWER_IMAGE;


class IceTower :public Abstract_Tower {
public:
	IceTower(int level, int x_location, int y_location);//constructor
	~IceTower();//destructor
	virtual void render();

	//const string const level_to_name(int level);
	virtual void load_tower_texture(SDL_BlendMode blending, Uint8 alpha);



private:
	//string name;
	//LTexture tower_texture;
	
	//frizing

};

IceTower::IceTower(int level, int x_tile_location, int y_tile_location) :
	Abstract_Tower(level, x_tile_location, y_tile_location)
{
	load_tower_texture(SDL_BLENDMODE_BLEND, 255);
	set_attack_range(200);
}
IceTower::~IceTower() {}
void IceTower::load_tower_texture(SDL_BlendMode blending, Uint8 alpha) {
	get_tower_texture()->loadFromFile(TOWER_DIR_PATH + ICE_TOWER_IMAGE);
	get_tower_texture()->setBlendMode(blending);
	get_tower_texture()->setAlpha(alpha);

}
void IceTower::render() {
	get_tower_texture()->render(get_tower_width_tile_location()*TILE_WIDTH,
		get_tower_height_tile_location()*TILE_WIDTH,
		Abstract_Tower::get_tower_image_clip_list()[get_tower_level()]);
}


#endif // !_ICE_TOWER_H