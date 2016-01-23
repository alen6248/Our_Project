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
	vector<vector<unit_attack_range>> Towers_attack_range_1D; //[tower_label][section]
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
			//get path start & final point
			int section_start_x = path[_section].get_initial_x_location();
			int section_start_y= path[_section].get_initial_y_location();
			int seciton_final_x = path[_section].get_final_x_location();
			int seciton_final_y = path[_section].get_final_y_location();
			//boundary
			int section_left = (section_start_x <= seciton_final_x) ? section_start_x : seciton_final_x;
			int section_right= (section_start_x >= seciton_final_x) ? section_start_x : seciton_final_x;
			int section_up = (section_start_y <= seciton_final_y) ? section_start_y : seciton_final_y;
			int section_down = (section_start_y >= seciton_final_y) ? section_start_y : seciton_final_y;

			//calculate start&terminal distance from tower
			float tower_start_x= fabs(tower_x_location - section_start_x);
			float tower_start_y= fabs(tower_y_location - section_start_y);
				//start_tower distance
			float tower_section_start_distance=pow(tower_start_x *tower_start_x + tower_start_y*tower_start_y,0.5);

			float tower_final_x = fabs(tower_x_location - seciton_final_x);
			float tower_final_y = fabs(tower_y_location - seciton_final_y);
				//terminal_tower distance
			float tower_section_final_distance = pow(tower_final_x *tower_final_x + tower_final_y*tower_final_y, 0.5);
		


			if (path[_section].get_direction() == Direction::UP || path[_section].get_direction() == Direction::DOWN) {
				//tower_road distance
				float distance = fabs(tower_x_location - section_start_x);

				//judge whether the range cover the road_section
				bool inside_range = true;
				if (distance < attack_range) {
					if (tower_section_start_distance > attack_range&&
						tower_section_final_distance > attack_range) {
						inside_range = false;
					}
					else { inside_range = true; }
				}
				else { inside_range = false; }


				if (inside_range) {
					bool out_up_boundary = (tower_y_location < section_up);
					bool out_down_boundary = (tower_y_location > section_down);
					//not the above two -> in the boundary

					float half_range = powf(attack_range*attack_range - distance*distance, 0.5);

					int projected_distance = get_accumulate_path_distance(_section); //calculate the distance accumulate before _section
					int section_projected_distance = (int)fabs(tower_y_location - section_start_y);
					projected_distance += section_projected_distance;

					if ((!out_up_boundary) && (!out_down_boundary)) {//in_the boundary

						int up_range_cover = ((int)fabs(section_up - tower_y_location) <= (int)half_range) ? //choose the small one
							(int)fabs(section_up - tower_y_location) : (int)half_range;
						int down_range_cover = ((int)fabs(section_down - tower_y_location) <= (int)half_range) ? //choose the small one
							(int)fabs(section_down - tower_y_location) : (int)half_range;

						if (path[_section].get_direction() == Direction::UP) {
							valid_attack_range_number_of_a_tower++;
							Towers_attack_range_1D[_label].resize(valid_attack_range_number_of_a_tower);
							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].start_d = projected_distance - down_range_cover;
							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].terminate_d = projected_distance + up_range_cover;

						}
						else if (path[_section].get_direction() == Direction::DOWN) {
							valid_attack_range_number_of_a_tower++;
							Towers_attack_range_1D[_label].resize(valid_attack_range_number_of_a_tower);
							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].start_d = projected_distance - up_range_cover;
							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].terminate_d = projected_distance + down_range_cover;
						}

					}
					else if (out_up_boundary) {

						if (path[_section].get_direction() == Direction::UP) {
							valid_attack_range_number_of_a_tower++;
							Towers_attack_range_1D[_label].resize(valid_attack_range_number_of_a_tower);

							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].start_d =
								(
									projected_distance - (int)half_range <=
									projected_distance - (int)fabs(tower_y_location - section_down)
								) ?
								(projected_distance - (int)half_range) :
								(projected_distance - (int)fabs(tower_y_location - section_down));

							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].terminate_d =
								projected_distance - (int)fabs(tower_y_location - section_up);
						}



						else if (path[_section].get_direction() == Direction::DOWN) {
							valid_attack_range_number_of_a_tower++;
							Towers_attack_range_1D[_label].resize(valid_attack_range_number_of_a_tower);

							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].start_d =
								projected_distance - (int)fabs(tower_y_location - section_up);

							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].terminate_d =
								(
									projected_distance - 2 * (int)fabs(tower_y_location - section_up) + (int)half_range <=
									projected_distance - 2 * (int)fabs(tower_y_location - section_up) + (int)fabs(tower_y_location - section_down)
								) ?
								(projected_distance - 2 * (int)fabs(tower_y_location - section_up) + (int)half_range) :
								(projected_distance - 2 * (int)fabs(tower_y_location - section_up) + (int)fabs(tower_y_location - section_down));

						}


					}
					else if (out_down_boundary) {

						if (path[_section].get_direction() == Direction::UP) {
							valid_attack_range_number_of_a_tower++;
							Towers_attack_range_1D[_label].resize(valid_attack_range_number_of_a_tower);

							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].start_d =
								projected_distance - (int)fabs(tower_y_location - section_down);

							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].terminate_d =
								(
									projected_distance - 2 * (int)fabs(tower_y_location - section_down) + (int)half_range <=
									projected_distance - 2 * (int)fabs(tower_y_location - section_down) + (int)fabs(tower_y_location - section_up)
								) ?
								(projected_distance - 2 * (int)fabs(tower_y_location - section_down) + (int)half_range) :
								(projected_distance - 2 * (int)fabs(tower_y_location - section_down) + (int)fabs(tower_y_location - section_up));



						}



						else if (path[_section].get_direction() == Direction::DOWN) {
							valid_attack_range_number_of_a_tower++;
							Towers_attack_range_1D[_label].resize(valid_attack_range_number_of_a_tower);

							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].start_d =
								(
									projected_distance - (int)half_range <=
									projected_distance - (int)fabs(tower_y_location - section_up)
								) ?
								(projected_distance - (int)half_range) :
								(projected_distance - (int)fabs(tower_y_location - section_up));

							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].terminate_d =
								projected_distance - (int)fabs(tower_y_location - section_down);

						}

					}
				}
			}
			else if (path[_section].get_direction() == Direction::LEFT || path[_section].get_direction() == Direction::RIGHT) {
				//tower_road distance
				float distance =fabs(tower_y_location- section_start_y);

				//judge whether the range cover the road_section
				bool inside_range = true;
				if (distance < attack_range) {
					if (tower_section_start_distance > attack_range&&
						tower_section_final_distance > attack_range) {
						inside_range = false;
					}
					else { inside_range = true; }

				}
				else { inside_range = false; }


				if (inside_range) {


					bool out_left_boundary = (tower_x_location < section_left);
					bool out_right_boundary = (tower_x_location > section_right);
					//not the above two -> in the boundary

					float half_range = powf(attack_range*attack_range - distance*distance, 0.5);

					int projected_distance = get_accumulate_path_distance(_section); //calculate the distance accumulate before _section
					int section_projected_distance = (int)fabs(tower_x_location - section_start_x);
					projected_distance += section_projected_distance;

					if ((!out_left_boundary) && (!out_right_boundary)) {//in_the boundary

						int left_range_cover = ((int)fabs(section_left - tower_x_location) <= (int)half_range) ? //choose the small one
							(int)fabs(section_left - tower_x_location) : (int)half_range;
						int right_range_cover = ((int)fabs(section_right - tower_x_location) <= (int)half_range) ? //choose the small one
							(int)fabs(section_right - tower_x_location) : (int)half_range;

						if (path[_section].get_direction() == Direction::LEFT) {
							valid_attack_range_number_of_a_tower++;
							Towers_attack_range_1D[_label].resize(valid_attack_range_number_of_a_tower);
							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].start_d = projected_distance - right_range_cover;
							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].terminate_d = projected_distance + left_range_cover;

						}
						else if (path[_section].get_direction() == Direction::RIGHT) {
							valid_attack_range_number_of_a_tower++;
							Towers_attack_range_1D[_label].resize(valid_attack_range_number_of_a_tower);
							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].start_d = projected_distance - left_range_cover;
							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].terminate_d = projected_distance + right_range_cover;
						}

					}
					else if (out_left_boundary) {

						if (path[_section].get_direction() == Direction::LEFT) {
							valid_attack_range_number_of_a_tower++;
							Towers_attack_range_1D[_label].resize(valid_attack_range_number_of_a_tower);

							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].start_d =
								(
									projected_distance - (int)half_range <=
									projected_distance - (int)fabs(tower_x_location - section_right)
								) ?
								(projected_distance - (int)half_range) :
								(projected_distance - (int)fabs(tower_x_location - section_right));


							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].terminate_d =
								projected_distance - (int)fabs(tower_x_location - section_left);
						}



						else if (path[_section].get_direction() == Direction::RIGHT) {
							valid_attack_range_number_of_a_tower++;
							Towers_attack_range_1D[_label].resize(valid_attack_range_number_of_a_tower);

							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].start_d =
								projected_distance - (int)fabs(tower_x_location - section_left);

							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].terminate_d =
								(
									projected_distance + (int)half_range - 2 * (int)fabs(tower_x_location - section_left) <=
									projected_distance + (int)fabs(tower_x_location - section_right) - 2 * (int)fabs(tower_x_location - section_left)
								) ?
								(projected_distance + (int)half_range - 2 * (int)fabs(tower_x_location - section_left)) :
								(projected_distance + (int)fabs(tower_x_location - section_right) - 2 * (int)fabs(tower_x_location - section_left));

						}


					}
					else if (out_right_boundary) {

						if (path[_section].get_direction() == Direction::LEFT) {
							valid_attack_range_number_of_a_tower++;
							Towers_attack_range_1D[_label].resize(valid_attack_range_number_of_a_tower);

							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].start_d =
								projected_distance - (int)fabs(tower_x_location - section_right);

							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].terminate_d =
								(
									projected_distance + (int)half_range - 2 * (int)fabs(tower_x_location - section_right) <=
									projected_distance + (int)fabs(tower_x_location - section_left) - 2 * (int)fabs(tower_x_location - section_right)
								) ?
								(projected_distance + (int)half_range - 2 * (int)fabs(tower_x_location - section_right)) :
								(projected_distance + (int)fabs(tower_x_location - section_left) - 2 * (int)fabs(tower_x_location - section_right));
						}



						else if (path[_section].get_direction() == Direction::RIGHT) {
							valid_attack_range_number_of_a_tower++;
							Towers_attack_range_1D[_label].resize(valid_attack_range_number_of_a_tower);

							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].start_d =
								(
									projected_distance - (int)half_range <=
									projected_distance - (int)fabs(tower_x_location - section_left)
								) ?
								(projected_distance - (int)half_range) :
								(projected_distance - (int)fabs(tower_x_location - section_left));

							Towers_attack_range_1D[_label][valid_attack_range_number_of_a_tower - 1].terminate_d =
								projected_distance - (int)fabs(tower_x_location - section_right);

						}

					}
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
	for (int i = 0; i < simulated_Enemies.size(); i++) {
		simulated_Enemies[i]->progress();
	}

	for (int i = 0; i < simulated_Towers.size(); i++) {
		if (simulated_Towers[i] != NULL) {
			simulated_Enemies[i]->progress();
		}
	}
}
void Attack_Calculator::init_set_simulated_Enemies() {
	simulated_Enemies.resize(Enemies.size());
	for (int i = 0; i < simulated_Enemies.size(); i++) {
		simulated_Enemies[i] = new Simulated_Enemy(
			i,
			Enemies[i]->get_life(),
			Enemies[i]->get_speed(),
			Enemies[i]->get_d_location()
			);
	}

}
void Attack_Calculator::init_set_simulated_Towers() {
	simulated_Towers.resize(Towers.size());
	for (int i = 0; i < simulated_Towers.size(); i++) {
		if (!(Towers[i] == NULL)) {
			simulated_Towers[i] = new Simulated_Tower(
				Towers[i]->get_tower_type(),
				Towers[i]->get_attack_range(),
				Towers[i]->get_special_attack_span(),
				Towers[i]->get_attack_cd(),
				Towers[i]->get_attack_damage(),
				Towers[i]->get_special_attack_damage()
			);
		}
	}


}





