#pragma once

#ifndef _TOWER_H
#define _TOWER_H



//====================設計=========================================
//Enemy 參數紀錄
//Enemy類別
//StrongEnemy  FastEnemy  BossEnemy  三種不同敵人


//=================================================================




/*****************問題******************************************/
//塔升級時是否改變所占面積?   //暫定不改變
//FireTower是否改成攻擊範圍360度?  或是1對1攻擊?
//FireTower 升級前1對1,升級後範圍攻擊?
//Tower賣掉時可將錢全數回歸，因為遊戲重點在最佳化問題

/***************************************************************/

#include "Enemy.h"
#include "Result_Loader.h"
#include <vector>
#include <iostream>
#include "Map.h"
#include "LTexture.h"
#include <cstring>


extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int TILE_WIDTH;
extern const int WIDTH_TILE_NUMBER;
extern const int HEIGHT_TILE_NUMBER;

const string TOWER_DIR_PATH = "F:\\Project_resourses\\tower\\";
const string FIRE_TOWER_IMAGE = "fire_tower.png";
const string ICE_TOWER_IMAGE = "ice_tower.png";
const string POISON_TOWER_IMAGE = "poison_tower.png";

using namespace std;

class Tower {

	public:
		virtual void load_tower_texture(int tower_level, int tile_order, int width_number, int height_number, SDL_BlendMode blending, Uint8 alpha);
		SDL_Texture* get_tower_texture_ptr();
		//vector<Attack_Target&> tow_att_list; //該塔在不同時間的攻擊目標
		Tower();
		Tower(int level, int x_location, int y_location);
		~Tower();
		static int tow_num; //塔的總數量
		LTexture tower_texture;
		friend class Map;
	
		//int lebel; //編號
		int tower_level;
		float attack_range; //攻擊範圍
		int tower_width_tile_location;//tile位置
		int tower_height_tile_location;
		int tower_width_pixel_location;//pixel位置
		int tower_height_pixel_location;

		static const int tile_width; //塔的寬度  40*40 pixels
		//int y_width;
		float attack_cd; //攻擊間隔時間
		float attack_damage; //攻擊傷害
		vector<int> build_money; //build_money[0]為建造塔所需錢   build_money[1]為第一次升級  以此類推
		//bool can_attack; //目前是否可以攻擊 ?  可以為1
protected:  //optimize the class later
	private:

};
const int Tower::tile_width = TILE_WIDTH;

Tower::Tower() {

}
Tower::Tower(int level, int x_location, int y_location) :
	tower_level(level), tower_width_tile_location(x_location), tower_height_tile_location(y_location),  //initialize tile and pixel location
	tower_width_pixel_location(tower_width_tile_location*TILE_WIDTH),tower_height_pixel_location(tower_height_tile_location*TILE_WIDTH) {

}
Tower::~Tower(){
	build_money.clear();
}
void Tower::load_tower_texture(int tower_level, int tile_order, int width_number, int height_number, SDL_BlendMode blending, Uint8 alpha) {

}
SDL_Texture* Tower::get_tower_texture_ptr() {
	return tower_texture.mTexture;
}

class FireTower:public Tower {
public:
	FireTower(int level, int x_location, int y_location);
	~FireTower();
	//const string const level_to_name(int level);

	virtual void load_tower_texture(int tower_level, int tile_order, int width_number, int height_number, SDL_BlendMode blending, Uint8 alpha);
	virtual SDL_Texture* get_tower_texture_ptr();
	LTexture& get_tower_LTexture();


private:
		//string name;
		//LTexture tower_texture;
		 

};

class IceTower :public Tower {
public:
	IceTower(int level, int x_location, int y_location);
	~IceTower();
	//const string const level_to_name(int level);
	virtual void load_tower_texture(int tower_level, int tile_order, int width_number, int height_number, SDL_BlendMode blending, Uint8 alpha);
	virtual SDL_Texture* get_tower_texture_ptr();
	LTexture& get_tower_LTexture();
private:
	//string name;
	//LTexture tower_texture;
	
};

class PoisonTower :public Tower {
public:
	PoisonTower(int level, int x_location, int y_location);
	~PoisonTower();
	//const string const level_to_name(int level);
	virtual void load_tower_texture(int tower_level, int tile_order, int width_number, int height_number, SDL_BlendMode blending, Uint8 alpha);
	virtual SDL_Texture* get_tower_texture_ptr();
	LTexture& get_tower_LTexture();
private:
	//string name;
	//LTexture tower_texture;
};


FireTower::FireTower(int level,int x_location,int y_location):
	Tower(level,x_location,y_location){ //Constructor

}
FireTower::~FireTower() {
	
}
void FireTower::load_tower_texture(int tower_level,int tile_order,int width_number,int height_number, SDL_BlendMode blending, Uint8 alpha) {
	//load tower image
	tower_texture.load_tower(TOWER_DIR_PATH + FIRE_TOWER_IMAGE, width_number, height_number, LTexture::tower_image_clip_list[tower_level], blending, alpha);
	
	////set Texture mWidth and mHeight
	//tower_texture.mWidth = TOWER_IMAGE_WIDTH;
	//tower_texture.mHeight= TOWER_IMAGE_HEIGHT;

	//set tower level
	Tower::tower_level = tower_level;

		
}
SDL_Texture* FireTower::get_tower_texture_ptr() {
	return tower_texture.mTexture;
}
LTexture& FireTower::get_tower_LTexture() {
	return tower_texture; 
}




IceTower::IceTower(int level, int x_location, int y_location) :
	Tower(level, x_location, y_location) { //Constructor

}
IceTower::~IceTower() {

}
void IceTower::load_tower_texture(int tower_level, int tile_order, int width_number, int height_number, SDL_BlendMode blending, Uint8 alpha) {
	//load tower image
	tower_texture.load_tower(TOWER_DIR_PATH + FIRE_TOWER_IMAGE, width_number, height_number, LTexture::tower_image_clip_list[tower_level], blending, alpha);

	////set Texture mWidth and mHeight
	//tower_texture.mWidth = TOWER_IMAGE_WIDTH;
	//tower_texture.mHeight= TOWER_IMAGE_HEIGHT;

	//set tower level
	Tower::tower_level = tower_level;


}
SDL_Texture* IceTower::get_tower_texture_ptr() {
	return tower_texture.mTexture;
}
LTexture& IceTower::get_tower_LTexture() {
	return tower_texture;
}




PoisonTower::PoisonTower(int level, int x_location, int y_location) :
	Tower(level, x_location, y_location) { //Constructor

}
PoisonTower::~PoisonTower() {

}
void PoisonTower::load_tower_texture(int tower_level, int tile_order, int width_number, int height_number, SDL_BlendMode blending, Uint8 alpha) {
	//load tower image
	tower_texture.load_tower(TOWER_DIR_PATH + FIRE_TOWER_IMAGE, width_number, height_number, LTexture::tower_image_clip_list[tower_level], blending, alpha);

	////set Texture mWidth and mHeight
	//tower_texture.mWidth = TOWER_IMAGE_WIDTH;
	//tower_texture.mHeight= TOWER_IMAGE_HEIGHT;

	//set tower level
	Tower::tower_level = tower_level;


}
SDL_Texture* PoisonTower::get_tower_texture_ptr() {
	return tower_texture.mTexture;
}
LTexture& PoisonTower::get_tower_LTexture() {
	return tower_texture;
}


#endif 