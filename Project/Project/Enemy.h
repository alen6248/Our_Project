#pragma once

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
#include <stdio.h>  //exit() 
#include <fstream> //read files
#include "Map.h"
#include "LTexture.h"
#include <cstring>


using namespace std;
class Enemy {
	public:
		Enemy(int level, float hp, int _speed, int start_x_location, int start_y_location, vector<Enemy_Path>_path); //constructor
		~Enemy();//destructor
		void go_forward();
		virtual void draw();
		virtual void load_enemy_image();
		void load_path_file(); //judge total_phase_stage on the way
	protected:
		mutable int x_pixel_location;	
		mutable int y_pixel_location;
		//mutable int d;  //一維位置

	private:
		string enemy_path_file_path;
		int enemy_level;
		float life;
		int speed;  // pixels per frame
		int path_phase; //meet the turn, path_phase++
		int total_phase_stage; //how to get??  //how to initailize??
		LTexture* enemy_image;
		vector<Enemy_Path> path;
		
	
};

Enemy::Enemy(int level,float hp,int _speed,int start_x_location,int start_y_location, vector<Enemy_Path>_path) :
	enemy_level(level),life(hp),speed(_speed),x_pixel_location(start_x_location),y_pixel_location(start_y_location),
	path(_path),enemy_image(NULL),path_phase(0){
	for (int i = 0; i < total_phase_stage; i++) {
		path[i].judge_direction();
	}
}
Enemy::~Enemy() {//destructor
	path.clear();
	enemy_image->free();
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
void Enemy::go_forward() {
	if (path[path_phase].get_final_x_location == x_pixel_location &&
		path[path_phase].get_fianl_y_location == y_pixel_location) {
		path_phase++;
	}
	else {
		switch (path[path_phase].get_direction())
		{
		case UP: y_pixel_location += speed; break;
		case DOWN: y_pixel_location -= speed; break;
		case LEFT: x_pixel_location -= speed; break;
		case RIGHT:x_pixel_location += speed; break;
		default:
#ifdef DEBUG
			cout << "path direction error in go_foward()" << endl;
#endif // DEBUG
			break;
		}//end of switch
	}//end of else
}//end of go_forward


















class StrongEnemy : public Enemy {
	private:
		char* em_name;
		bool survive;
		//SDL圖像檔

	protected:
	public:
};


class FastEnemy : public Enemy {
	private:
		char* em_name;
		bool survive;
		//SDL圖像檔
	protected:
	public:
};

class BossEnemy : public Enemy {
	private:
		char* em_name;
		bool survive;
		//SDL圖像檔
	protected:
	public:
};













#endif // !_ENEMY_H