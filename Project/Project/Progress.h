#pragma once
//==========================設計===================================
////遊戲進展(時間管理) -> 使程式隨著時間跑起來
//**總管時間
//載入EnemyManager的敵人安排資料
//載入Tower的att_list
//儲存在 Result_Loader 將資料傳到 Screen 呈現給玩家
//將塔的攻擊時刻與目標轉換成動畫(準備到Screen映出)
//**計算時使用時間模擬器
//**放映時使用SDL_GetTicks()取得時間再與時間模擬器比對
//時間固定使用Unit64

//=================================================================




/**************************問題***********************************/


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