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

//files path  //need to modify to be more protable!!
const string ENEMY_DIR_PATH = "F:\\Project_resourses\\enemy\\";
const string STRONG_ENEMY_IMAGE = "strong_enemy.png";
const string FAST_ENEMY_IMAGE = "fast_enemy.png";
const string BOSS_ENEMY_IMAGE = "boss_enemy.png";


const int ENEMY_IMAGE_WIDTH=40;




class Abstract_Enemy {
public:
	Abstract_Enemy(int level, float hp, int _speed, 
			int start_x_location, int start_y_location); //constructor
	Abstract_Enemy(Abstract_Enemy&); //copy constructor
	~Abstract_Enemy(); //destructor
	Abstract_Enemy& operator=(Abstract_Enemy&); //assign operator

	//image
	virtual void render();
	virtual void load_enemy_texture();
	LTexture* get_enemy_texture() const;

	//tower_image_clip_list
	static vector<SDL_Rect*>& get_enemy_image_clip_list() ;
	static void set_tower_image_clip();

	//enemy path
	vector<Enemy_Path>& get_path() ;
	void load_and_init_path_file(); //judge total_phase_stage on the way
	void go_forward();

	//level
	void set_level(int level);
	int get_level() const;

	//location
	int get_x_location() const;
	int get_y_location() const;
	void set_x_location(int _x);
	void set_y_location(int _y);

private:
	//vector<string>  enemy_name; //name of different levels of enemies

	static vector<SDL_Rect*> enemy_image_clip_list; //static member, need to declare in .cpp and initialize

	mutable int x_location;
	mutable int y_location;
	int level;
	float life;
	int speed;  // pixels per frame

	int path_phase; //meet the turn, path_phase++
	int total_phase_stage;  //initialize in load_and_init_path_file()
	LTexture* enemy_texture;

	//enemy_path
	string enemy_path_file_path;
	vector<Enemy_Path> path;

};

Abstract_Enemy::Abstract_Enemy(int _level, float hp, int _speed,
	int start_x_location, int start_y_location):
	level(_level), life(hp), speed(_speed), x_location(start_x_location), y_location(start_y_location),
	enemy_texture(NULL), path_phase(0) {

	//pointer member 
	enemy_texture = new LTexture;
	load_enemy_texture();

	load_and_init_path_file(); //load_path_file  
							   //calculate_total_phase_stage
							   //set direction
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
Abstract_Enemy& Abstract_Enemy::operator=(Abstract_Enemy& that) { //assign operator
	//pointer member assign
	enemy_texture = new LTexture;
	*enemy_texture = *that.enemy_texture;

	//normal member assing
	x_location = that.x_location;
	y_location = that.y_location;
	level = that.level;
	speed = that.speed;
	path_phase = that.path_phase;
	enemy_path_file_path = that.enemy_path_file_path;

	//re_load_path
	load_and_init_path_file();
}
Abstract_Enemy::~Abstract_Enemy() {//destructor
	path.clear();
	enemy_texture->free();
}
void Abstract_Enemy::render() {
	enemy_texture->render(x_location,y_location,enemy_image_clip_list[level]);
}
void Abstract_Enemy::load_enemy_texture() { //empty
	//declare in the derived class
}
vector<SDL_Rect*>& Abstract_Enemy::get_enemy_image_clip_list() {
	return enemy_image_clip_list;
}
void Abstract_Enemy::set_tower_image_clip() {
	enemy_image_clip_list.resize(5);//level:1,2,3,4, exclusive of 0

	for (int i = 1; i < 5; i++) {
		enemy_image_clip_list[i] = new SDL_Rect;
		enemy_image_clip_list[i]->x = (i - 1)*ENEMY_IMAGE_WIDTH;
		enemy_image_clip_list[i]->y = 0;
		enemy_image_clip_list[i]->w = ENEMY_IMAGE_WIDTH;
		enemy_image_clip_list[i]->h = ENEMY_IMAGE_WIDTH;
	}
}
vector<Enemy_Path>& Abstract_Enemy::get_path() {
	return path;
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
	total_phase_stage = count_num; //count total_path_phase on the way

	//judge direction of each turn
	for (int i = 0; i < total_phase_stage; i++) {
		path[i].judge_direction();
	}

	enemy_path_file.close();
	
}
void Abstract_Enemy::go_forward() {
	bool out_path = false;

	//caution: UP-> y decrease!!   DOWN -> y increase
	//judge out of path range ?
	switch (path[path_phase].get_direction()) {
	case UP: 
		if (y_location <= path[path_phase].final_y_location) {
			assert(x_location == path[path_phase].final_x_location);
			out_path = true;
			y_location = path[path_phase].final_y_location; //re_oriented
		}
		break;
	case DOWN: 
		if (y_location >= path[path_phase].final_y_location) {
			assert(x_location == path[path_phase].final_x_location);
			out_path = true;
			y_location = path[path_phase].final_y_location;//re_oriented
		}
		break;
	case LEFT: 
		if (x_location <= path[path_phase].final_x_location) {
			assert(y_location == path[path_phase].final_y_location);
			out_path = true;
			x_location = path[path_phase].final_x_location;//re_oriented
		}
		break;
	case RIGHT:
		if (x_location >= path[path_phase].final_x_location) {
			assert(y_location == path[path_phase].final_y_location);
			out_path = true;
			x_location = path[path_phase].final_x_location;//re_oriented
		}
		break;
	default:
#ifdef DEBUG
		cout << "path direction error in go_foward()" << endl;
#endif // DEBUG

	}
 
	if (out_path==true) {
		path_phase++;
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
	return x_location;
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








#endif // !_ABSTRACT_ENEMY_H
