//#pragma once
//Thouth there is nothing new than Abstract_Enemy now, 
//it's more flexible if want to develop new features of Enemy in the future.
#ifndef _FAST_ENEMY
#define _FAST_ENEMY

#include "Abstract_Enemy.h"

extern const string ENEMY_DIR_PATH;
extern const string ENEMY_PATH;
extern const string FAST_ENEMY_IMAGE;

class FastEnemy :public Abstract_Enemy {
public:
	FastEnemy(int level, float hp, int _speed);
	~FastEnemy();
	virtual void render();
	virtual void load_enemy_texture(int level, SDL_BlendMode blending, Uint8 alpha);

private:
	bool survive;

};
FastEnemy::FastEnemy(int level, float hp, int _speed) :
	Abstract_Enemy(ENEMY_DIR_PATH + STRONG_ENEMY_IMAGE, ENEMY_DIR_PATH + ENEMY_PATH, level, hp, _speed), survive(true) {

	load_enemy_texture(get_level(), SDL_BLENDMODE_BLEND, 255);
}
FastEnemy::~FastEnemy() { //call Abstract_Enemy destructor is enough

}
void FastEnemy::load_enemy_texture(int level, SDL_BlendMode blending, Uint8 alpha) {
	get_enemy_texture()->loadFromFile(ENEMY_DIR_PATH + FAST_ENEMY_IMAGE);
	get_enemy_texture()->setBlendMode(blending);
	get_enemy_texture()->setAlpha(alpha);
	set_level(level);
}
void FastEnemy::render() {
	get_enemy_texture()->render(get_x_location(), get_y_location(), 
		get_enemy_image_clip_list()[get_enemy_state()][get_path()[get_path_phase()].get_direction()][get_foot_step()]);
}




#endif // !_STRONG_ENEMY
