#pragma once
//==========================�]�p===================================
////Container
//�s�@�@�ث��A�A�x�sProgress�һݸ��
//���A�A�x�s2D���(��m�𪺦�m�P�ĤH������m
//���A�A�x�s�a�ϻP��2D�ন1D�����(�b���u�����Ӧa�観���)
//���A�A�x�s���u�����Ӱϰ�O���Ӷ𪺧����d��

//=================================================================




/**************************���D***********************************/
//��m���O�@�ӹ���?
//�i��m�𪺤��n�h�j?   �ثe�ȩw�@�Ӷ�e��3*3������
//Attack_Target �P Attack_List  �n�Ыح��ث��A ?   vector<Attack_Target> �@��att_list
//�O�_�ݭnTower_Range_2D

/*****************************************************************/

#include "Tower.h"





enum Type_Exist { NonExist,Tower_Exist, Enemy_Exist }; //�ӫ��A�O�_�s�b����
enum Location_type{Tower_type,Enemy_type,None};  //�Ӧ�m��m�����A
//Location_type -> Type_Exist  
//None ���������� NonExist
//Tower_type���������� NonExist �άO Tower_Exist
//Enemy_type���������� NonExist �άO Enemy_Exist




//���A�A�x�s 1D �� 2D���(��m�𪺦�m�P�ĤH������m
//�D�鬰"�I(��m)"
//�ϥΤ�k: vector<Tower_Location>
struct Location{
	int x;
	int y;
	int d;  //1D ���
	enum Turn { straigh, up, down, left, right };  //straight:���u�L���
	Turn turn;

	Location_type loctype;  
	Type_Exist tpexist;
	//Location_type -> Type_Exist  
	//None ���������� NonExist
	//Tower_type���������� NonExist �άO Tower_Exist
	//Enemy_type���������� NonExist �άO Enemy_Exist

	Tower& tow;		//None  �άO NonExist �ݹ�����NULL
	Enemy& em;		//None  �άO NonExist �ݹ�����NULL
	vector<Tower*> tow_cover_set; //�b���I�Q���Ƕ𪺧����d��[�\��

};







//���A�A�x�s���u�����Ӱϰ�O���Ӷ𪺧����d��  
//�D�鬰"��"
//�ϥΤ�k  vector<Range_Tower_1D>
struct Tower_Range_1D {   //�Y�@�Ӷ�A�[�\1�����|�����Ǧa��
	 Tower* tow; 
	 vector<int> cover_location; //�Ҳ[�\���a��A�s���I���X
	 

};

//���A�A�x�s�����M��
//�D�鬰"�@�Ӷ�"
//��m�bTower����
//�ϥΤ�k vector<Attack_Target	>   //�@�Ӷ�b���P�ɶ�����������H
struct Attack_Target { 
	int t; //�ɶ�
	// Tower* tow;  //�]����m�b�𤧤��A�G���A�ŧi��
	vector<Enemy*> em_list;   //�d������i�����h��Enemy, �@��@�����Ȥ@��

};

//���A�A�x�s�Ҧ���Ҧ��ɶ��������M��
struct Attack_List {
	Tower& tow;
	vector<Attack_Target&>& tow_att_list;
};



//���A�A�x�s�i���ĤH��T

