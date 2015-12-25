#pragma once
//==========================�]�p===================================
////�C���i�i(�ɶ��޲z) -> �ϵ{���H�ۮɶ��]�_��
//**�`�ޮɶ�
//���JEnemyManager���ĤH�w�Ƹ��
//���JTower��att_list
//�x�s�b Result_Loader �N��ƶǨ� Screen �e�{�����a
//�N�𪺧����ɨ�P�ؼ��ഫ���ʵe(�ǳƨ�Screen�M�X)
//**�p��ɨϥήɶ�������
//**��M�ɨϥ�SDL_GetTicks()���o�ɶ��A�P�ɶ����������
//�ɶ��T�w�ϥ�Unit64

//=================================================================




/**************************���D***********************************/


/*****************************************************************/


#include "SDL.h"
#include "Attack_Calculator.h"
#include "Result_Loader.h"

using namespace std;

class Progress_Manager {
public:
protected:
public:
	Uint64 time_pass;
	const Uint64 unit_time;
	Attack_Calculator att_calculator;
	vector<Tower&> tow_set;
	vector<Enemy&> em_set;

	vector<Tower&>& progress_tow(const Uint64);
	vector<Enemy&>& progress_em(const Uint64);




};