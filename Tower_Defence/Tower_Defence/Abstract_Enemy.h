//#pragma once
#ifndef _ABSTRACT_ENEMY_H
#define _ABSTRACT_ENEMY_H


#include <iostream>
#include <vector>
#include "Map.h"
#include "LTexture.h"
#include <cstring>
#include "Enemy_Path.h"
#include <fstream> //read files
//#include "Attack_Calculator.h"  //um_commemt the line will cause error!!??

//files path  //need to modify to be more protable!!
const string ENEMY_DIR_PATH = "..\\Project_resourses\\enemy\\";
const string ENEMY_PATH = "enemy_path.txt";
const string STRONG_ENEMY_IMAGE = "strong_enemy.png";
const string FAST_ENEMY_IMAGE = "fast_enemy.png";
const string BOSS_ENEMY_IMAGE = "boss_enemy.png";


const int ENEMY_IMAGE_WIDTH=40;




class Abstract_Enemy {
public:
	enum Enemy_State {
		NORMAL,
		FREEZED,
		POISONED,
		TOTAL_STATE
	};
	enum FootStep {
		FIFST_STEP,
		SECOND_STEP,
		THIRD_STEP,
		TOTAL_STEP
	};

	Abstract_Enemy(string _enemy_image_path,string path_file_path,int level, float hp, int _speed); //constructor
	Abstract_Enemy(Abstract_Enemy&); //copy constructor
	~Abstract_Enemy(); //destructor
	//Abstract_Enemy& operator=(Abstract_Enemy&); //assign operator

	//image
	virtual void render()=0; //pure virtual function
	virtual void load_enemy_texture(int level, SDL_BlendMode blending, Uint8 alpha)=0; //pure virtual function
	LTexture* get_enemy_texture() const;

	//tower_image_clip_list
	//BossEnemy declare another clip list in derived class, and use virtual function to render.
	static vector<vector<vector<SDL_Rect*>>>& get_enemy_image_clip_list() ;
	static void set_enemy_image_clip_list();

	//enemy path
	static vector<Enemy_Path>& get_path() ;
	static vector<Enemy_Path>* get_path_ptr();
	void load_and_init_path_file(); //judge total_phase_stage on the way
	void go_forward();
	bool in_the_terminal();
	//level
	void set_level(int level);
	int get_level() const;

	//location
	int get_x_location() const;
	int get_y_location() const;
	void set_x_location(int _x);
	void set_y_location(int _y);

	//enemy_state
	Enemy_State get_enemy_state();
	void set_enemy_state(Enemy_State _new_state);

	//path_phase
	int get_path_phase();
	int get_total_phase_stage();

	//foot_step
	int get_foot_step();
	//set foot_step in go_foreward() function

	friend class Attack_Calculator;

private:
	//vector<string>  enemy_name; //name of different levels of enemies

	//static vector<SDL_Rect*> enemy_image_clip_list; //static member, need to declare in .cpp and initialize
	static vector<vector<vector<SDL_Rect*>>> enemy_image_clip_list;
	mutable int x_location;
	mutable int y_location;
	int level;
	float life;
	int speed;  // pixels per frame

	int path_phase; //meet the turn, path_phase++
	int total_phase_stage;  //initialize in load_and_init_path_file()
	

	//texture
	string enemy_image_path;
	LTexture* enemy_texture;

	//enemy_path
	string enemy_path_file_path;
	static vector<Enemy_Path> path;

	//enemy_state
	Enemy_State enemy_state;

	//enemy_footstep
	FootStep foot_step;

};

Abstract_Enemy::Abstract_Enemy(string _enemy_image_path,string _path_file_path,int _level, float hp, int _speed):
	enemy_image_path(_enemy_image_path),enemy_path_file_path(_path_file_path),level(_level), life(hp), speed(_speed),
	enemy_texture(NULL), path_phase(0) {

	//pointer member 
	enemy_texture = new LTexture;


	load_and_init_path_file(); //load_path_file  
							   //calculate_total_phase_stage
							   //set direction

	x_location = path[path_phase].get_initial_x_location();
	y_location = path[path_phase].get_initial_y_location();
}
Abstract_Enemy::Abstract_Enemy(Abstract_Enemy& that):
	x_location(that.x_location),y_location(that.y_location),level(that.level),
	speed(that.speed),path_phase(that.path_phase),enemy_path_file_path(that.enemy_path_file_path)
{
	//pointer member assign
	enemy_texture = new LTexture;
	*enemy_texture = *that.enemy_texture;

	//re_load_path
	load_and_init_path_file();
}
Abstract_Enemy::~Abstract_Enemy() {//destructor
	path.clear();
	enemy_texture->free();
}
vector<vector<vector<SDL_Rect*>>>& Abstract_Enemy::get_enemy_image_clip_list() {
	return enemy_image_clip_list;
}
void Abstract_Enemy::set_enemy_image_clip_list() {
	//!! Only for StrongEnemy and FastEnemy!!
	//!! BossEnemy use another clip_list, whick define in derived class.!!
	//set the size of 3D vector
	enemy_image_clip_list.resize(3);
	for (int i = 0; i < 3; i++) {
		enemy_image_clip_list[i].resize(4);
		for (int j = 0; j < 4; j++) {
			enemy_image_clip_list[i][j].resize(3);
		}
	}

	for (int _state = 0; _state < TOTAL_STATE; _state++) {
		for (int _direction = 0; _direction < TOTAL_DIRECTION; _direction++) {
			for (int _step = 0; _step < TOTAL_STEP; _step++) {
				enemy_image_clip_list[_state][_direction][_step]=new SDL_Rect;
				enemy_image_clip_list[_state][_direction][_step]->x = _direction*3* ENEMY_IMAGE_WIDTH + _step * ENEMY_IMAGE_WIDTH;
				enemy_image_clip_list[_state][_direction][_step]->y = _state*ENEMY_IMAGE_WIDTH;
				enemy_image_clip_list[_state][_direction][_step]->w = ENEMY_IMAGE_WIDTH;
				enemy_image_clip_list[_state][_direction][_step]->h = ENEMY_IMAGE_WIDTH;
			}
		}
	}

	//enemy_image_clip_list.resize(5);//level:1,2,3,4, exclusive of 0

	//for (int i = 1; i < 5; i++) {
	//	enemy_image_clip_list[i] = new SDL_Rect;
	//	enemy_image_clip_list[i]->x = (i - 1)*ENEMY_IMAGE_WIDTH;
	//	enemy_image_clip_list[i]->y = 0;
	//	enemy_image_clip_list[i]->w = ENEMY_IMAGE_WIDTH;
	//	enemy_image_clip_list[i]->h = ENEMY_IMAGE_WIDTH;
	//}
}
vector<Enemy_Path>& Abstract_Enemy::get_path() {
	return path;
}
vector<Enemy_Path>* Abstract_Enemy::get_path_ptr() {
	return &path;
}
void Abstract_Enemy::load_and_init_path_file() {
	//load_path_file  
	//calculate_total_phase_stage
	//set direction

	fstream enemy_path_file;
	enemy_path_file.open(enemy_path_file_path.c_str(), ios::in); //open file, read only


	int count_num = 0;

	if (!enemy_path_file) {
		cerr << "can't open file" << endl;
		exit(1);
	}
	else {
		while (!enemy_path_file.eof()) {
			count_num++;
			path.resize(count_num);
			char comma;
			enemy_path_file >> path[count_num-1].initial_x_location;
			enemy_path_file >> comma;
			enemy_path_file >> path[count_num-1].initial_y_location;
			enemy_path_file >> comma;
			enemy_path_file >> path[count_num-1].final_x_location;
			enemy_path_file >> comma;
			enemy_path_file >> path[count_num-1].final_y_location;
			enemy_path_file >> comma;

			
		}//end of while
	}//end of else
	total_phase_stage = count_num; //count total_path_phase on the way

	//judge direction of each turn
	for (int i = 0; i < total_phase_stage; i++) {
		path[i].judge_direction();
	}

	enemy_path_file.close();
	
}
void Abstract_Enemy::go_forward() {
	bool out_path = false;
	
	//foot_step++
	if (foot_step == FIFST_STEP) {
		foot_step = SECOND_STEP;
	}
	else if (foot_step == SECOND_STEP) {
		foot_step = THIRD_STEP;
	}
	else if (foot_step == THIRD_STEP) {
		foot_step = FIFST_STEP;
	}

	//caution: UP-> y decrease!!   DOWN -> y increase
	//judge out of path range ?
	switch (path[path_phase].get_direction()) {
	case UP: 
		if (y_location < path[path_phase].final_y_location|| y_location == path[path_phase].final_y_location) {
			assert(x_location == path[path_phase].final_x_location);
			out_path = true;
			y_location = path[path_phase].final_y_location; //re_oriented
		}
		break;
	case DOWN: 
		if (y_location > path[path_phase].final_y_location|| y_location == path[path_phase].final_y_location) {
			assert(x_location == path[path_phase].final_x_location);
			out_path = true;
			y_location = path[path_phase].final_y_location;//re_oriented
		}
		break;
	case LEFT: 
		if (x_location < path[path_phase].final_x_location|| x_location == path[path_phase].final_x_location) {
			assert(y_location == path[path_phase].final_y_location);
			out_path = true;
			x_location = path[path_phase].final_x_location;//re_oriented
		}
		break;
	case RIGHT:
		if (x_location > path[path_phase].final_x_location|| x_location == path[path_phase].final_x_location) {
			assert(y_location == path[path_phase].final_y_location);
			out_path = true;
			x_location = path[path_phase].final_x_location;//re_oriented
		}
		break;


	}
 
	if (out_path==true) {
		if (path_phase == total_phase_stage-1) {
			x_location = path[path_phase].final_x_location;
			y_location = path[path_phase].final_y_location;
		}
		else {
			path_phase++;
			x_location = path[path_phase].initial_x_location;
			y_location = path[path_phase].initial_y_location;
		}
	}
	else {
		switch (path[path_phase].get_direction())
		{
		case UP: y_location -= speed; break;
		case DOWN: y_location += speed; break;
		case LEFT: x_location -= speed; break;
		case RIGHT:x_location += speed; break;
		default:
#ifdef DEBUG
			cout << "path direction error in go_foward()" << endl;
#endif // DEBUG
			break;
		}//end of switch
	}//end of else
}//end of go_forward
void Abstract_Enemy::set_level(int _level) {
	level = _level;
}
int Abstract_Enemy::get_level() const {
	return level;
}
int Abstract_Enemy::get_x_location() const {
	return x_location;
}
int Abstract_Enemy::get_y_location() const {
	return y_location;
}
void Abstract_Enemy::set_x_location(int _x) {
	x_location = _x;
}
void Abstract_Enemy::set_y_location(int _y) {
	y_location = _y;
}
LTexture* Abstract_Enemy::get_enemy_texture() const{
	return enemy_texture;
}
//enemy_state
Abstract_Enemy::Enemy_State Abstract_Enemy::get_enemy_state() {
	return enemy_state;
}
void Abstract_Enemy::set_enemy_state(Enemy_State _new_state) {
	enemy_state = _new_state;
}
//path_phase
int Abstract_Enemy::get_path_phase() {
	return path_phase;
}
int Abstract_Enemy::get_total_phase_stage() {
	return total_phase_stage;
}
//foot_step
int Abstract_Enemy::get_foot_step() {
	return foot_step;
}

bool Abstract_Enemy::in_the_terminal() {
	if (x_location == path[total_phase_stage - 1].get_final_x_location() &&
		y_location == path[total_phase_stage - 1].get_final_y_location()) {
		return true;
	}
	else { return false; }
}



#endif // !_ABSTRACT_ENEMY_H
