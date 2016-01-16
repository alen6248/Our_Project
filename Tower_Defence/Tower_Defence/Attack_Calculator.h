#pragma once

#include "Enemy_Path.h"
#include "Abstract_Enemy.h"
#include "Input_Interface.h"
#include "Abstract_Tower.h"
#include "Input_Interface.h"
#include "Simulated_Enemy.h"
#include "Simulated_Tower.h"
#include <fstream>
#include <cmath>
#include <cstdlib>


//extern Input_Interface input_interface;
extern const int TILE_WIDTH;
extern const string ENEMY_DIR_PATH;
const string ENEMY_PATH_TYPE_B = "enemy_path_Type_B.txt";

class Attack_Calculator {

public:
	struct unit_attack_range {
		int start_d;
		int terminate_d;
	};
	
	void Attack_Calculator_Core();
	Attack_Calculator(Input_Interface& _input_interface, vector<Abstract_Enemy*>& _Enemies);
	~Attack_Calculator();
	void load_1D_tower_attack_range();
	int get_accumulate_path_distance(int _section)const; //get_accumulate_path_distance before _section
	void load_and_init_path_file();
	void init_set_simulated_Enemies();
	void init_set_simulated_Towers();
	void progress();


private:
	//vector<Enemy_Path*> path_ptr;
	vector<Enemy_Path> path;
	vector<Abstract_Tower*>& Towers;
	vector<vector<unit_attack_range>> Towers_attack_range_1D; //[label][section]
	Input_Interface& input_interface;
	vector<Abstract_Enemy*>& Enemies;
	vector<Simulated_Enemy*> simulated_Enemies;
	vector<Simulated_Tower*> simulated_Towers;

};

void Attack_Calculator::Attack_Calculator_Core() {
	cout << "Enter Attack_Calculator_Core" << endl;
	load_and_init_path_file();
	load_1D_tower_attack_range();

	path; //debug
	Towers_attack_range_1D; //debug
}
Attack_Calculator::Attack_Calculator(
	Input_Interface& _input_interface,
	vector<Abstract_Enemy*>& _Enemies):
		input_interface(_input_interface),
		Towers(_input_interface.get_Towers()),
		Enemies(_Enemies){//get path and Towers from outer
	
}
Attack_Calculator::~Attack_Calculator() {
	for (int i = 0; i < Towers_attack_range_1D.size(); i++){
		Towers_attack_range_1D[i].clear();
	}
	Towers_attack_range_1D.clear();

}

//函數不完整，沒處理到邊角的情況  //但決定將邊角的地方設成不可放塔
void Attack_Calculator::load_1D_tower_attack_range() {
	int Towers_num = Towers.size();
	Towers_attack_range_1D.resize(Towers_num);
	int total_section_num = path.size();

	for (int _label = 0; _label < Towers_num; _label++) {
		int valid_attack_range_number_of_a_tower = 0;
		float attack_range = Towers[_label]->get_attack_range();
		int tower_x_location = (Towers[_label]->get_tower_width_pixel_location() + TILE_WIDTH / 2);
		int tower_y_location = (Towers[_label]->get_tower_height_pixel_location() + TILE_WIDTH / 2);
		for (int _section = 0; _section < total_section_num; _section++) {

			//calculate start&terminal distance from tower
			float tower_initial_x= fabs(tower_x_location - path[_section].get_initial_x_location());
			float tower_initial_y= fabs(tower_y_location - path[_section].get_initial_y_location());
			float tower_section_initial_distance=pow(tower_initial_x *tower_initial_x + tower_initial_y*tower_initial_y,0.5);

			float tower_final_x = fabs(tower_x_location - path[_section].get_final_x_location());
			float tower_final_y = fabs(tower_y_location - path[_section].get_final_y_location());
			float tower_section_final_distance = pow(tower_final_x *tower_final_x + tower_final_y*tower_final_y, 0.5);
		


			if (path[_section].get_direction() == Direction::UP || path[_section].get_direction() == Direction::DOWN) {
				float distance =
					fabs(
						tower_x_location
						- path[_section].get_initial_x_location()
						);

				bool inside_range = true;
				if (distance < attack_range) {
					if (tower_section_initial_distance > attack_range&&
						tower_section_final_distance > attack_range) {
						inside_range = false;
					}
					else { inside_range = true; }

				}
				else { inside_range = false; }


				if(inside_range) {


					float half_range = powf(attack_range*attack_range - distance*distance, 0.5);

					int projected_distance = get_accumulate_path_distance(_section); //calculate the distance accumulate before _section
					int section_projected_distance =  //this _section
						(int)fabs(
							tower_y_location
							- path[_section].get_initial_y_location()
							);
					projected_distance += section_projected_distance;


					int forward_bound =
						(int)fabs(
							path[_section].get_final_y_location()
							- tower_y_location
							); //max distance
					if (forward_bound > half_range) { //judge section_projected_distance out of range?
						forward_bound = half_range;
					}

					int backward_bound =
						(int)fabs(
							path[_section].get_initial_y_location()
							- tower_y_location
							);//max distance
					if (backward_bound > half_range) { //judge section_projected_distance out of range?
						backward_bound = half_range;
					}
					valid_attack_range_number_of_a_tower++;
					Towers_attack_range_1D[_label].resize(valid_attack_range_number_of_a_tower);
					Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].start_d = projected_distance - backward_bound;
					Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].terminate_d = projected_distance + forward_bound;
				}
			}
			else if (path[_section].get_direction() == Direction::LEFT || path[_section].get_direction() == Direction::RIGHT) {

				float distance =
					fabs(
						tower_y_location
						- path[_section].get_initial_y_location()
						);

				bool inside_range = true;
				if (distance < attack_range) {
					if (tower_section_initial_distance > attack_range&&
						tower_section_final_distance > attack_range) {
						inside_range = false;
					}
					else { inside_range = true; }

				}
				else { inside_range = false; }


				if (inside_range) {


					float half_range = powf(attack_range*attack_range - distance*distance, 0.5);

					int projected_distance = get_accumulate_path_distance(_section); //calculate the distance accumulate before _section
					int section_projected_distance =  //this _section
						(int)fabs(
							tower_x_location
							- path[_section].get_initial_x_location()
							);
					projected_distance += section_projected_distance;


					int forward_bound =
						(int)fabs(
							path[_section].get_final_x_location()
							- tower_x_location
							); //max distance
					if (forward_bound > half_range) { //judge section_projected_distance out of range?
						forward_bound = half_range;
					}

					int backward_bound =
						(int)fabs(
							path[_section].get_initial_x_location()
							- tower_x_location
							);//max distance
					if (backward_bound > half_range) { //judge section_projected_distance out of range?
						backward_bound = half_range;
					}

					valid_attack_range_number_of_a_tower++;
					Towers_attack_range_1D[_label].resize(valid_attack_range_number_of_a_tower);
					Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].start_d = projected_distance - backward_bound;
					Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].terminate_d = projected_distance + forward_bound;
				}
			}
		}
	}
}
int Attack_Calculator::get_accumulate_path_distance(int _section)const {
	int accumulate_distance = 0;
	for (int i = 0; i < _section; i++) {
		if (path[i].get_direction() == Direction::UP || path[i].get_direction() == Direction::DOWN) {
			accumulate_distance += 
				(int)fabs(
					path[i].get_final_y_location() 
					- path[i].get_initial_y_location()
				);
		}
		else if (path[i].get_direction() == Direction::LEFT || path[i].get_direction() == Direction::RIGHT) {
			accumulate_distance += 
				(int)fabs(
					path[i].get_final_x_location() 
					- path[i].get_initial_x_location()
				);
		}
	}
	return accumulate_distance;

}
void Attack_Calculator::load_and_init_path_file() {
	fstream enemy_path_file;
	enemy_path_file.open(ENEMY_DIR_PATH + ENEMY_PATH_TYPE_B, ios::in); //open file, read only

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
			int location;
			enemy_path_file >> location;
				path[count_num - 1].set_initial_x_location(location);
			enemy_path_file >> comma;
			enemy_path_file >> location;
				path[count_num - 1].set_initial_y_location(location);
			enemy_path_file >> comma;
			enemy_path_file >> location;
				path[count_num - 1].set_final_x_location(location);
			enemy_path_file >> comma;
			enemy_path_file >> location;
				path[count_num - 1].set_final_y_location(location);
			enemy_path_file >> comma;


		}//end of while
	}//end of else

	int total_phase_stage = count_num; //count total_path_phase on the way

									   //judge direction of each turn
	for (int i = 0; i < total_phase_stage; i++) {
		path[i].judge_direction();
	}

	enemy_path_file.close();

}
void Attack_Calculator::progress() {

}




