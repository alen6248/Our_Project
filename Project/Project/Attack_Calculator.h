#pragma once
//==========================�]�p===================================
//�o�X���Ӷ𪺧����M��
//�N���|�Ԧ����u�A�Q��p�� (2���ন1��)
//�ϥ�vector������������
//
//=================================================================




/**************************���D***********************************/

//Attack_Manager �\��O�_�]�p�b��class���� ?
//strong �w�q����q�̦h�A�[�Wweak�w�q����q�̤�,�[�W�����Ҧ�:�̺C?
//�Nspeed�Php�ĦX���t�@���ܼ�"���n���I���{��" ?
/*****************************************************************/


#include "Enemy.h"
#include "Tower.h"


using namespace std;

class Attack_Calculator {
private:
	enum Attack_Type{Strong,Weak,Fast,First,Last,Auto} att_type;
public:
	Attack_Calculator();
	~Attack_Calculator();
	float tow_em_distance(Tower* tow,Enemy* em);
	void enrol_att_list(Tower* tow, Enemy* em);
	//�N�a�ϻP���ഫ�����u�����  //���гy�A��container�x�s
	//�o�X������[�\�d����
	//�o�X�𪺧����ɨ�P�ؼ�(1D)
	//�N�𪺧����ɨ�P�ؼ��ഫ��2D

protected:
};