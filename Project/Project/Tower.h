#pragma once
//====================�]�p=========================================
//Enemy �ѼƬ���
//Enemy���O
//StrongEnemy  FastEnemy  BossEnemy  �T�ؤ��P�ĤH


//=================================================================




/*****************���D******************************************/
//��ɯŮɬO�_���ܩҥe���n?
//FireTower�O�_�令�����d��360��?
//FireTower �ɯūe1��1,�ɯū�d�����?
/***************************************************************/

#include "Enemy.h"
#include <vector>
using namespace std;
class Tower {
	private:



	protected:
		int level;
		float att_range; //�����d��
		int x;//��m
		int y;
		int x_width;
		int y_width;
		float att_cd; //�������j�ɶ�
		float att_damage; //�����ˮ`

	public:
		vector<vector<Enemy *>> att_list; //enemylist -> nth attack -> enemies
		Tower();
		~Tower();
};

class FireTower:public Tower {
	private:
		char* name;
		//SDL �Ϲ���
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