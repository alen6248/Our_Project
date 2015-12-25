#pragma once

//====================�]�p=========================================
//Enemy �ѼƬ���
//Enemy���O
//StrongEnemy  FastEnemy  BossEnemy  �T�ؤ��P�ĤH


//=================================================================


/***************************���D********************************/
//��ɯŮɬO�_���ܩҥe���n?
//FireTower�O�_�令�����d��360��?
//FireTower �ɯūe1��1,�ɯū�d�����?
/***************************************************************/
using namespace std;
class Enemy {
	private:

	protected:
		int level;
		float hp;	//��q
		int speed;  //�H�e�������(integer)
		mutable int x;	//��m  
		mutable int y;
		mutable int d;  //�@����m
		mutable enum movedirection { up, down, left, right } mvdir; //�e�i��V


	public:

		Enemy(); //constructor
		~Enemy();//destructor
	

	
};

class StrongEnemy : public Enemy {
	private:
		char* em_name;
		bool survive;
		//SDL�Ϲ���

	protected:
	public:
};


class FastEnemy : public Enemy {
	private:
		char* em_name;
		bool survive;
		//SDL�Ϲ���
	protected:
	public:
};

class BossEnemy : public Enemy {
	private:
		char* em_name;
		bool survive;
		//SDL�Ϲ���
	protected:
	public:
};
