//#pragma once
#ifndef _ENEMY_PATH_H
#define _ENEMY_PATH_H
#define DEBUG

#include <iostream>
#include "Map.h"
#include "LTexture.h"
#include <cstring>

enum Direction {
	UP=0,DOWN=1,LEFT=2,RIGHT=3
};
//use vector<Enemy_Path> to load path of turns
class Enemy_Path {
public:
	Enemy_Path(int x_i, int y_i, int x_f, int y_f);
	~Enemy_Path();
	Direction judge_direction();
	int get_initial_x_location() const;
	int	get_final_x_location() const;
	int get_initial_y_location() const;
	int get_final_y_location() const;
	Direction get_direction()const ;

	void set_initial_x_location(int x_i) ;
	void set_final_x_location(int x_f) ;
	void set_initial_y_location(int y_i) ;
	void set_final_y_location(int y_f) ;
	
	//friend void Enemy::load_path_file();
	friend class Enemy;
private:
	int initial_x_location;
	int final_x_location;
	int initial_y_location;
	int final_y_location;
	Direction direction;
	//int speed; //pixels per frame
};

Enemy_Path::Enemy_Path(int x_i,int y_i,int x_f,int y_f):
	initial_x_location(x_i), initial_y_location(y_i), final_x_location(x_f), final_y_location(y_f){

}
Enemy_Path::~Enemy_Path() {

}
Direction Enemy_Path::judge_direction() {
	int w_x=final_x_location-initial_x_location;
	int w_y = final_y_location-initial_y_location;

	if (w_x == 0&& w_y > 0) {
		direction = UP;
	}
	else if (w_x == 0 && w_y < 0) {
		direction = DOWN;
	}
	else if (w_x < 0 && w_y == 0) {
		direction = LEFT;
	}
	else if (w_x > 0 && w_y == 0) {
		direction = RIGHT;
	}
	else {
#ifdef DEBUG
		cout << "Enemy Path Error!!" << endl;
#endif // DEBUG
	}
	return direction;
}
int Enemy_Path::get_initial_x_location() const {
	return initial_x_location;
}
int	Enemy_Path::get_final_x_location() const {
	return final_y_location;
}
int Enemy_Path::get_initial_y_location() const {
	return initial_y_location;
}
int Enemy_Path::get_final_y_location() const {
	return final_y_location;
}
Direction Enemy_Path::get_direction()const {
	return direction;
}
void Enemy_Path::set_initial_x_location(int x_i) {
	initial_x_location = x_i;
}
void Enemy_Path::set_final_x_location(int x_f) {
	final_x_location = x_f;
}
void Enemy_Path::set_initial_y_location(int y_i) {
	initial_y_location = y_i;
}
void Enemy_Path::set_final_y_location(int y_f) {
	final_y_location = y_f;
}
#endif // !_ENEMY_PATH_H