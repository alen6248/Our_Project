#pragma once

#include "Abstract_Tower.h"
#include "Abstract_Enemy.h"
#include "LTimer.h"
#include "Input_Interface.h"
#include "StrongEnemy.h"
#include "FastEnemy.h"
#include "BossEnemy.h"

extern SDL_Renderer* gRenderer;

class Screen_Player {
public:
	Screen_Player(vector<Abstract_Tower*>&  _Towers, LTimer& _timer, Input_Interface& _input_interface);
	~Screen_Player();
	void Screen_Player_Core();
	void set_Enemies();
	void draw();
private:
	vector<Abstract_Tower*>&  Towers;
	vector<Abstract_Enemy*> Enemies; //modify later!!
	LTimer& timer;

	Input_Interface& input_interface;
	int Enemies_number;
	int time_length_per_frame; //unit: ms
};
Screen_Player::Screen_Player(vector<Abstract_Tower*>&  _Towers, LTimer& _timer, Input_Interface& _input_interface) :
		Towers(_Towers),timer(_timer),input_interface(_input_interface),time_length_per_frame(75)
{

}

Screen_Player::~Screen_Player() {
	for (int i = 0; i < Enemies_number; i++) {
		delete Enemies[i];
	}
	
}
void Screen_Player::Screen_Player_Core(){
	cout << "enter Screen_Player_Core" << endl;
	set_Enemies();

	Enemies; //debug

	while (1) {
		SDL_RenderClear(gRenderer);//Clear
		timer.start();
		input_interface.render();
		for (int i = 0; i < Enemies_number; i++) {
			Enemies[i]->go_forward(); //call virtual function
			if (Enemies[i]->in_the_terminal()){//do nothing
			}
			else {
				Enemies[i]->render();
			}
		}
		
		draw();

		SDL_Delay(time_length_per_frame - timer.getTicks());
		timer.stop();

	}//end of while


}//end of Core
void Screen_Player::set_Enemies(){
	Enemies.resize(3);

	Enemies[0] = new StrongEnemy(1,100,10);
	Enemies[1] = new FastEnemy(1, 100, 20);
	Enemies[2] = new BossEnemy(1, 100, 7);


	Enemies_number = Enemies.size();

}
void Screen_Player::draw() {
	SDL_RenderPresent(gRenderer);
}