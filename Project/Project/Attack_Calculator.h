#pragma once
//==========================設計===================================

//=================================================================




/**************************問題***********************************/
//得出給個塔的攻擊清單
//Attack_Manager 功能是否設計在此class之內 ?
//使用vector紀錄攻擊順序

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