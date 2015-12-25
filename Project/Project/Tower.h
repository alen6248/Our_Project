#pragma once
//====================設計=========================================
//Enemy 參數紀錄
//Enemy類別
//StrongEnemy  FastEnemy  BossEnemy  三種不同敵人


//=================================================================




/*****************問題******************************************/
//塔升級時是否改變所占面積?   //暫定不改變
//FireTower是否改成攻擊範圍360度?  或是1對1攻擊?
//FireTower 升級前1對1,升級後範圍攻擊?
//Tower賣掉時可將錢全數回歸，因為遊戲重點在最佳化問題

/***************************************************************/

#include "Enemy.h"
#include "Result_Loader.h"
#include <vector>
using namespace std;
class Tower {
	private:



	protected:
		int lebel; //編號
		int level;
		float att_range; //攻擊範圍
		int x;//位置
		int y;
		int x_width; //塔的寬度  目前暫定為3*3
		int y_width;
		float att_cd; //攻擊間隔時間
		float att_damage; //攻擊傷害
		vector<int> build_money; //build_money[0]為建造塔所需錢   build_money[1]為第一次升級  以此類推
		bool can_att; //目前是否可以攻擊 ?  可以為1

	public:
		vector<Attack_Target&> tow_att_list; //該塔在不同時間的攻擊目標
		Tower();
		~Tower();
		static int tow_num; //塔的總數量
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