#pragma once
#pragma comment(lib,"winmm.lib")

#include<iostream>
#include<fstream>
#include<stdio.h>
#include<graphics.h>
#include<string>

#include"World.h"
#include"Tools.h"
#include"Control.h"


/*��Ϸ��Դ����*/

using namespace std;

#define WIN_Width 900
#define WIN_Hight 600


void load_source()
{
	char name[64];
	//������Ϸ����
	loadimage(&imgBg, _T("res/menus/bg.jpg"));

	//��ʼ����ʬ�Ķ�̬֡ͼƬ
	for (int i = 0; i < 22; i++) {
		sprintf_s(name, sizeof(name), _T("res/zm/%d.png"), i + 1);
		loadimage(&imageZombie[i], name);
	}

	//���������˶����㶹�ӵ�
	loadimage(&imgBulletNormal, _T("res/bullets/bullet_normal.png"));

	//�����㶹�ӵ�����ͼƬ
	loadimage(&imgBallBlast[3], "res/bullets/bullet_blast.png");
	for (int i = 0; i < 3; i++) {
		float k = (i + 1) * 0.2;
		loadimage(&imgBallBlast[i], "res/bullets/bullet_blast.png",
			imgBallBlast[3].getwidth() * k,
			imgBallBlast[3].getheight() * k, true);
	}

	//���ؽ�ʬ������ͼƬ
	for (int i = 0; i < 10; i++) {
		sprintf_s(name, sizeof(name), "res/zm_dead/%d.png", i + 1);
		loadimage(&imageZmDead[i], name);
	}

	//���ؽ�ʬ��ֲ���ͼƬ
	for (int i = 0; i < 21; i++) {
		sprintf_s(name, sizeof(name), "res/zm_eat/%d.png", i + 1);
		loadimage(&imageZmEat[i], name);
	}

	//����Ѳ��ʱ��ʬվ����ͼƬ
	for (int i = 0; i < 11; i++) {
		sprintf_s(name, sizeof(name), "res/zm_stand/%d.png", i + 1);
		loadimage(&imageZmStand[i], name);
	}

	//������Ҷ���
	for (int i = 0; i < 13; i++) {
		sprintf_s(name, sizeof(name), "res/player/%d.png", i + 1);
		loadimage(&PlayerStand[i], name);
	}

	//���ؾ�����
	loadimage(&up_ex, "res/menus/up_ex.png");

	//���������
	loadimage(&player_ui, "res/menus/player_ui.png", 400, 100);

	//������������
	loadimage(&upcard, "res/menus/up.png", 220, 300);

	//��һ��
	loadimage(&next_ui, "res/menus/next_ui.png", 450, 380);
	loadimage(&game_fail, "res/menus/fail.png", 450, 380);

	//������ͣ
	loadimage(&going, "res/menus/going.png", 40, 40);
	loadimage(&pauseui, "res/menus/pause.png", 450, 380);


	//������Ϸ��ͼ�δ���
	initgraph(WIN_Width, WIN_Hight);

	srand(time(NULL));

	//��������
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 30;
	f.lfWeight = 15;
	strcpy_s(f.lfFaceName, _T("Segoe UI Black"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	setbkmode(TRANSPARENT);
	setcolor(BLACK);

	GameStatus = MENU;
}

