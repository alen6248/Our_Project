//#pragma once

#ifndef _ABSTRACT_TOWER_H
#define _ABSTRACT_TOWER_H

#include <vector>
#include <iostream>
#include <cstring>
#include "LTexture.h"


using namespace std;

//const string TOWER_DIR_PATH = "F:\\Project_resourses\\tower\\";
const string TOWER_DIR_PATH = "..\\Project_resourses\\tower\\";
const string FIRE_TOWER_IMAGE = "fire_tower.png";
const string ICE_TOWER_IMAGE = "ice_tower.png";
const string POISON_TOWER_IMAGE = "poison_tower.png";

enum TowerType {
	FIRE_TOWER,
	ICE_TOWER,
	POISON_TOWER,
	TOTAL_TOWER_TYPE
};

class Abstract_Tower {
public:

	Abstract_Tower(int level, int x_tile_location, int y_tile_location); //constructor
	Abstract_Tower(Abstract_Tower&);//deep copy constructor
	~Abstract_Tower(); //destructor

	static void set_tower_number(int tow_num);
	static vector<SDL_Rect*>& get_tower_image_clip_list();
	static void set_tower_image_clip_list();

	 //tower_texture
	LTexture* get_tower_texture() const;
	virtual void load_tower_texture(SDL_BlendMode blending, Uint8 alpha)=0; //pure virtual function
	virtual void render()=0; //pure virtual function

	//location
	int get_tower_width_tile_location() const;
	int get_tower_height_tile_location() const;
	int get_tower_width_pixel_location() const;
	int get_tower_height_pixel_location() const;

	//level
	int get_tower_level() const;
	void set_tower_level(int new_level);

	//attack_range
	float get_attack_range() const;
	void set_attack_range(float new_range);

	//attack_damage
	float get_attack_damage() const;
	void set_attack_damage(float new_damege);

	//attack_cd
	float get_attack_cd() const;
	void set_attack_cd(float new_cd);

	//Tower_type
	TowerType get_tower_type();
	void set_tower_type(TowerType _tower_type);

	//Special attack
	int get_special_attack_span();
	void set_special_attack_span(int _special_attack_span);
	int get_special_attack_damage();
	void set_special_attack_damage(int _special_attack_damage);

protected:

private:
	//vector<int> build_money;  //move to derived tower's static const member
	//build_money[1] is the money needed to build the tower   
	//build_money[2] is the money needed to levelup to level 2
	static int tower_number; //the total number of towers  //need to be written into main.cpp
	static vector<SDL_Rect*> tower_image_clip_list;

	const int tower_width_tile_location;//location measured in tile
	const int tower_height_tile_location;
	const int tower_width_pixel_location;//location measured in pixel
	const int tower_height_pixel_location;

	//tower type
	TowerType tower_type;

	//special attack
	int special_attack_span;
	int special_attack_damage;

	int tower_level; //level: 1,2,3,4
	float attack_range;
	int attack_damage; 
	int attack_cd; //the time length between attacks //unit : frame

	//int lebel; //the lebel of this tower
	

	LTexture* tower_texture;  //tentatively put this in public 

	//bool can_attack; //目前是否可以攻擊 ?  可以為1
	//vector<Attack_Target&> tow_att_list; //該塔在不同時間的攻擊目標
};



Abstract_Tower::Abstract_Tower(int level, int x_tile_location, int y_tile_location) :
	tower_level(level), tower_width_tile_location(x_tile_location), tower_height_tile_location(y_tile_location),  //initialize tile and pixel location
	tower_width_pixel_location(tower_width_tile_location*TILE_WIDTH), tower_height_pixel_location(tower_height_tile_location*TILE_WIDTH) {
	tower_texture = new LTexture;
}
Abstract_Tower::Abstract_Tower(Abstract_Tower& that):
	tower_level(that.tower_level), tower_width_tile_location(that.tower_width_tile_location),
	tower_height_tile_location(that.tower_height_tile_location), tower_width_pixel_location(tower_width_tile_location*TILE_WIDTH),
	tower_height_pixel_location(tower_height_tile_location*TILE_WIDTH), attack_cd(that.attack_cd),attack_damage(that.attack_damage),
	attack_range(that.attack_range)
{
	tower_texture = new LTexture;
	*tower_texture = *(that.tower_texture);


}
Abstract_Tower::~Abstract_Tower() { //destructor
	tower_texture->free();
}
void Abstract_Tower::set_tower_number(int tow_num) {
	tower_number = tow_num;
}
void Abstract_Tower::set_tower_image_clip_list(){  //set static member
	tower_image_clip_list.resize(5); //level:1,2,3,4, exclusive of 0

	for (int i = 1; i < 5; i++) { //start from 1
		tower_image_clip_list[i] = new SDL_Rect;
		tower_image_clip_list[i]->x = (i - 1)*TILE_WIDTH;
		tower_image_clip_list[i]->y = 0;
		tower_image_clip_list[i]->w = TILE_WIDTH;
		tower_image_clip_list[i]->h = TILE_WIDTH;
	}
}
vector<SDL_Rect*>& Abstract_Tower::get_tower_image_clip_list() {
	return tower_image_clip_list;
}
LTexture* Abstract_Tower::get_tower_texture() const {
	return tower_texture;
}
int Abstract_Tower::get_tower_width_tile_location() const {
	return tower_width_tile_location;
}
int Abstract_Tower::get_tower_height_tile_location() const {
	return tower_height_tile_location;
}
int Abstract_Tower::get_tower_width_pixel_location() const {
	return tower_width_pixel_location;
}
int Abstract_Tower::get_tower_height_pixel_location() const {
	return tower_height_pixel_location;
}
int Abstract_Tower::get_tower_level() const {
	return tower_level;
}
void Abstract_Tower::set_tower_level(int new_level) {
	tower_level = new_level;
}
float Abstract_Tower::get_attack_range() const {
	return attack_range;
}
void Abstract_Tower::set_attack_range(float new_range) {
	attack_range = new_range;
}
float Abstract_Tower::get_attack_damage() const {
	return attack_damage;
}
void Abstract_Tower::set_attack_damage(float new_damege) {
	attack_damage = new_damege;
}
float Abstract_Tower::get_attack_cd() const {
	return attack_cd;
}
void Abstract_Tower::set_attack_cd(float new_cd) {
	attack_cd = new_cd;
}
//Tower_type
TowerType Abstract_Tower::get_tower_type() {
	return tower_type;
}
void Abstract_Tower::set_tower_type(TowerType _tower_type) {
	tower_type = _tower_type;
}
//Special attack
int Abstract_Tower::get_special_attack_span() {
	return special_attack_span;
}
void Abstract_Tower::set_special_attack_span(int _special_attack_span) {
	special_attack_span = _special_attack_span;
}
int Abstract_Tower::get_special_attack_damage() {
	return special_attack_damage;
}
void Abstract_Tower::set_special_attack_damage(int _special_attack_damage) {
	special_attack_damage = _special_attack_damage;
}






#endif // !_ABSTRACT_TOWER_H
