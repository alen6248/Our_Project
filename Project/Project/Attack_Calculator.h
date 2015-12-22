#pragma once
//==========================�]�p===================================

//=================================================================




/**************************���D***********************************/
//�o�X���Ӷ𪺧����M��
//Attack_Manager �\��O�_�]�p�b��class���� ?
//�ϥ�vector������������

/*****************************************************************/


#include "Enemy.h"
#include "Tower.h"


using namespace std;

class Attack_Calculator {
private:
	enum Attack_Type{Strong,Fast,First,Last,Auto} att_type;
public:
	Attack_Calculator();
	~Attack_Calculator();
	float tow_em_distance(Tower* tow,Enemy* em);
	void enrol_att_list(Tower* tow, Enemy* em);


protected:
};