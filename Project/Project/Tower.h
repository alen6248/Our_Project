#pragma once
//====================�]�p=========================================
//Enemy �ѼƬ���
//Enemy���O
//StrongEnemy  FastEnemy  BossEnemy  �T�ؤ��P�ĤH


//=================================================================




/*****************���D******************************************/
//��ɯŮɬO�_���ܩҥe���n?   //�ȩw������
//FireTower�O�_�令�����d��360��?  �άO1��1����?
//FireTower �ɯūe1��1,�ɯū�d�����?
//Tower�汼�ɥi�N�����Ʀ^�k�A�]���C�����I�b�̨Τư��D

/***************************************************************/

#include "Enemy.h"
#include "Result_Loader.h"
#include <vector>
using namespace std;
class Tower {
	private:



	protected:
		int lebel; //�s��
		int level;
		float att_range; //�����d��
		int x;//��m
		int y;
		int x_width; //�𪺼e��  �ثe�ȩw��3*3
		int y_width;
		float att_cd; //�������j�ɶ�
		float att_damage; //�����ˮ`
		vector<int> build_money; //build_money[0]���سy��һݿ�   build_money[1]���Ĥ@���ɯ�  �H������
		bool can_att; //�ثe�O�_�i�H���� ?  �i�H��1

	public:
		vector<Attack_Target&> tow_att_list; //�Ӷ�b���P�ɶ��������ؼ�
		Tower();
		~Tower();
		static int tow_num; //���`�ƶq
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