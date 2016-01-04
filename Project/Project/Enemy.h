//#pragma once

//====================設計=========================================
//Enemy 參數紀錄
//Enemy類別
//StrongEnemy  FastEnemy  BossEnemy  三種不同敵人


//=================================================================


/***************************問題********************************/
//塔升級時是否改變所占面積?
//FireTower是否改成攻擊範圍360度?
//FireTower 升級前1對1,升級後範圍攻擊?
/***************************************************************/

#ifndef _ENEMY_H
#define _ENEMY_H

#include "Enemy_Path.h"
#include <iostream>
#include <vector>
#include <stdio.h>  //exit() 
#include <fstream> //read files
#include "Map.h"
#include "LTexture.h"
#include <cstring>

//files path  //need to modify to more protable!!
const string ENEMY_DIR_PATH = "F:\\Project_resourses\\enemy\\";
const string STRONG_ENEMY_IMAGE = "strong_enemy.png";
const string FAST_ENEMY_IMAGE = "fast_enemy.png";
const string BOSS_ENEMY_IMAGE = "boss_enemy.png";

using namespace std;
class Enemy {
	public:
		Enemy(int level, float hp, int _speed, int start_x_location, int start_y_location); //constructor
		~Enemy();//destructor
		void go_forward();
		virtual void draw();
		virtual void load_enemy_texture();
		void load_path_file(); //judge total_phase_stage on the way
		void set_enemy_level(int level);
		int get_enemy_level() const;
		//virtual string level_to_name();
		LTexture* get_enemy_texture();
		vector<Enemy_Path>& get_path();
		mutable int x_pixel_location;
		mutable int y_pixel_location;
	protected:
		
		//mutable int d;  //一維位置

	private:
		//vector<string>  enemy_name; //name of different levels of enemies
		string enemy_path_file_path;
		int enemy_level;
		float life;
		int speed;  // pixels per frame
		int path_phase; //meet the turn, path_phase++
		int total_phase_stage; //how to get??  //how to initailize??
		LTexture* enemy_texture;
		vector<Enemy_Path> path;
		
	
};

Enemy::Enemy(int level,float hp,int _speed,int start_x_location,int start_y_location) :
	enemy_level(level),life(hp),speed(_speed),x_pixel_location(start_x_location),y_pixel_location(start_y_location),
	enemy_texture(NULL),path_phase(0){
	for (int i = 0; i < total_phase_stage; i++) {
		path[i].judge_direction();
	}
}
Enemy::~Enemy() {//destructor
	path.clear();
	enemy_texture->free();
}
void Enemy::load_path_file() {
	fstream enemy_path_file;
	enemy_path_file.open(enemy_path_file_path.c_str(), ios::in); //open file, read only

	
	int count_num = 0;

	if (!enemy_path_file) {
		cerr << "can't open file" << endl;
		exit(1);
	}
	else {
		while (!enemy_path_file.eof()) {
			char comma;
			enemy_path_file >> path[count_num].initial_x_location;
			enemy_path_file >> comma;
			enemy_path_file >> path[count_num].initial_y_location;
			enemy_path_file >> comma;
			enemy_path_file >> path[count_num].final_x_location;
			enemy_path_file >> comma;
			enemy_path_file >> path[count_num].final_y_location;
			enemy_path_file >> comma;

			count_num++;
		}//end of while
	}//end of else
	enemy_path_file.close();
	total_phase_stage = count_num; //count total_path_phase on the way
}
//void Enemy::go_forward() {
//	if (path[path_phase].get_final_x_location == x_pixel_location &&
//		path[path_phase].get_final_y_location == y_pixel_location) {
//		path_phase++;
//	}
//	else {
//		switch (path[path_phase].get_direction())
//		{
//		case UP: y_pixel_location -= speed; break;
//		case DOWN: y_pixel_location += speed; break;
//		case LEFT: x_pixel_location -= speed; break;
//		case RIGHT:x_pixel_location += speed; break;
//		default:
//#ifdef DEBUG
//			cout << "path direction error in go_foward()" << endl;
//#endif // DEBUG
//			break;
//		}//end of switch
//	}//end of else
//}//end of go_forward
void Enemy::set_enemy_level(int level) {
	enemy_level = level;
}
int Enemy::get_enemy_level() const {
	return enemy_level;
}
LTexture* Enemy::get_enemy_texture() {
	return enemy_texture;
}
vector<Enemy_Path>& Enemy::get_path() {
	return path;
}

class StrongEnemy : public Enemy {
	
	public:
		StrongEnemy(int level, float hp, int _speed, int start_x_location, int start_y_location
			);
		~StrongEnemy();
		virtual void render();
		virtual void load_enemy_texture(int level, int tile_order, int width_pixel_location, int height_pixel_location, SDL_BlendMode blending, Uint8 alpha);

	protected:
	
	private:
		
		bool survive;
};
class FastEnemy : public Enemy {
public:
	FastEnemy(int level, float hp, int _speed, int start_x_location, int start_y_location);
	~FastEnemy();
	virtual void render();
	virtual void load_enemy_texture(int level, int tile_order, int width_pixel_location, int height_pixel_location, SDL_BlendMode blending, Uint8 alpha);

protected:

private:

	bool survive;
};
class BossEnemy : public Enemy {
public:
	BossEnemy(int level, float hp, int _speed, int start_x_location, int start_y_location);
	~BossEnemy();
	virtual void render();
	virtual void load_enemy_texture(int level, int tile_order, int width_pixel_location, int height_pixel_location, SDL_BlendMode blending, Uint8 alpha);

protected:

private:

	bool survive;
};



StrongEnemy::StrongEnemy(int level, float hp, int _speed, int start_x_location, int start_y_location
						):Enemy(level,hp,_speed, start_x_location,  start_y_location) {

}
StrongEnemy::~StrongEnemy() {
	
}
void StrongEnemy::render() {
	//get_enemy_texture()->render(x_pixel_location,y_pixel_location,LTexture::get_enemy_image_clip_list()[get_enemy_level()]);
}
void StrongEnemy::load_enemy_texture(int level, int tile,int width_pixel_location, int height_pixel_location, SDL_BlendMode blending, Uint8 alpha) {
	/*get_enemy_texture()->load_enemy(ENEMY_DIR_PATH + STRONG_ENEMY_IMAGE, width_pixel_location, height_pixel_location,
		LTexture::get_enemy_image_clip_list()[level], blending, alpha);*/
	set_enemy_level(level);
}




FastEnemy::FastEnemy(int level, float hp, int _speed, int start_x_location, int start_y_location) :
	Enemy(level, hp, _speed, start_x_location, start_y_location) {

}
FastEnemy::~FastEnemy() {

}
void FastEnemy::render() {
	get_enemy_texture()->render(x_pixel_location, y_pixel_location, LTexture::get_enemy_image_clip_list()[get_enemy_level()]);
}
void FastEnemy::load_enemy_texture(int level, int tile_order, int width_pixel_location, int height_pixel_location, SDL_BlendMode blending, Uint8 alpha) {
	get_enemy_texture()->load_enemy(ENEMY_DIR_PATH + FAST_ENEMY_IMAGE, width_pixel_location, height_pixel_location,
		LTexture::get_enemy_image_clip_list()[level], blending, alpha);
	set_enemy_level(level);
}



BossEnemy::BossEnemy(int level, float hp, int _speed, int start_x_location, int start_y_location) 
	:Enemy(level, hp, _speed, start_x_location, start_y_location) {

}
BossEnemy::~BossEnemy() {

}
void BossEnemy::render() {
	get_enemy_texture()->render(x_pixel_location, y_pixel_location, LTexture::get_enemy_image_clip_list()[get_enemy_level()]);
}
void BossEnemy::load_enemy_texture(int level, int tile_order, int width_pixel_location, int height_pixel_location, SDL_BlendMode blending, Uint8 alpha) {
	get_enemy_texture()->load_enemy(ENEMY_DIR_PATH + BOSS_ENEMY_IMAGE, width_pixel_location, height_pixel_location,
		LTexture::get_enemy_image_clip_list()[level], blending, alpha);
	set_enemy_level(level);
}





#endif // !_ENEMY_H