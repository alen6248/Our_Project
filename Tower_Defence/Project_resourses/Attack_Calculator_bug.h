//#pragma once
#ifndef _ATTACK_CALCULATOR
#define _ATTACK_CALCULATOR

#include "Input_Interface.h"
#include "Abstract_Enemy.h"
#include <fstream>
#include <cstdlib>
#include "Enemy_Path.h"

extern Input_Interface input_interface;
extern const string ENEMY_DIR_PATH;
const string ENEMY_PATH_TYPE_B = "enemy_path_Type_b.txt";

struct point {
	int x;
	int y;
};



struct enemy_1D_data;

class Attack_Calculator {
public:
	struct enemy_1D_point {
		int d;
		Abstract_Enemy* enemy;
	};
	struct unit_attack_range {
		int start_d;
		int terminate_d;
	};
	struct Towers_1D_attack_ranges {
		//int d=0;
		vector<vector<unit_attack_range*>> attack_range_1D; //[lebel][section]
	};
	Attack_Calculator();
	~Attack_Calculator();

	
	void turn_to_1D_attack_range();
	void read_enemy_path();
	void point_to_path();

private:
	//vector<point> path_turn_points;
	//vector<Enemy_Path>& path=Abstract_Enemy::get_path(); //point to Abstract_Enemy static member path_ptr
	vector<vector<enemy_1D_point*>> enemy_1D_location; //[enemy_type][lebel]
	//vector<Enemy_Path> path;
	Towers_1D_attack_ranges towers_attack_ranges;
	int total_phase_stage;
	vector<Enemy_Path> path;
	//Enemy_Path path;
	
};

Attack_Calculator::Attack_Calculator() {

}

Attack_Calculator::~Attack_Calculator() {

}

void Attack_Calculator::turn_to_1D_attack_range() {
	
	//read_enemy_path();
	int Tower_num = input_interface.get_Towers().size();
	towers_attack_ranges.attack_range_1D.resize(Tower_num);
	int _total_section_num = path.size();

	for (int _lebel=0; _lebel < Tower_num; _lebel++) {
		for (int _section_num =0; _section_num < _total_section_num; _section_num++) {
			if (path.at(_section_num).get_derection)
				path;


		}




	}
	



}


//void Attack_Calculator::point_to_path() {
//	path = Abstract_Enemy::get_path();
//}

//void Attack_Calculator::read_enemy_path() {
//	fstream enemy_path_file;
//	enemy_path_file.open(ENEMY_DIR_PATH + ENEMY_PATH_TYPE_B, ios::in); //open file, read only
//
//	int count_num = 0;
//	if (!enemy_path_file) {
//		cerr << "can't open file" << endl;
//		exit(1);
//	}
//	else {
//		while (!enemy_path_file.eof()) {
//			count_num++;
//			path_turn_points.resize(count_num);
//			char comma;
//			enemy_path_file >> path_turn_points[count_num - 1].x;
//			enemy_path_file >> comma;
//			enemy_path_file >> path_turn_points[count_num - 1].y;
//			enemy_path_file >> comma;
//		}//end of while
//	}//end of else
//}




#endif // !_ATTACK_CALCULATOR
