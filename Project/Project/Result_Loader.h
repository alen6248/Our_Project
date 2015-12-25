#pragma once
//==========================設計===================================
////Container
//製作一種型態，儲存Progress所需資料
//型態，儲存2D資料(放置塔的位置與敵人走的位置
//型態，儲存地圖與塔2D轉成1D的資料(在直線的哪個地方有放塔)
//型態，儲存直線的哪個區域是哪個塔的攻擊範圍

//=================================================================




/**************************問題***********************************/
//位置單位是一個像素?
//可放置塔的方格要多大?   目前暫定一個塔占用3*3的方格數
//Attack_Target 與 Attack_List  要創建哪種型態 ?   vector<Attack_Target> 作為att_list
//是否需要Tower_Range_2D

/*****************************************************************/

#include "Tower.h"





enum Type_Exist { NonExist,Tower_Exist, Enemy_Exist }; //該型態是否存在物件
enum Location_type{Tower_type,Enemy_type,None};  //該位置放置的型態
//Location_type -> Type_Exist  
//None 必須對應到 NonExist
//Tower_type必須對應到 NonExist 或是 Tower_Exist
//Enemy_type必須對應到 NonExist 或是 Enemy_Exist




//型態，儲存 1D 及 2D資料(放置塔的位置與敵人走的位置
//主體為"點(位置)"
//使用方法: vector<Tower_Location>
struct Location{
	int x;
	int y;
	int d;  //1D 資料
	enum Turn { straigh, up, down, left, right };  //straight:直線無轉折
	Turn turn;

	Location_type loctype;  
	Type_Exist tpexist;
	//Location_type -> Type_Exist  
	//None 必須對應到 NonExist
	//Tower_type必須對應到 NonExist 或是 Tower_Exist
	//Enemy_type必須對應到 NonExist 或是 Enemy_Exist

	Tower& tow;		//None  或是 NonExist 需對應到NULL
	Enemy& em;		//None  或是 NonExist 需對應到NULL
	vector<Tower*> tow_cover_set; //在該點被那些塔的攻擊範圍涵蓋到

};







//型態，儲存直線的哪個區域是哪個塔的攻擊範圍  
//主體為"塔"
//使用方法  vector<Range_Tower_1D>
struct Tower_Range_1D {   //某一個塔，涵蓋1維路徑的那些地方
	 Tower* tow; 
	 vector<int> cover_location; //所涵蓋的地方，連續的點集合
	 

};

//型態，儲存攻擊清單
//主體為"一個塔"
//放置在Tower之內
//使用方法 vector<Attack_Target	>   //一個塔在不同時間的的攻擊對象
struct Attack_Target { 
	int t; //時間
	// Tower* tow;  //因為放置在塔之內，故不再宣告塔
	vector<Enemy*> em_list;   //範圍攻擊可攻擊多個Enemy, 一對一攻擊僅一個

};

//型態，儲存所有塔所有時間的攻擊清單
struct Attack_List {
	Tower& tow;
	vector<Attack_Target&>& tow_att_list;
};



//型態，儲存進場敵人資訊

