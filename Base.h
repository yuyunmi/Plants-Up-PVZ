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


/*游戏资源加载*/

using namespace std;

#define WIN_Width 900
#define WIN_Hight 600


void load_source()
{
	char name[64];
	//加载游戏背景
	loadimage(&imgBg, _T("res/menus/bg.jpg"));

	//初始化僵尸的动态帧图片
	for (int i = 0; i < 22; i++) {
		sprintf_s(name, sizeof(name), _T("res/zm/%d.png"), i + 1);
		loadimage(&imageZombie[i], name);
	}

	//加载正常运动的豌豆子弹
	loadimage(&imgBulletNormal, _T("res/bullets/bullet_normal.png"));

	//加载豌豆子弹击中图片
	loadimage(&imgBallBlast[3], "res/bullets/bullet_blast.png");
	for (int i = 0; i < 3; i++) {
		float k = (i + 1) * 0.2;
		loadimage(&imgBallBlast[i], "res/bullets/bullet_blast.png",
			imgBallBlast[3].getwidth() * k,
			imgBallBlast[3].getheight() * k, true);
	}

	//加载僵尸死亡的图片
	for (int i = 0; i < 10; i++) {
		sprintf_s(name, sizeof(name), "res/zm_dead/%d.png", i + 1);
		loadimage(&imageZmDead[i], name);
	}

	//加载僵尸吃植物的图片
	for (int i = 0; i < 21; i++) {
		sprintf_s(name, sizeof(name), "res/zm_eat/%d.png", i + 1);
		loadimage(&imageZmEat[i], name);
	}

	//加载巡场时僵尸站立的图片
	for (int i = 0; i < 11; i++) {
		sprintf_s(name, sizeof(name), "res/zm_stand/%d.png", i + 1);
		loadimage(&imageZmStand[i], name);
	}

	//加载玩家动作
	for (int i = 0; i < 13; i++) {
		sprintf_s(name, sizeof(name), "res/player/%d.png", i + 1);
		loadimage(&PlayerStand[i], name);
	}

	//加载经验条
	loadimage(&up_ex, "res/menus/up_ex.png");

	//加载人物槽
	loadimage(&player_ui, "res/menus/player_ui.png", 400, 100);

	//加载升级卡槽
	loadimage(&upcard, "res/menus/up.png", 220, 300);

	//下一关
	loadimage(&next_ui, "res/menus/next_ui.png", 450, 380);
	loadimage(&game_fail, "res/menus/fail.png", 450, 380);

	//加载暂停
	loadimage(&going, "res/menus/going.png", 40, 40);
	loadimage(&pauseui, "res/menus/pause.png", 450, 380);


	//创建游戏的图形窗口
	initgraph(WIN_Width, WIN_Hight);

	srand(time(NULL));

	//设置字体
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

