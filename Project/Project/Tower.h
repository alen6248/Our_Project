#pragma once
//====================設計=========================================
//Enemy 參數紀錄
//Enemy類別
//StrongEnemy  FastEnemy  BossEnemy  三種不同敵人


//=================================================================




/*****************問題******************************************/
//塔升級時是否改變所占面積?
//FireTower是否改成攻擊範圍360度?
//FireTower 升級前1對1,升級後範圍攻擊?
/***************************************************************/

#include "Enemy.h"
#include <vector>
using namespace std;
class Tower {
	private:



	protected:
		int level;
		float att_range; //攻擊範圍
		int x;//位置
		int y;
		int x_width;
		int y_width;
		float att_cd; //攻擊間隔時間
		float att_damage; //攻擊傷害

	public:
		vector<vector<Enemy *>> att_list; //enemylist -> nth attack -> enemies
		Tower();
		~Tower();
};

class FireTower:public Tower {
	private:
		char* name;
		//SDL 圖像檔
	protected:
	public:
		FireTower();
		~FireTower();
		const char* const level_to_name(int level);

};

class IceTower :public Tower {
	private:


	protected:
	public:
	
};

class PoisonTower :public Tower {
	private:


	protected:
	public:
	
};