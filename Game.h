#pragma once

#include"World.h"
#include"Bullets.h"
#include"Zombie.h"
#include"Upgrade.h"

/*游戏各种状态流程的控制*/


//碰撞判定
void collisionCheck() {
	bullet.checkBullet2Zm();
	zm.checkEat();
}


//升级判定
void UpCheck() {

	if (P1.ex >= Ex_limit) {
		GameStatus = UP;
		P1.ex = P1.ex - Ex_limit;
		P1.lv++;
		Ex_limit = 100 + 100 * P1.lv;

		for (int i = 0; i < 3; i++) {
			card[i].init_data(i);
		}
	}

}


//界面更新
void updateWindow() {
	BeginBatchDraw();//开始缓冲

	//加载地图
	putimage(-112, 0, &imgBg);
	putimagePNG(840, 10, &going);


	
	out_txt("Level: %d", Level, 800, 575);
	out_txt("剩余:%d", kill_goal - killCount, 650, 575);


	//角色UI
	putimagePNG(30, 5, &player_ui);
	out_txt("Lv：%d", P1.lv, 235, 28, 20);
	out_txt("攻击力：%d", P1.attack, 234, 45, 18);
	out_txt("攻击间隔：%d", P1.shootspeed, 234, 60, 18);
	out_txt("经验获取：%d %%", P1.getex_rate * 100, 234, 75, 18);

	//血条计算显示
	setfillcolor(RED);
	int hp_rate = 1.45 * P1.hp;
	POINT pts[] = { {265, 15}, {265 + hp_rate, 15}, {255 + hp_rate, 24},{265, 24} };
	solidpolygon(pts, 4);


	//经验条计算显示
	setcolor(BLUE);
	out_txt("Ex:", 0, 200 - 30, 575);
	putimagePNG(232 - 30, 577, &up_ex);
	setfillcolor(GREEN);
	int ex_rate = (382 - 238) * (P1.ex / Ex_limit) + 238 - 30;
	solidrectangle(238 - 30, 583, ex_rate, 591);


	//升级检测
	UpCheck();

	P1.DrawPlayer();

	//渲染僵尸
	zm.drawZombie();

	//渲染豌豆子弹
	bullet.showBullets();//渲染运动
	bullet.showBlast();//渲染击中

	EndBatchDraw();//结束双缓冲
}


//角色更新
void updateGame() 
{
	//*实现僵尸的更新
	zm.creatZombie();
	zm.updateZombie();

	//发射豌豆子弹
	bullet.creatBullet();
	bullet.updateBullet();

	//碰撞检测，包括两种检测
	collisionCheck();

}


//游戏流程
void Play_Game()
{
	int timer = 0;
	bool flag = true;

	while (1) {
		
		userClick();
		timer += getDelay();
		if (timer > 20) {   //帧率控制
			flag = true;
			timer = 0;
		}

		if (flag) {
			flag = false;
			updateWindow();//界面更新
			updateGame();//状态更新
		}
		
		if (GameStatus != GOING) {
			break;
		}
	}
}


//暂停流程
void Pause_Game() {
	int timer = 0;
	bool flag = true;
	PlaySound(_T("res/music/Bullet/pause.wav"), NULL, SND_FILENAME | SND_ASYNC);

	while (1) {
		userClick_pause();
		timer += getDelay();

		if (timer > 20) {   //帧率控制
			flag = true;
			timer = 0;
		}

		if (flag) {
			flag = false;
			putimagePNG(250, 100, &pauseui);
		}
		if (GameStatus != PAUSE) {
			break;
		}
	}

}


//升级流程
void Up_Game() {
	int timer = 0;
	bool flag = true;
	PlaySound(_T("res/music/Bullet/up.wav"), NULL, SND_FILENAME | SND_ASYNC);

	while (1) {
		userClick_up();
		timer += getDelay();

		if (timer > 1000) {
			flag = true;
			timer = 0;
		}

		if (flag) {
			flag = false;
			putimagePNG(150, 150, &upcard);
			putimagePNG(400, 150, &upcard);
			putimagePNG(650, 150, &upcard);

			for (int i = 0; i < 3; i++) {
				card[i].buff_print();
			}
		}
		if (GameStatus != UP) {
			break;
		}
	}

}


//下一关卡
void Next_Game() {
	Level++;
	int timer = 0;
	bool flag = true;

	while (1) {
		userClick_next();
		timer += getDelay();

		if (timer > 20) {   //帧率控制
			flag = true;
			timer = 0;
		}

		if (flag) {
			flag = false;
			putimagePNG(250, 100, &next_ui);
		}
		if (GameStatus != NEXT) {
			kill_goal = 4 * Level;
			zm.InitZombie();

			break;
		}
	}
}


//游戏失败
void Fail_Game() {
	int timer = 0;
	bool flag = true;

	close_music("eat.mp3");
	close_music("eat_1.mp3");
	close_music("going.mp3");

	play_music("fail.mp3", 0, 100);

	while (1) {
		userClick_fail();
		timer += getDelay();

		if (timer > 20) {   //帧率控制
			flag = true;
			timer = 0;
		}

		if (flag) {
			flag = false;
			putimagePNG(250, 100, &game_fail);
		}
		if (GameStatus != FAIL) {
			break;
		}
	}
}
