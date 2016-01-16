//#pragma once
//enemy_image_width is 80 pixels
#ifndef _BOSS_ENEMY
#define _BOSS_ENEMY

#include "Abstract_Enemy.h"

extern const string ENEMY_DIR_PATH;
extern const string ENEMY_PATH;
extern const string BOSS_ENEMY_IMAGE;

//const int BOSS_ENEMY_IMAGE_WIDTH = 80;

class BossEnemy :public Abstract_Enemy {
public:
	BossEnemy(int level, int _life, int _speed, int _enter_delay);
	~BossEnemy();
	virtual void render();
	virtual void load_enemy_texture(int level, SDL_BlendMode blending, Uint8 alpha);
	
	//tower_image_clip_list
	//BossEnemy declare another clip list in derived class, and use virtual function to render.
	//static vector<vector<vector<SDL_Rect*>>>& get_boss_enemy_image_clip_list();
	//static void set_boss_enemy_image_clip_list();

private:
	//static vector<vector<vector<SDL_Rect*>>> boss_enemy_image_clip_list;
	bool survive;

};
BossEnemy::BossEnemy(int level, int _life, int _speed, int _enter_delay) :
	Abstract_Enemy(ENEMY_DIR_PATH + STRONG_ENEMY_IMAGE, ENEMY_DIR_PATH + ENEMY_PATH, level, _life, _speed,_enter_delay), survive(true) {

	load_enemy_texture(get_level(), SDL_BLENDMODE_BLEND, 255);
}
BossEnemy::~BossEnemy() { //call Abstract_Enemy destructor is enough

}
void BossEnemy::load_enemy_texture(int level, SDL_BlendMode blending, Uint8 alpha) {
	get_enemy_texture()->loadFromFile(ENEMY_DIR_PATH + BOSS_ENEMY_IMAGE);
	get_enemy_texture()->setBlendMode(blending);
	get_enemy_texture()->setAlpha(alpha);
	set_level(level);
}
void BossEnemy::render() {
	get_enemy_texture()->render(get_x_location(), get_y_location(), 
		get_enemy_image_clip_list()[get_enemy_state()][get_path()[get_path_phase()].get_direction()][get_foot_step()]);
}
//static function
//vector<vector<vector<SDL_Rect*>>>& BossEnemy::get_boss_enemy_image_clip_list() {
//	return boss_enemy_image_clip_list;
//}
//void BossEnemy::set_boss_enemy_image_clip_list() { 
//	boss_enemy_image_clip_list.resize(3);
//	for (int i = 0; i < 3; i++) {
//		boss_enemy_image_clip_list[i].resize(4);
//		for (int j = 0; j < 4; j++) {
//			boss_enemy_image_clip_list[i][j].resize(3);
//		}
//	}
//
//	for (int _state = 0; _state < TOTAL_STATE; _state++) {
//		for (int _direction = 0; _direction < TOTAL_DIRECTION; _direction++) {
//			for (int _step = 0; _step < TOTAL_STEP; _step++) {
//				boss_enemy_image_clip_list[_state][_direction][_step]->x = _direction * 3 * ENEMY_IMAGE_WIDTH + _step * ENEMY_IMAGE_WIDTH;
//				boss_enemy_image_clip_list[_state][_direction][_step]->y = _state*ENEMY_IMAGE_WIDTH;
//				boss_enemy_image_clip_list[_state][_direction][_step]->w = ENEMY_IMAGE_WIDTH;
//				boss_enemy_image_clip_list[_state][_direction][_step]->h = ENEMY_IMAGE_WIDTH;
//			}
//		}
//	}
//}




#endif // !_STRONG_ENEMY