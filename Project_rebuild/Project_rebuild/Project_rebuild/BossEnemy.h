//#pragma once
//Thouth there is nothing new than Abstract_Enemy now, 
//it's more flexible if want to develop new features of Enemy in the future.
#ifndef _BOSS_ENEMY
#define _BOSS_ENEMY

#include "Abstract_Enemy.h"

extern const string ENEMY_DIR_PATH;
extern const string ENEMY_PATH;
extern const string BOSS_ENEMY_IMAGE;

class BossEnemy :public Abstract_Enemy {
public:
	BossEnemy(int level, float hp, int _speed);
	~BossEnemy();
	virtual void render();
	virtual void load_enemy_texture(int level, SDL_BlendMode blending, Uint8 alpha);

private:
	bool survive;

};
BossEnemy::BossEnemy(int level, float hp, int _speed) :
	Abstract_Enemy(ENEMY_DIR_PATH + STRONG_ENEMY_IMAGE, ENEMY_DIR_PATH + ENEMY_PATH, level, hp, _speed), survive(true) {

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
	get_enemy_texture()->render(get_x_location(), get_y_location(), get_enemy_image_clip_list()[get_level()]);
}




#endif // !_STRONG_ENEMY