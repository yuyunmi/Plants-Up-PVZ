#pragma once
#include<iostream>

#include"World.h"
#include"Base.h"
#include"Control.h"
#include"Game.h"

/*��Ϸ��ѭ��*/

using namespace std;

#define WIN_Width 900
#define WIN_Hight 600

//������
int main()
{
	load_source();//��Դ�ļ�����

	while (1)
	{
		//��Ϸ״̬-���˵�
		if (GameStatus == MENU) {
			startUI();
		}
		//��Ϸ״̬-����
		else if (GameStatus == GOING) {
			Play_Game();
		}
		//��Ϸ״̬-��ͣ
		else if (GameStatus == PAUSE) {
			Pause_Game();
		}
		//��Ϸ״̬-����
		else if (GameStatus == UP) {
			Up_Game();
		}
		//��Ϸ״̬-��һ��
		else if (GameStatus == NEXT) {
			Next_Game();
		}
		//��Ϸ״̬-ʧ��
		else if (GameStatus == FAIL) {
			Fail_Game();
		}
	}

	system("pause");
	return 0;
}