#pragma once

#include"Player.h"
#include"World.h"
#include"Zombie.h"

#define WIN_Width 900
#define WIN_Hight 600

/*子弹类实现*/

class Bullets {
public:
	int x, y;//位置坐标
	int row;//行数
	bool used;//是否使用
	int speed;//速度
	bool blast = 0;//是否击中
	int frameIndex;//击中图片的帧序号


	void creatBullet();//子弹生成
	void updateBullet();//子弹运动更新
	void checkBullet2Zm();//碰撞检测
	void showBullets();//子弹渲染
	void showBlast();//渲染子弹击中效果

};


Bullets bullet;
Bullets bullets[200];//子弹池


//子弹生成
void Bullets::creatBullet() {
	int lines[5] = { 0 };
	int bulletNum = sizeof(bullets) / sizeof(bullets[0]);

	P1.PlayerLine(P1.y);

	if (!getshoot_delay(P1.shootspeed)) {
		int k;
		for (k = 0; k < bulletNum && bullets[k].used; k++);
		if (k < bulletNum) {
			bullets[k].used = true;
			bullets[k].row = P1.line;
			bullets[k].speed = 6;
			bullets[k].blast = false;
			bullets[k].frameIndex = 0;
			bullets[k].x = P1.x + 28;
			bullets[k].y = P1.y + 5;
		}
		PlaySound("res/music/Bullet/shoot.wav", NULL, SND_FILENAME | SND_ASYNC);
	}
}



//运动更新
void Bullets::updateBullet() {
	int bulletNum = sizeof(bullets) / sizeof(bullets[0]);
	for (int i = 0; i < bulletNum; i++) {
		if (bullets[i].used) {
			//子弹运动
			bullets[i].x += bullets[i].speed;
			//边界处理
			if (bullets[i].x > WIN_Width) {
				bullets[i].used = false;
			}
			//碰撞处理
			if (bullets[i].blast) {
				bullets[i].frameIndex++;
				if (bullets[i].frameIndex >= 4) {
					bullets[i].used = false;
				}
			}
		}
	}
}


//碰撞检测
void Bullets::checkBullet2Zm() {
	int bulletCount = 200;

	for (int i = 0; i < bulletCount; i++) {
		if (bullets[i].used == false || bullets[i].blast == true) continue;

		for (int k = 0; k < kill_goal; k++) {
			if (zombies[k].used == false) continue;
			int x1 = zombies[k].x + 80;
			int x2 = zombies[k].x + 110;
			int x = bullets[i].x;
			if (zombies[k].dead == false && bullets[i].row == zombies[k].row && x > x1 && x < x2) {
				PlaySound("res/music/Bullet/attack.wav", NULL, SND_FILENAME | SND_ASYNC);
				zombies[k].blood = zombies[k].blood - P1.attack;
				bullets[i].blast = true; //确认碰撞
				bullets[i].speed = 0;

				if (zombies[k].blood <= 0) {
					zombies[k].dead = true;
					zombies[k].speed = 0;
					zombies[k].frameIndex = 0;
					PlaySound("res/music/Bullet/zombie_die.wav", NULL, SND_FILENAME | SND_ASYNC);
				}
				break;
			}
		}
	}
}


//渲染子弹
void Bullets::showBullets() {
	int bulletNum = sizeof(bullets) / sizeof(bullets[0]);
	for (int i = 0; i < bulletNum; i++) {
		if (bullets[i].used) {
			putimagePNG(bullets[i].x, bullets[i].y, &imgBulletNormal);
		}
	}
}


//击中效果
void Bullets::showBlast() {
	int bulletMax = sizeof(bullets) / sizeof(bullets[0]);
	for (int i = 0; i < bulletMax; i++) {
		if (bullets[i].used) {
			if (bullets[i].blast) {
				IMAGE* img = &imgBallBlast[bullets[i].frameIndex];
				putimagePNG(bullets[i].x, bullets[i].y, img);
			}
			else {
				putimagePNG(bullets[i].x, bullets[i].y, &imgBulletNormal);
			}
		}
	}
}