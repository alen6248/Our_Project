#pragma once


class Simulated_Enemy {
public:
	Simulated_Enemy(int _label,int _life,int _speed,int _d_location);
	~Simulated_Enemy();
	void progress();
	bool judge_survive();



private:
	int label;
	int life;
	bool survive;
	int speed;
	int d_location; //one dimension location




};


Simulated_Enemy::Simulated_Enemy(int _label, int _life, int _speed, int _d_location):
	label(_label),life(_life),speed(_speed),d_location(_d_location)
{

}
Simulated_Enemy::~Simulated_Enemy() {

}
void Simulated_Enemy::progress() {
	d_location += speed;
}
bool Simulated_Enemy::judge_survive() {
	if (life > 0) {
		survive = true;
	}
	else { survive = false; }
	return survive;
}