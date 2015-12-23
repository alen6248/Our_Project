#pragma once
//==========================設計===================================
//得出給個塔的攻擊清單
//將路徑拉成直線，利於計算 (2維轉成1維)
//使用vector紀錄攻擊順序
//
//=================================================================




/**************************問題***********************************/

//Attack_Manager 功能是否設計在此class之內 ?
//strong 定義為血量最多，加上weak定義為血量最少,加上攻擊模式:最慢?
//將speed與hp融合成另一個變數"不好應付的程度" ?
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
	//將地圖與塔轉換成直線的函數  //須創造適當的container儲存
	//得出塔攻擊涵蓋範圍資料
	//得出塔的攻擊時刻與目標(1D)
	//將塔的攻擊時刻與目標轉換成2D

protected:
};