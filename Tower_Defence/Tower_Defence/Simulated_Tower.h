#pragma once

#define DEBUG

#include "Abstract_Tower.h"
#include "FireTower.h"
#include "IceTower.h"
#include "PoisonTower.h"


class Simulated_Tower {
public:
	Simulated_Tower(
		TowerType _tower_type,
		float _attack_range,
		int _special_attack_span,
		int _attack_cd,
		int _attack_damage,
		int _poison_attack_damage
		);
	~Simulated_Tower();
	void progress();
	bool judge_can_attack();


private:
	TowerType tower_type;
	float attack_range;
	int special_attack_span; //unit : frame //always 0 for fire_tower
	int special_attack_span_left; //always 0 for fire_tower

	int attack_cd; //unit : frame
	int attack_cd_left; //the left time before next attack

	bool can_attack;


	int attack_damage;
	int poison_attack_damage; //for Poison_Tower //always 0 for !poison_tower
};

Simulated_Tower::Simulated_Tower(
	TowerType _tower_type,
	float _attack_range,
	int _special_attack_span,
	int _attack_cd,
	int _attack_damage,
	int _poison_attack_damage
	) :
	tower_type(_tower_type),
	attack_range(_attack_range),
	special_attack_span(_special_attack_span),
	attack_cd(attack_cd),
	attack_damage(_attack_damage),
	poison_attack_damage(_poison_attack_damage),
	special_attack_span_left(0),
	attack_cd_left(0),
	can_attack(true)
{

}

Simulated_Tower::~Simulated_Tower() {

}
bool Simulated_Tower::judge_can_attack() {
	can_attack = (attack_cd_left == 0);
#ifdef DEBUG
	assert(attack_cd_left >= 0);
#endif // DEBUG
	return can_attack;


}
void Simulated_Tower::progress() {
	attack_cd_left--;
	special_attack_span_left--;
}



