#pragma once

#include"World.h"
#include"Bullets.h"
#include"Zombie.h"
#include"Upgrade.h"

/*��Ϸ����״̬���̵Ŀ���*/


//��ײ�ж�
void collisionCheck() {
	bullet.checkBullet2Zm();
	zm.checkEat();
}


//�����ж�
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


//�������
void updateWindow() {
	BeginBatchDraw();//��ʼ����

	//���ص�ͼ
	putimage(-112, 0, &imgBg);
	putimagePNG(840, 10, &going);


	
	out_txt("Level: %d", Level, 800, 575);
	out_txt("ʣ��:%d", kill_goal - killCount, 650, 575);


	//��ɫUI
	putimagePNG(30, 5, &player_ui);
	out_txt("Lv��%d", P1.lv, 235, 28, 20);
	out_txt("��������%d", P1.attack, 234, 45, 18);
	out_txt("���������%d", P1.shootspeed, 234, 60, 18);
	out_txt("�����ȡ��%d %%", P1.getex_rate * 100, 234, 75, 18);

	//Ѫ��������ʾ
	setfillcolor(RED);
	int hp_rate = 1.45 * P1.hp;
	POINT pts[] = { {265, 15}, {265 + hp_rate, 15}, {255 + hp_rate, 24},{265, 24} };
	solidpolygon(pts, 4);


	//������������ʾ
	setcolor(BLUE);
	out_txt("Ex:", 0, 200 - 30, 575);
	putimagePNG(232 - 30, 577, &up_ex);
	setfillcolor(GREEN);
	int ex_rate = (382 - 238) * (P1.ex / Ex_limit) + 238 - 30;
	solidrectangle(238 - 30, 583, ex_rate, 591);


	//�������
	UpCheck();

	P1.DrawPlayer();

	//��Ⱦ��ʬ
	zm.drawZombie();

	//��Ⱦ�㶹�ӵ�
	bullet.showBullets();//��Ⱦ�˶�
	bullet.showBlast();//��Ⱦ����

	EndBatchDraw();//����˫����
}


//��ɫ����
void updateGame() 
{
	//*ʵ�ֽ�ʬ�ĸ���
	zm.creatZombie();
	zm.updateZombie();

	//�����㶹�ӵ�
	bullet.creatBullet();
	bullet.updateBullet();

	//��ײ��⣬�������ּ��
	collisionCheck();

}


//��Ϸ����
void Play_Game()
{
	int timer = 0;
	bool flag = true;

	while (1) {
		
		userClick();
		timer += getDelay();
		if (timer > 20) {   //֡�ʿ���
			flag = true;
			timer = 0;
		}

		if (flag) {
			flag = false;
			updateWindow();//�������
			updateGame();//״̬����
		}
		
		if (GameStatus != GOING) {
			break;
		}
	}
}


//��ͣ����
void Pause_Game() {
	int timer = 0;
	bool flag = true;
	PlaySound(_T("res/music/Bullet/pause.wav"), NULL, SND_FILENAME | SND_ASYNC);

	while (1) {
		userClick_pause();
		timer += getDelay();

		if (timer > 20) {   //֡�ʿ���
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


//��������
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


//��һ�ؿ�
void Next_Game() {
	Level++;
	int timer = 0;
	bool flag = true;

	while (1) {
		userClick_next();
		timer += getDelay();

		if (timer > 20) {   //֡�ʿ���
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


//��Ϸʧ��
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

		if (timer > 20) {   //֡�ʿ���
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
