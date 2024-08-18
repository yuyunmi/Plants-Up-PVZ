#pragma once

#include"Player.h"


/*全局变量以及存读档*/

IMAGE imgBg;//游戏背景
IMAGE going;//继续按钮
IMAGE pauseui;//暂停视图
IMAGE upcard;//升级卡槽
IMAGE next_ui;//下一关
IMAGE up_ex;//经验条
IMAGE player_ui;//角色ui
IMAGE game_fail;//游戏失败


//僵尸的动态帧数组
IMAGE imageZombie[22];//正常移动
IMAGE imageZmDead[10];//死亡
IMAGE imageZmEat[21];//攻击
IMAGE imageZmStand[11];//静止

IMAGE imgBulletNormal;//运动中的子弹图片
IMAGE imgBallBlast[4];//子弹击中后的图片

//玩家1
Player P1;


enum Status { GOING, PAUSE, MENU, UP, NEXT, FAIL };
Status GameStatus;//游戏状态

int Level = 1;//关卡
int Ex_limit = 100;//升级需求经验
int kill_goal = 4 * Level;//关卡击杀目标



//存档
void save_file(int flag = 1) {
	errno_t err;
	FILE* progress;
	char filename[] = "res/game_data/data.dat";

	if (!flag) {
		Level = 1;
		Ex_limit = 100;
		kill_goal = 2;

		P1.lv = 0;
		P1.ex = 0;
		P1.hp = 100;
		P1.getex_rate = 1;
		P1.attack = 20;
		P1.shootspeed = 120;
	}


	err = fopen_s(&progress, filename, "wb");
	if (err != 0) {
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	// 写入变量到文件
	fwrite(&Level, sizeof(int), 1, progress);
	fwrite(&Ex_limit, sizeof(int), 1, progress);
	fwrite(&kill_goal, sizeof(int), 1, progress);

	fwrite(&P1.lv, sizeof(int), 1, progress);
	fwrite(&P1.hp, sizeof(int), 1, progress);
	fwrite(&P1.ex, sizeof(float), 1, progress);
	fwrite(&P1.getex_rate, sizeof(float), 1, progress);
	fwrite(&P1.attack, sizeof(float), 1, progress);
	fwrite(&P1.shootspeed, sizeof(float), 1, progress);

	fclose(progress);
}


//读档
void load_file() {
	errno_t err;
	FILE* progress;
	char filename[] = "res/game_data/data.dat";

	err = fopen_s(&progress, filename, "rb");
	if (err != 0) {
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	// 从文件读取变量
	fread(&Level, sizeof(int), 1, progress);
	fread(&Ex_limit, sizeof(int), 1, progress);
	fread(&kill_goal, sizeof(int), 1, progress);

	fread(&P1.lv, sizeof(int), 1, progress);
	fread(&P1.hp, sizeof(int), 1, progress);
	fread(&P1.ex, sizeof(float), 1, progress);
	fread(&P1.getex_rate, sizeof(float), 1, progress);
	fread(&P1.attack, sizeof(float), 1, progress);
	fread(&P1.shootspeed, sizeof(float), 1, progress);

	fclose(progress);
}






