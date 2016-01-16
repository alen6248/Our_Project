//#pragma once
#ifndef _POISON_TOWER_H
#define _POISON_TOWER_H

#include <vector>
#include <iostream>
#include <cstring>
#include "LTexture.h"
#include "Abstract_Tower.h"

extern const string TOWER_DIR_PATH;
extern const string POISON_TOWER_IMAGE;


class PoisonTower :public Abstract_Tower {
public:
	PoisonTower(int level, int x_location, int y_location, TowerType _tower_type, int _special_attack_span, int _special_attack_damage );//constructor
	~PoisonTower();//destructor
	virtual void render();

	//const string const level_to_name(int level);
	virtual void load_tower_texture(SDL_BlendMode blending, Uint8 alpha);



private:
	//string name;
	//LTexture tower_texture;

	//poison 

};

PoisonTower::PoisonTower(int level, int x_tile_location, int y_tile_location, TowerType _tower_type, int _special_attack_span, int _special_attack_damage ) :
	Abstract_Tower(level, x_tile_location, y_tile_location)
{
	set_tower_type(_tower_type);
	set_special_attack_span(_special_attack_span);
	set_special_attack_damage(_special_attack_damage);
	load_tower_texture(SDL_BLENDMODE_BLEND, 255);
}
PoisonTower::~PoisonTower() {}
void PoisonTower::load_tower_texture(SDL_BlendMode blending, Uint8 alpha) {
	get_tower_texture()->loadFromFile(TOWER_DIR_PATH + POISON_TOWER_IMAGE);
	get_tower_texture()->setBlendMode(blending);
	get_tower_texture()->setAlpha(alpha);

}
void PoisonTower::render() {
	get_tower_texture()->render(get_tower_width_tile_location()*TILE_WIDTH,
		get_tower_height_tile_location()*TILE_WIDTH,
		Abstract_Tower::get_tower_image_clip_list()[get_tower_level()]);
}



#endif // !_FIRE_TOWER_H
