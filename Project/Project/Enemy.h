#pragma once

//====================設計=========================================
//Enemy 參數紀錄
//Enemy類別
//StrongEnemy  FastEnemy  BossEnemy  三種不同敵人


//=================================================================


/***************************問題********************************/
//塔升級時是否改變所占面積?
//FireTower是否改成攻擊範圍360度?
//FireTower 升級前1對1,升級後範圍攻擊?
/***************************************************************/
using namespace std;
class Enemy {
	private:

	protected:
		int level;
		float hp;	//血量
		int speed;  //以畫素為單位(integer)
		mutable int x;	//位置  
		mutable int y;
		mutable int d;  //一維位置
		mutable enum movedirection { up, down, left, right } mvdir; //前進方向


	public:

		Enemy(); //constructor
		~Enemy();//destructor
	

	
};

class StrongEnemy : public Enemy {
	private:
		char* em_name;
		bool survive;
		//SDL圖像檔

	protected:
	public:
};


class FastEnemy : public Enemy {
	private:
		char* em_name;
		bool survive;
		//SDL圖像檔
	protected:
	public:
};

class BossEnemy : public Enemy {
	private:
		char* em_name;
		bool survive;
		//SDL圖像檔
	protected:
	public:
};
