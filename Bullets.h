#pragma once

#include"Player.h"
#include"World.h"
#include"Zombie.h"

#define WIN_Width 900
#define WIN_Hight 600

/*�ӵ���ʵ��*/

class Bullets {
public:
	int x, y;//λ������
	int row;//����
	bool used;//�Ƿ�ʹ��
	int speed;//�ٶ�
	bool blast = 0;//�Ƿ����
	int frameIndex;//����ͼƬ��֡���


	void creatBullet();//�ӵ�����
	void updateBullet();//�ӵ��˶�����
	void checkBullet2Zm();//��ײ���
	void showBullets();//�ӵ���Ⱦ
	void showBlast();//��Ⱦ�ӵ�����Ч��

};


Bullets bullet;
Bullets bullets[200];//�ӵ���


//�ӵ�����
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



//�˶�����
void Bullets::updateBullet() {
	int bulletNum = sizeof(bullets) / sizeof(bullets[0]);
	for (int i = 0; i < bulletNum; i++) {
		if (bullets[i].used) {
			//�ӵ��˶�
			bullets[i].x += bullets[i].speed;
			//�߽紦��
			if (bullets[i].x > WIN_Width) {
				bullets[i].used = false;
			}
			//��ײ����
			if (bullets[i].blast) {
				bullets[i].frameIndex++;
				if (bullets[i].frameIndex >= 4) {
					bullets[i].used = false;
				}
			}
		}
	}
}


//��ײ���
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
				bullets[i].blast = true; //ȷ����ײ
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


//��Ⱦ�ӵ�
void Bullets::showBullets() {
	int bulletNum = sizeof(bullets) / sizeof(bullets[0]);
	for (int i = 0; i < bulletNum; i++) {
		if (bullets[i].used) {
			putimagePNG(bullets[i].x, bullets[i].y, &imgBulletNormal);
		}
	}
}


//����Ч��
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