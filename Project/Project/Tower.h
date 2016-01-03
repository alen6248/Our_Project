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
//#include "Result_Loader.h"
#include <vector>
#include <iostream>
#include "Map.h"
#include "LTexture.h"
#include <cstring>

//Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int TILE_WIDTH;
extern const int WIDTH_TILE_NUMBER;
extern const int HEIGHT_TILE_NUMBER;

//files path
const string TOWER_DIR_PATH = "F:\\Project_resourses\\tower\\";
const string FIRE_TOWER_IMAGE = "fire_tower.png";
const string ICE_TOWER_IMAGE = "ice_tower.png";
const string POISON_TOWER_IMAGE = "poison_tower.png";

using namespace std;

class Tower {
	public:
		//Tower(); //default constructor
		Tower(int level, int x_location, int y_location); //constructor
		~Tower(); //destructor
		//need copy constructor?

		static int tow_num; //the total number of towers**  //need to be written into main.cpp
		static const int tile_width; //40*40 pixels	 //need to be written into main.cpp

		//tower_texture
		
		LTexture* get_tower_texture_ptr() const;
		virtual void load_tower_texture(int tower_level, int tile_order, int width_number, int height_number,
			 SDL_BlendMode blending = SDL_BLENDMODE_BLEND, Uint8 alpha = 255);
		
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
		LTexture* tower_texture;  //tentatively put this in public 
		
		friend class Map;
	protected:  
		
	private:
		vector<int> build_money; 
		//build_money[1] is the money needed to build the tower   
		//build_money[2] is the money needed to levelup to level 2

		float attack_cd; //the time length between attacks
		float attack_damage;

		const int tower_width_tile_location;//location measured in tile
		const int tower_height_tile_location;

		const int tower_width_pixel_location;//location measured in pixel
		const int tower_height_pixel_location;

		//int lebel; //the lebel of this tower
		int tower_level; //level: 1,2,3,4
		float attack_range;
		
		//bool can_attack; //目前是否可以攻擊 ?  可以為1
		//vector<Attack_Target&> tow_att_list; //該塔在不同時間的攻擊目標
};
const int Tower::tile_width = TILE_WIDTH; //set static const member value

Tower::Tower(int level, int x_location, int y_location) :
	tower_level(level), tower_width_tile_location(x_location), tower_height_tile_location(y_location),  //initialize tile and pixel location
	tower_width_pixel_location(tower_width_tile_location*TILE_WIDTH),tower_height_pixel_location(tower_height_tile_location*TILE_WIDTH){
	tower_texture = new LTexture;
}
Tower::~Tower(){
	build_money.clear();
	tower_texture->free();
}
void Tower::load_tower_texture(int tower_level, int tile_order, int width_number, int height_number,
	 SDL_BlendMode blending, Uint8 alpha) {

}
LTexture* Tower::get_tower_texture_ptr() const {
	return tower_texture;
}


int Tower::get_tower_width_tile_location() const {
	return tower_width_tile_location;
}
int Tower::get_tower_height_tile_location() const {
	return tower_height_tile_location;
}
int Tower::get_tower_width_pixel_location() const {
	return tower_width_pixel_location;
}
int Tower::get_tower_height_pixel_location() const {
	return tower_height_pixel_location;
}
int Tower::get_tower_level() const {
	return tower_level;
}
void Tower::set_tower_level(int new_level) {
	tower_level = new_level;
}
float Tower::get_attack_range() const {
	return attack_range;
}
void Tower::set_attack_range(float new_range) {
	attack_range = new_range;
}






/*derived class declaration*/
class FireTower:public Tower {
public:
	FireTower(int level, int x_location, int y_location);//constructor
	~FireTower();//destructor
	//const string const level_to_name(int level);
	virtual void load_tower_texture(int tower_level, int tile_order, int width_number, int height_number
		, SDL_BlendMode blending= SDL_BLENDMODE_BLEND, Uint8 alpha=255);
	//virtual LTexture* get_tower_texture_ptr()const;
	//LTexture& get_tower_LTexture();


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
	//virtual SDL_Texture* get_tower_texture_ptr();
	//LTexture& get_tower_LTexture();
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
	//virtual SDL_Texture* get_tower_texture_ptr();
	//LTexture& get_tower_LTexture();
private:
	//string name;
	//LTexture tower_texture;
};
/*end of derived class declaration*/








FireTower::FireTower(int level,int x_location,int y_location):
	Tower(level,x_location,y_location){ //Constructor

}
FireTower::~FireTower() {
	
}
void FireTower::load_tower_texture(int level,int tile_order,int width_number,int height_number, SDL_BlendMode blending, Uint8 alpha) {
	//load tower image
	tower_texture->load_tower(TOWER_DIR_PATH + FIRE_TOWER_IMAGE, width_number, height_number,
				LTexture::tower_image_clip_list[level], blending, alpha);
	
	////set Texture mWidth and mHeight
	//tower_texture.mWidth = TOWER_IMAGE_WIDTH;
	//tower_texture.mHeight= TOWER_IMAGE_HEIGHT;

	//set tower level
	set_tower_level(level);

		
}
//LTexture* Tower::get_tower_texture_ptr() const;

//LTexture& FireTower::get_tower_LTexture() {
//	return *tower_texture; 
//}




IceTower::IceTower(int level, int x_location, int y_location) :
	Tower(level, x_location, y_location) { //Constructor

}
IceTower::~IceTower() {

}
void IceTower::load_tower_texture(int level, int tile_order, int width_number, int height_number, SDL_BlendMode blending, Uint8 alpha) {
	//load tower image
	tower_texture->load_tower(TOWER_DIR_PATH + FIRE_TOWER_IMAGE, width_number, height_number, 
		LTexture::tower_image_clip_list[level], blending, alpha);

	////set Texture mWidth and mHeight
	//tower_texture.mWidth = TOWER_IMAGE_WIDTH;
	//tower_texture.mHeight= TOWER_IMAGE_HEIGHT;

	//set tower level
	set_tower_level(level);


}
//SDL_Texture* IceTower::get_tower_texture_ptr() {
//	return tower_texture->mTexture;
//}
//LTexture& IceTower::get_tower_LTexture() {
//	return *tower_texture;
//}




PoisonTower::PoisonTower(int level, int x_location, int y_location) :
	Tower(level, x_location, y_location) { //Constructor

}
PoisonTower::~PoisonTower() {

}
void PoisonTower::load_tower_texture(int level, int tile_order, int width_number, int height_number, SDL_BlendMode blending, Uint8 alpha) {
	//load tower image
	tower_texture->load_tower(TOWER_DIR_PATH + FIRE_TOWER_IMAGE, width_number, height_number, 
		LTexture::tower_image_clip_list[level], blending, alpha);

	////set Texture mWidth and mHeight
	//tower_texture.mWidth = TOWER_IMAGE_WIDTH;
	//tower_texture.mHeight= TOWER_IMAGE_HEIGHT;

	//set tower level
	set_tower_level(level);


}
//SDL_Texture* PoisonTower::get_tower_texture_ptr() {
//	return tower_texture->mTexture;
//}
//LTexture& PoisonTower::get_tower_LTexture() {
//	return *tower_texture;
//}


#endif 