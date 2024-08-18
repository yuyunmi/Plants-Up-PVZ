#pragma once

#include"Math.h"
#include"World.h"

/*����������ʵ��*/

using namespace std;

enum Buff { ATTACK, POWER, SPEED, HP };

class Upgrage
{
public:
	int ID = 0;//������
	float value;//������ֵ
	int feature;//��������

	void activate();//����
	void buff_print();//��Ⱦ���
	void init_data(int id);//�����ʼ��
};


Upgrage card[3];


//�����ʼ��
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


//���漤��
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
	//����Ѫ������
	case HP: {
		P1.hp += value;
		if (P1.hp > 100) {
			P1.hp = 100;
		}
		break;
	}
	}
}


//������ʾ
void Upgrage::buff_print()
{
	if (ID == 0) {
		switch (feature)
		{
		case ATTACK: {
			out_txt("����������: %d %%", value, 180, 370, 20);
			break;
		}
		case POWER: {
			out_txt("�����ȡ����: %d %%", value, 180, 370, 20);
			break;
		}
		case SPEED: {
			out_txt("�����ٶ�����: %d %%", value, 180, 370, 20);
			break;
		}
		case HP: {
			out_txt("Ѫ���ظ�: %d ", value, 180, 370, 20);
			break;
		}
		}
	}

	else if (ID == 1) {
		switch (feature){
		case ATTACK: {
			out_txt("����������: %d %%", value, 430, 370, 20);
			break;
		}
		case POWER: {
			out_txt("�����ȡ����: %d %%", value, 430, 370, 20);
			break;
		}
		case SPEED: {
			out_txt("�����ٶ�����: %d %%", value, 430, 370, 20);
			break;
		}
		case HP: {
			out_txt("Ѫ���ظ�: %d ", value, 430, 370, 20);
			break;
		}
		}
	}

	else if (ID == 2) {

		switch (feature){
		case ATTACK: {
			out_txt("����������: %d %%", value, 680, 370, 20);
			break;
		}
		case POWER: {
			out_txt("�����ȡ����: %d %%", value, 680, 370, 20);
			break;
		}
		case SPEED: {
			out_txt("�����ٶ�����: %d %%", value, 680, 370, 20);
			break;
		}
		case HP: {
			out_txt("Ѫ���ظ�: %d ", value, 680, 370, 20);
			break;
		}
		}
	}
}

