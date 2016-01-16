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
	Map& get_map();
	vector<Abstract_Enemy*>& get_Enemies(int round);
	void init_set_Enemies();


private:
	vector<vector<Abstract_Enemy*>>  Enemies;  //[round][sequence]
	Map map;
	


};

Setting::Setting() :map(SCREEN_WIDTH, SCREEN_HEIGHT) {
	init_set_Enemies();

}
Setting::~Setting(){

}
Map& Setting::get_map() {
	return map;
}
void Setting::init_set_Enemies() {
	//round 1
	Enemies.resize(1);
	Enemies[0].resize(3);
	Enemies[0][0] = new StrongEnemy(1, 100, 10);
	Enemies[0][1] = new FastEnemy(1, 100, 20);
	Enemies[0][2] = new BossEnemy(1, 100, 7);


}
vector<Abstract_Enemy*>& Setting::get_Enemies(int round) {
	return Enemies[round - 1];
}