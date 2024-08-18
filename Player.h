#pragma once

#include"World.h"
#include"Tools.h"

/*�����ʵ��*/


//��ҵĶ�̬֡
IMAGE PlayerStand[13];

class Player
{
public:
	int hp = 100;//Ѫ��
	int x = 150, y = 180;//λ������
	int line = 2;//���ﵱǰ��������
	int frameindex = 0;//����֡
	int lv;//�ȼ�

	float ex ;  //������
	float getex_rate;  //�����ȡЧ��
	float shootspeed;  //����ٶ�
	float attack;  //�˺�

	void MoveRight();//�����ƶ�
	void MoveLeft();//�����ƶ�
	void MoveUp();//�����ƶ�
	void MoveDown();//�����ƶ�
	void DrawPlayer();//������Ⱦ
	void PlayerLine(int pos);//��λ���ж�
};




//�����ƶ�
void Player::MoveLeft()
{
	if (x > 120) {
		x -= 5;
	}
}


//�����ƶ�
void Player::MoveUp()
{
	if (y > 100) {
		y -= 5;
	}
}


//�����ƶ�
void Player::MoveRight()
{
	if (x < 800) {
		x += 5;
	}
}


//�����ƶ�
void Player::MoveDown()
{
	if (y < 490) {
		y += 5;
	}
}


//�������
void Player::DrawPlayer()
{
	IMAGE img = NULL;

	frameindex++;

	img = PlayerStand[frameindex %= 13];

	putimagePNG(x, y, &img);
	Sleep(15);
}


//λ���ж�
void Player::PlayerLine(int pos)
{
	if (0 < pos && pos < 160) { line = 0; }
	if (160 <= pos && pos < 250) { line = 1; }
	if (250 <= pos && pos < 360) { line = 2; }
	if (360 <= pos && pos < 450) { line = 3; }
	if (450 <= pos && pos < 490) { line = 4; }
}

