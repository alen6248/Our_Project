//#pragma once
//Thouth there is nothing new than Abstract_Enemy now, 
//it's more flexible if want to develop new features of Enemy in the future.
#ifndef _STRONG_ENEMY
#define _STRONG_ENEMY

#include "AbstractEnemy.h"

extern const string ENEMY_DIR_PATH ;
extern const string STRONG_ENEMY_IMAGE ;

class StrongEnemy :public Abstract_Enemy {
public:
	StrongEnemy(string path_file_path,int level, float hp, int _speed, int start_x_location, int start_y_location);
	~StrongEnemy();
	virtual void render();
	virtual void load_enemy_texture(int level, int x_location, int y_location, SDL_BlendMode blending, Uint8 alpha);

private:
	bool survive;

};
StrongEnemy::StrongEnemy(string path_file_path,int level, float hp, int _speed, int start_x_location, int start_y_location
	) :Abstract_Enemy(path_file_path,level, hp, _speed, start_x_location, start_y_location),survive(true) {
	load_enemy_texture(get_level(),Abstract_Enemy::get_path()[0].get_initial_x_location(), 
		Abstract_Enemy::get_path()[0].get_initial_y_location(),SDL_BLENDMODE_BLEND,255);
}
StrongEnemy::~StrongEnemy() { //call Abstract_Enemy destructor is enough

}
void StrongEnemy::load_enemy_texture(int level, int x_location, int y_location, SDL_BlendMode blending, Uint8 alpha) {
	get_enemy_texture()->loadFromFile(ENEMY_DIR_PATH + STRONG_ENEMY_IMAGE);
	get_enemy_texture()->setBlendMode(blending);
	get_enemy_texture()->setAlpha(alpha);
	set_x_location(x_location);
	set_y_location(y_location);
	set_level(level);
}
void StrongEnemy::render() {
	Abstract_Enemy::render();
}




#endif // !_STRONG_ENEMY
