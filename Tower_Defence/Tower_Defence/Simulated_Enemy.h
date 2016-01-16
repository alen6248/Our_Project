#pragma once


class Simulated_Enemy {
public:
	Simulated_Enemy(int _label,int _life,int _speed,int _enter_delay);
	~Simulated_Enemy();
	void progress();
	bool judge_survive();

	bool judge_enter_path();

private:
	int label;
	int life;
	bool survive;
	int speed;
	int d_location; //one dimension location

	//enter_delay
	int enter_delay; //unit : frame 
	int enter_delay_left;
	bool enter_path;



};


Simulated_Enemy::Simulated_Enemy(
	int _label, 
	int _life, 
	int _speed, 
	int _enter_delay
	):
		label(_label),
		life(_life),
		speed(_speed),
		d_location(0),
		enter_delay(_enter_delay),
		enter_delay_left(enter_delay),
		enter_path(false)
{

}
Simulated_Enemy::~Simulated_Enemy() {

}
void Simulated_Enemy::progress() {
	if (enter_path) {
		d_location += speed;
	}
	else {
		enter_delay_left--;
		if (enter_delay_left < 0) {
			enter_delay_left = 0;
		}
		judge_enter_path();
	}
}
bool Simulated_Enemy::judge_survive() {
	if (life > 0) {
		survive = true;
	}
	else { survive = false; }
	return survive;
}
bool Simulated_Enemy::judge_enter_path() {
	enter_path = (enter_delay_left == 0);
	return enter_path;
}





