#pragma once
//==========================設計===================================
////Container
//製作一種型態，儲存Progress所需資料
//型態，儲存2D資料(放置塔的位置與敵人走的位置
//型態，儲存地圖與塔2D轉成1D的資料(在直線的哪個地方有放塔)
//型態，儲存直線的哪個區域是哪個塔的攻擊範圍

//=================================================================




/**************************問題***********************************/
//型態，儲存1D轉回2D的資料(哪個位置需要轉彎)-->直接用2D資料??

/*****************************************************************/

#include "Tower.h"




//型態，儲存2D資料(放置塔的位置與敵人走的位置
//使用方法: vector<Tower_Location>
enum Type_Exist { NonExist,Tower_Exist, Enemy_Exist }; //該型態是否存在物件
enum Location_type{Tower_type,Enemy_type,None};  //該位置放置的型態
//Location_type -> Type_Exist  
//None 必須對應到 NonExist
//Tower_type必須對應到 NonExist 或是 Tower_Exist
//Enemy_type必須對應到 NonExist 或是 Enemy_Exist

enum Turn {straigh, up, down,left,right };  //straight:直線無轉折

struct Location{
	int x;
	int y;
	Turn trun;

	Location_type loctype;  
	Type_Exist tpexist;
	//Location_type -> Type_Exist  
	//None 必須對應到 NonExist
	//Tower_type必須對應到 NonExist 或是 Tower_Exist
	//Enemy_type必須對應到 NonExist 或是 Enemy_Exist

	Tower* tow;		//None  或是 NonExist 需對應到NULL
	Enemy* em;		//None  或是 NonExist 需對應到NULL


};







//型態，儲存地圖與塔2D轉成1D的資料(在直線的哪個地方有放塔)
struct Path_1D {
	int d;
	Turn turn;
	Location_type loctype;
	Type_Exist tpexist;
	//Location_type -> Type_Exist  
	//None 必須對應到 NonExist
	//Tower_type必須對應到 NonExist 或是 Tower_Exist
	//Enemy_type必須對應到 NonExist 或是 Enemy_Exist

	Tower* tow;		//None  或是 NonExist 需對應到NULL
	Enemy* em;		//None  或是 NonExist 需對應到NULL

	struct Cover_by_Tower_Range {
		vector<Tower*> cover_tow_set;

	};
};
//型態，儲存直線的哪個區域是哪個塔的攻擊範圍
struct Range_Tower_1D {

};

