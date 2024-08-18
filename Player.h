#pragma once

#include"World.h"
#include"Tools.h"

/*玩家类实现*/


//玩家的动态帧
IMAGE PlayerStand[13];

class Player
{
public:
	int hp = 100;//血量
	int x = 150, y = 180;//位置坐标
	int line = 2;//人物当前所处行数
	int frameindex = 0;//动作帧
	int lv;//等级

	float ex ;  //经验条
	float getex_rate;  //经验获取效率
	float shootspeed;  //射击速度
	float attack;  //伤害

	void MoveRight();//向右移动
	void MoveLeft();//向左移动
	void MoveUp();//向上移动
	void MoveDown();//向下移动
	void DrawPlayer();//动画渲染
	void PlayerLine(int pos);//行位置判定
};




//向左移动
void Player::MoveLeft()
{
	if (x > 120) {
		x -= 5;
	}
}


//向上移动
void Player::MoveUp()
{
	if (y > 100) {
		y -= 5;
	}
}


//向右移动
void Player::MoveRight()
{
	if (x < 800) {
		x += 5;
	}
}


//向下移动
void Player::MoveDown()
{
	if (y < 490) {
		y += 5;
	}
}


//人物绘制
void Player::DrawPlayer()
{
	IMAGE img = NULL;

	frameindex++;

	img = PlayerStand[frameindex %= 13];

	putimagePNG(x, y, &img);
	Sleep(15);
}


//位置判定
void Player::PlayerLine(int pos)
{
	if (0 < pos && pos < 160) { line = 0; }
	if (160 <= pos && pos < 250) { line = 1; }
	if (250 <= pos && pos < 360) { line = 2; }
	if (360 <= pos && pos < 450) { line = 3; }
	if (450 <= pos && pos < 490) { line = 4; }
}

