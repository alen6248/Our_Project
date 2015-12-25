#pragma once
//==========================�]�p===================================
//�o�X���Ӷ𪺧����M��
//�N���|�Ԧ����u�A�Q��p�� (2���ন1��)
//�ϥ�vector������������
//�HSDL_GetTicks() ���o�ɶ�
//�ɶ��������A�b�p��ɨϥΡA��M�ɥι�ڮɶ��P�ɶ����������
//=================================================================




/**************************���D***********************************/

//Attack_Manager �\��O�_�]�p�b��class���� ?
//strong �w�q����q�̦h�A�[�Wweak�w�q����q�̤�,�[�W�����Ҧ�:�̺C?
//�Nspeed�Php�ĦX���t�@���ܼ�"���n���I���{��" ?
//�T�{�ɶ��w�q  //�w�g�B�z�n�ƾڦA��M�X�ӡA�j��B��t�׮t�����j�A�i���ۦP���ɶ����j?
//�ϧ_�t�~�w�q�@�خɶ����A?
//���`�N�Ǧ^���A�A�]��handle�OAttack_Calculator����
/*****************************************************************/


#include "Enemy.h"
#include "Tower.h"
#include "Result_Loader.h"
#include "SDL.h"

using namespace std;

class Attack_Calculator {
private:
	enum Attack_Type{Strong,Weak,Fast,First,Last,Auto} att_type;
public:
	vector<Tower&> Tower_Set; //����Tower���,�Ѧ�����ƭק蠟
	vector<Enemy&> Enemy_Set; //����Enemy���,�Ѧ�����ƭק蠟

	Attack_Calculator();
	~Attack_Calculator();
	float tow_em_distance(Tower* tow,Enemy* em);


	// vector<Attack_List>& enrol_att_list(Tower* tow, Enemy* em);

	//�N�a�ϻP���ഫ�����u�����  (2D -> 1D   x,y -> d)
	vector<Location&> calculate_1D_data (vector<Location&>);

	//�o�X������[�\�d����
	vector<Tower_Range_1D&> calculate_Tower_Range_1D(vector<Location&>);

	//�o�X�𪺧����ɨ�P�ؼСA���Tower������att_list (���A�� vector<Attack_Target>
	vector<Tower&> calculate_and_enrol_att_Target(vector<Location&>, Attack_Type);


	

	//�ɶ�������
	class Time_Simulator {
		const Uint64 unit_time; //�]�w���ɶ�  //�n�A�w�q�@�خɶ����A�M���B�z�ɶ�?
		Uint64 time_pass_simu;  //�x�s�ɶ�

		Uint64& time_progress(Uint64); //�C��progress�@�����ɶ�
	}tm_simulator;

protected:
};