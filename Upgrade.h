#pragma once

#include"Math.h"
#include"World.h"

/*升级词条的实现*/

using namespace std;

enum Buff { ATTACK, POWER, SPEED, HP };

class Upgrage
{
public:
	int ID = 0;//增益编号
	float value;//增益数值
	int feature;//增益种类

	void activate();//激活
	void buff_print();//渲染输出
	void init_data(int id);//增益初始化
};


Upgrage card[3];


//增益初始化
void Upgrage::init_data(int id)
{
	ID = id;
	feature = rand() % 4;
	switch (feature)
	{
	case ATTACK: {
		value = rand() % 20 + 1; break;
	}
	case POWER: {
		value = rand() % 10 + 1; break;
	}
	case SPEED: {
		value = rand() % 15 + 1; break;
	}
	case HP: {
		value = rand() % 15 + 1; break;
	}

	}
}


//增益激活
void Upgrage::activate()
{
	switch (feature)
	{
	case ATTACK: {
		P1.attack = P1.attack * (1 + value / 100);
		break;
	}
	case POWER: {
		P1.getex_rate = P1.getex_rate * (1 + value / 100);
		break;
	}
	case SPEED: {
		P1.shootspeed = P1.shootspeed * (1 - value / 100);
		break;
	}
	//限制血量上限
	case HP: {
		P1.hp += value;
		if (P1.hp > 100) {
			P1.hp = 100;
		}
		break;
	}
	}
}


//增益显示
void Upgrage::buff_print()
{
	if (ID == 0) {
		switch (feature)
		{
		case ATTACK: {
			out_txt("攻击力提升: %d %%", value, 180, 370, 20);
			break;
		}
		case POWER: {
			out_txt("经验获取提升: %d %%", value, 180, 370, 20);
			break;
		}
		case SPEED: {
			out_txt("攻击速度提升: %d %%", value, 180, 370, 20);
			break;
		}
		case HP: {
			out_txt("血量回复: %d ", value, 180, 370, 20);
			break;
		}
		}
	}

	else if (ID == 1) {
		switch (feature){
		case ATTACK: {
			out_txt("攻击力提升: %d %%", value, 430, 370, 20);
			break;
		}
		case POWER: {
			out_txt("经验获取提升: %d %%", value, 430, 370, 20);
			break;
		}
		case SPEED: {
			out_txt("攻击速度提升: %d %%", value, 430, 370, 20);
			break;
		}
		case HP: {
			out_txt("血量回复: %d ", value, 430, 370, 20);
			break;
		}
		}
	}

	else if (ID == 2) {

		switch (feature){
		case ATTACK: {
			out_txt("攻击力提升: %d %%", value, 680, 370, 20);
			break;
		}
		case POWER: {
			out_txt("经验获取提升: %d %%", value, 680, 370, 20);
			break;
		}
		case SPEED: {
			out_txt("攻击速度提升: %d %%", value, 680, 370, 20);
			break;
		}
		case HP: {
			out_txt("血量回复: %d ", value, 680, 370, 20);
			break;
		}
		}
	}
}

