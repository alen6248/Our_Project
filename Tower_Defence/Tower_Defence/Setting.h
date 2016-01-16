#pragma once



#include "Abstract_Enemy.h"
#include "FastEnemy.h"
#include "StrongEnemy.h"
#include "BossEnemy.h"
#include "Map.h"
#include <vector>



class Setting {
public:
	Setting();
	~Setting();

	//map
	Map& get_map();

	//enemy
	void init_set_Enemies();
	void inti_set_enemy_life();
	void init_set_enemy_speed();
	vector<Abstract_Enemy*>& get_Enemies(int round);

	int get_enemy_life(Enemy_Type _enemy_type, int _level) const;
	int get_enemy_speed(Enemy_Type _enemy_type, int _level) const;


	//tower
	void init_set_tower_range();
	void init_set_tower_damage();
	void init_set_tower_attack_cd();
	void init_set_ice_tower_special_attack_span();
	void init_set_poison_tower_special_attack_span();
	void init_set_poison_tower_special_attack_damage();

	float get_tower_range(TowerType _tower_type,int _level) const;
	int get_tower_damage(TowerType _tower_type, int _level) const;
	int get_attack_cd(TowerType _tower_type, int _level) const;
	int get_ice_tower_special_attack_span(int _level) const;
	int get_poison_tower_special_attack_span(int _level) const;
	int get_poison_tower_special_attack_damage(int _level) const;


private:
	//map
	Map map;

	//enemy
	vector<vector<Abstract_Enemy*>>  Enemies;  //[round][sequence]
	vector<vector<int>> enemy_life;	// [enemy_type][level]
	vector<vector<int>> enemy_speed;	//[enemy_type][level]

	//tower
	vector<vector<float>> tower_range;
	vector<vector<int>> tower_damage;
	vector<vector<int>> tower_attack_cd;
	vector<int> ice_tower_special_attack_span;
	vector<int> poison_tower_special_attack_span;
	vector<int> poison_tower_special_attack_damage;

};

Setting::Setting() :map(SCREEN_WIDTH, SCREEN_HEIGHT) /*map*/ {
	//enemy
	init_set_Enemies();
	inti_set_enemy_life();
	init_set_enemy_speed();

	//tower
	init_set_tower_range();
	init_set_tower_damage();
	init_set_tower_attack_cd();
	init_set_ice_tower_special_attack_span();
	init_set_poison_tower_special_attack_span();
	init_set_poison_tower_special_attack_damage();

}
Setting::~Setting(){

}
Map& Setting::get_map() {
	return map;
}
void Setting::init_set_Enemies() {
	
	Enemies.resize(5); //all round number

	//round 1
	Enemies[0].resize(4); //[round][label]
	Enemies[0][0] = new FastEnemy(1, 100, 20, 0);
	Enemies[0][1] = new StrongEnemy(1, 100, 10, 5);
	Enemies[0][2] = new BossEnemy(1, 100, 7,20);
	Enemies[0][3] = new BossEnemy(1, 100, 7, 50);

	
}
vector<Abstract_Enemy*>& Setting::get_Enemies(int round) {
	return Enemies[round - 1];
}
//enemy_set_function
void Setting::inti_set_enemy_life() { // [enemy_type][level]

	enemy_life.resize((int)Enemy_Type::TOTAL_ENEMY_TYPE);

	for (int _type = 0; _type < (int)Enemy_Type::TOTAL_ENEMY_TYPE; _type++) {
		enemy_life[_type].resize(5); //level: 1,2,3,4  //no 0
	}


	enemy_life[(int)Enemy_Type::STRONG_ENEMY][1] = 100;
	enemy_life[(int)Enemy_Type::STRONG_ENEMY][2] = 120;
	enemy_life[(int)Enemy_Type::STRONG_ENEMY][3] = 140;
	enemy_life[(int)Enemy_Type::STRONG_ENEMY][4] = 160;

	enemy_life[(int)Enemy_Type::FAST_ENEMY][1] = 60;
	enemy_life[(int)Enemy_Type::FAST_ENEMY][2] = 70;
	enemy_life[(int)Enemy_Type::FAST_ENEMY][3] = 80;
	enemy_life[(int)Enemy_Type::FAST_ENEMY][4] = 90;

	enemy_life[(int)Enemy_Type::BOSS_ENEMY][1] = 300;
	enemy_life[(int)Enemy_Type::BOSS_ENEMY][2] = 400;
	enemy_life[(int)Enemy_Type::BOSS_ENEMY][3] = 500;
	enemy_life[(int)Enemy_Type::BOSS_ENEMY][4] = 600;



}
void Setting::init_set_enemy_speed() {
	enemy_speed.resize((int)Enemy_Type::TOTAL_ENEMY_TYPE);

	for (int _type = 0; _type < (int)Enemy_Type::TOTAL_ENEMY_TYPE; _type++) {
		enemy_speed[_type].resize(5); //level: 1,2,3,4  //no 0
	}

	enemy_speed[(int)Enemy_Type::STRONG_ENEMY][1] = 10;
	enemy_speed[(int)Enemy_Type::STRONG_ENEMY][2] = 10;
	enemy_speed[(int)Enemy_Type::STRONG_ENEMY][3] = 10;
	enemy_speed[(int)Enemy_Type::STRONG_ENEMY][4] = 10;

	enemy_speed[(int)Enemy_Type::FAST_ENEMY][1] = 16;
	enemy_speed[(int)Enemy_Type::FAST_ENEMY][2] = 18;
	enemy_speed[(int)Enemy_Type::FAST_ENEMY][3] = 20;
	enemy_speed[(int)Enemy_Type::FAST_ENEMY][4] = 22;

	enemy_speed[(int)Enemy_Type::BOSS_ENEMY][1] = 6;
	enemy_speed[(int)Enemy_Type::BOSS_ENEMY][2] = 6;
	enemy_speed[(int)Enemy_Type::BOSS_ENEMY][3] = 6;
	enemy_speed[(int)Enemy_Type::BOSS_ENEMY][4] = 6;

}
//tower_set_function
void Setting::init_set_tower_range() { //[tower_type][level]
	tower_range.resize((int)TowerType::TOTAL_TOWER_TYPE);

	for (int _type = 0; _type < (int)TowerType::TOTAL_TOWER_TYPE; _type++) {
		tower_range[_type].resize(5); //level: 1,2,3,4  //no 0
	}

	tower_range[(int)TowerType::FIRE_TOWER][1] = 200.0;
	tower_range[(int)TowerType::FIRE_TOWER][2] = 240.0;
	tower_range[(int)TowerType::FIRE_TOWER][3] = 280.0;
	tower_range[(int)TowerType::FIRE_TOWER][4] = 320.0;

	tower_range[(int)TowerType::ICE_TOWER][1] = 200.0;
	tower_range[(int)TowerType::ICE_TOWER][2] = 240.0;
	tower_range[(int)TowerType::ICE_TOWER][3] = 280.0;
	tower_range[(int)TowerType::ICE_TOWER][4] = 320.0;

	tower_range[(int)TowerType::POISON_TOWER][1] = 200.0;
	tower_range[(int)TowerType::POISON_TOWER][2] = 240.0;
	tower_range[(int)TowerType::POISON_TOWER][3] = 280.0;
	tower_range[(int)TowerType::POISON_TOWER][4] = 320.0;

}
void Setting::init_set_tower_damage() {
	tower_damage.resize((int)TowerType::TOTAL_TOWER_TYPE);

	for (int _type = 0; _type < (int)TowerType::TOTAL_TOWER_TYPE; _type++) {
		tower_damage[_type].resize(5); //level: 1,2,3,4  //no 0
	}

	tower_damage[(int)TowerType::FIRE_TOWER][1] = 20;
	tower_damage[(int)TowerType::FIRE_TOWER][1] = 30;
	tower_damage[(int)TowerType::FIRE_TOWER][1] = 40;
	tower_damage[(int)TowerType::FIRE_TOWER][1] = 60;

	tower_damage[(int)TowerType::ICE_TOWER][1] = 10;
	tower_damage[(int)TowerType::ICE_TOWER][2] = 15;
	tower_damage[(int)TowerType::ICE_TOWER][3] = 20;
	tower_damage[(int)TowerType::ICE_TOWER][4] = 25;

	tower_damage[(int)TowerType::POISON_TOWER][1] = 10;
	tower_damage[(int)TowerType::POISON_TOWER][2] = 15;
	tower_damage[(int)TowerType::POISON_TOWER][3] = 20;
	tower_damage[(int)TowerType::POISON_TOWER][4] = 25;

}
void Setting::init_set_tower_attack_cd() {
	tower_attack_cd.resize((int)TowerType::TOTAL_TOWER_TYPE);

	for (int _type = 0; _type < (int)TowerType::TOTAL_TOWER_TYPE; _type++) {
		tower_attack_cd[_type].resize(5); //level: 1,2,3,4  //no 0
	}
	//unit : frame
	tower_attack_cd[(int)TowerType::FIRE_TOWER][1] = 15;
	tower_attack_cd[(int)TowerType::FIRE_TOWER][1] = 15;
	tower_attack_cd[(int)TowerType::FIRE_TOWER][1] = 15;
	tower_attack_cd[(int)TowerType::FIRE_TOWER][1] = 15;

	tower_attack_cd[(int)TowerType::ICE_TOWER][1] = 15;
	tower_attack_cd[(int)TowerType::ICE_TOWER][2] = 15;
	tower_attack_cd[(int)TowerType::ICE_TOWER][3] = 15;
	tower_attack_cd[(int)TowerType::ICE_TOWER][4] = 15;

	tower_attack_cd[(int)TowerType::POISON_TOWER][1] = 15;
	tower_attack_cd[(int)TowerType::POISON_TOWER][2] = 15;
	tower_attack_cd[(int)TowerType::POISON_TOWER][3] = 15;
	tower_attack_cd[(int)TowerType::POISON_TOWER][4] = 15;

}
void Setting::init_set_ice_tower_special_attack_span() { //[level]
	ice_tower_special_attack_span.resize(5); //level: 1,2,3,4  //no 0

	ice_tower_special_attack_span[1] = 50;
	ice_tower_special_attack_span[2] = 60;
	ice_tower_special_attack_span[3] = 70;
	ice_tower_special_attack_span[4] = 80;

}
void Setting::init_set_poison_tower_special_attack_span() {
	poison_tower_special_attack_span.resize(5); //level: 1,2,3,4  //no 0

	poison_tower_special_attack_span[1] = 50;
	poison_tower_special_attack_span[2] = 55;
	poison_tower_special_attack_span[3] = 60;
	poison_tower_special_attack_span[4] = 65;
}
void Setting::init_set_poison_tower_special_attack_damage() {
	poison_tower_special_attack_damage.resize(5); //level: 1,2,3,4  //no 0

	poison_tower_special_attack_damage[1] = 1;
	poison_tower_special_attack_damage[2] = 2;
	poison_tower_special_attack_damage[3] = 3;
	poison_tower_special_attack_damage[4] = 4;
}


//enemy_get_function
int Setting::get_enemy_life(Enemy_Type _enemy_type, int _level) const {
	return enemy_life[(int)_enemy_type][_level];
}
int Setting::get_enemy_speed(Enemy_Type _enemy_type, int _level) const {
	return enemy_speed[(int)_enemy_type][_level];
}

//tower_get_function
float Setting::get_tower_range(TowerType _tower_type, int _level) const {
	return tower_range[(int)_tower_type][_level];
}
int Setting::get_tower_damage(TowerType _tower_type, int _level) const {
	return tower_damage[(int)_tower_type][_level];
}
int Setting::get_attack_cd(TowerType _tower_type, int _level) const {
	return tower_attack_cd[(int)_tower_type][_level];
}
int Setting::get_ice_tower_special_attack_span(int _level) const {
	return ice_tower_special_attack_span[_level];
}
int Setting::get_poison_tower_special_attack_span(int _level) const {
	return poison_tower_special_attack_span[_level];
}
int Setting::get_poison_tower_special_attack_damage(int _level) const {
	return poison_tower_special_attack_damage[_level];
}


