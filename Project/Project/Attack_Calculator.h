#pragma once
//==========================設計===================================
//得出給個塔的攻擊清單
//將路徑拉成直線，利於計算 (2維轉成1維)
//使用vector紀錄攻擊順序
//以SDL_GetTicks() 取得時間
//時間模擬器，在計算時使用，放映時用實際時間與時間模擬器比對
//=================================================================




/**************************問題***********************************/

//Attack_Manager 功能是否設計在此class之內 ?
//strong 定義為血量最多，加上weak定義為血量最少,加上攻擊模式:最慢?
//將speed與hp融合成另一個變數"不好應付的程度" ?
//確認時間定義  //已經處理好數據再放映出來，迴圈運算速度差異不大，可有相同的時間間隔?
//使否另外定義一種時間型態?
//須注意傳回型態，因為handle是Attack_Calculator物件
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
	vector<Tower&> Tower_Set; //取用Tower資料,供成員函數修改之
	vector<Enemy&> Enemy_Set; //取用Enemy資料,供成員函數修改之

	Attack_Calculator();
	~Attack_Calculator();
	float tow_em_distance(Tower* tow,Enemy* em);


	// vector<Attack_List>& enrol_att_list(Tower* tow, Enemy* em);

	//將地圖與塔轉換成直線的函數  (2D -> 1D   x,y -> d)
	vector<Location&> calculate_1D_data (vector<Location&>);

	//得出塔攻擊涵蓋範圍資料
	vector<Tower_Range_1D&> calculate_Tower_Range_1D(vector<Location&>);

	//得出塔的攻擊時刻與目標，更改Tower之內的att_list (型態為 vector<Attack_Target>
	vector<Tower&> calculate_and_enrol_att_Target(vector<Location&>, Attack_Type);


	

	//時間模擬器
	class Time_Simulator {
		const Uint64 unit_time; //設定單位時間  //要再定義一種時間型態專門處理時間?
		Uint64 time_pass_simu;  //儲存時間

		Uint64& time_progress(Uint64); //每次progress一次單位時間
	}tm_simulator;

protected:
};