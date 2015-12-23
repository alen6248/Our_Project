#pragma once
//==========================�]�p===================================
////Container
//�s�@�@�ث��A�A�x�sProgress�һݸ��
//���A�A�x�s2D���(��m�𪺦�m�P�ĤH������m
//���A�A�x�s�a�ϻP��2D�ন1D�����(�b���u�����Ӧa�観���)
//���A�A�x�s���u�����Ӱϰ�O���Ӷ𪺧����d��

//=================================================================




/**************************���D***********************************/
//���A�A�x�s1D��^2D�����(���Ӧ�m�ݭn���s)-->������2D���??

/*****************************************************************/

#include "Tower.h"




//���A�A�x�s2D���(��m�𪺦�m�P�ĤH������m
//�ϥΤ�k: vector<Tower_Location>
enum Type_Exist { NonExist,Tower_Exist, Enemy_Exist }; //�ӫ��A�O�_�s�b����
enum Location_type{Tower_type,Enemy_type,None};  //�Ӧ�m��m�����A
//Location_type -> Type_Exist  
//None ���������� NonExist
//Tower_type���������� NonExist �άO Tower_Exist
//Enemy_type���������� NonExist �άO Enemy_Exist

enum Turn {straigh, up, down,left,right };  //straight:���u�L���

struct Location{
	int x;
	int y;
	Turn trun;

	Location_type loctype;  
	Type_Exist tpexist;
	//Location_type -> Type_Exist  
	//None ���������� NonExist
	//Tower_type���������� NonExist �άO Tower_Exist
	//Enemy_type���������� NonExist �άO Enemy_Exist

	Tower* tow;		//None  �άO NonExist �ݹ�����NULL
	Enemy* em;		//None  �άO NonExist �ݹ�����NULL


};







//���A�A�x�s�a�ϻP��2D�ন1D�����(�b���u�����Ӧa�観���)
struct Path_1D {
	int d;
	Turn turn;
	Location_type loctype;
	Type_Exist tpexist;
	//Location_type -> Type_Exist  
	//None ���������� NonExist
	//Tower_type���������� NonExist �άO Tower_Exist
	//Enemy_type���������� NonExist �άO Enemy_Exist

	Tower* tow;		//None  �άO NonExist �ݹ�����NULL
	Enemy* em;		//None  �άO NonExist �ݹ�����NULL

	struct Cover_by_Tower_Range {
		vector<Tower*> cover_tow_set;

	};
};
//���A�A�x�s���u�����Ӱϰ�O���Ӷ𪺧����d��
struct Range_Tower_1D {

};

