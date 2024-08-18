#pragma once

#include<graphics.h>
#include"Tools.h"
#include"Math.h"
#include"Base.h"
#include"Upgrade.h"
#include"World.h"
#include"Zombie.h"

#define WIN_Width 900
#define WIN_Hight 600


/*���������Լ����ͼ��̵��������*/


//����Ѳ��
void viewScene() {
	int xMin = WIN_Width - imgBg.getwidth();
	//������ʬ��Ⱦ��λ��
	int points[5][2] = {
		{550,80},{530,160},{630,170},{530,200},{690,340}
	};
	int index[5];
	for (int i = 0; i < 5; i++)
	{
		index[i] = rand() % 11;
	}

	//�����ƶ�
	int count = 0;
	for (int x = 0; x >= xMin; x -= 2) {
		BeginBatchDraw();
		putimage(x, 0, &imgBg);

		count++;
		for (int k = 0; k < 5; k++) {
			putimagePNG(points[k][0] - xMin + x, points[k][1], &imageZmStand[index[k]]);
			if (count >= 7) {
				index[k] = (index[k] + 1) % 11;
			}
		}
		if (count >= 10)count = 0;

		EndBatchDraw();
		Sleep(15);
	}

	//ͣ��
	for (int i = 0; i < 100; i++) {
		BeginBatchDraw();
		putimage(xMin, 0, &imgBg);
		for (int k = 0; k < 5; k++) {
			putimagePNG(points[k][0], points[k][1], &imageZmStand[index[k]]);
			index[k] = (index[k] + 1) % 11;
		}
		EndBatchDraw();
		Sleep(30);
	}

	//�����л�
	for (int x = xMin; x <= -112; x += 2) {
		BeginBatchDraw();
		putimage(x, 0, &imgBg);

		count++;
		for (int k = 0; k < 5; k++) {
			putimagePNG(points[k][0] - xMin + x, points[k][1], &imageZmStand[index[k]]);
			if (count >= 7) {
				index[k] = (index[k] + 1) % 11;
			}
			if (count >= 10)count = 0;
		}
		EndBatchDraw();
		Sleep(15);
	}

}


//��ʼ����
void startUI() {
	close_music("going.mp3");

	//��ʼ�˵�ѡ��ť
	IMAGE imgBg, imgMenu1, imgMenu2, imgMenu3, imgMenu4, imgMenu5, imgMenu6;
	loadimage(&imgBg, _T("res/menus/menu.png"), 900, 600);
	loadimage(&imgMenu1, _T("res/menus/continue1.png"), 240, 80);
	loadimage(&imgMenu2, _T("res/menus/continue2.png"), 240, 80);
	loadimage(&imgMenu3, _T("res/menus/start1.png"), 240, 80);
	loadimage(&imgMenu4, _T("res/menus/start2.png"), 240, 80);
	loadimage(&imgMenu5, _T("res/menus/quit1.png"), 50, 50);
	loadimage(&imgMenu6, _T("res/menus/quit2.png"), 50, 50);

	int flag1 = 0;
	int flag2 = 0;
	int flag3 = 0;

	//���ش浵��Ϣ
	load_file();

	play_music("menu.mp3", 1, 400);

	while (1) {
		BeginBatchDraw();
		putimage(0, 0, &imgBg);
		putimagePNG(610, 220, flag1 ? &imgMenu1 : &imgMenu2);
		putimagePNG(605, 280, flag2 ? &imgMenu4 : &imgMenu3);
		putimagePNG(832, 510, flag3 ? &imgMenu5 : &imgMenu6);

		setcolor(WHITE);
		out_txt("%d", Level, 719, 230, 14);

		ExMessage msg;
		if (peekmessage(&msg)) {

			//������Ϸ
			if (msg.message == WM_LBUTTONDOWN
				&& msg.x > 610 && msg.x < 610 + 240
				&& msg.y > 210 && msg.y < 210 + 80) {
				flag1 = 1;
				PlaySound(_T("res/music/Bullet/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			else if (msg.message == WM_LBUTTONUP && flag1) {
				EndBatchDraw();
				GameStatus = GOING;
				close_music("menu.mp3");
				play_music("view.mp3", 0, 300);
				zm.InitZombie();//��ʼ����һ����ʬ
				viewScene();
				close_music("view.mp3");
				play_music("going.mp3", 1, 300);
				break;
			}

			//�µĿ�ʼ
			if (msg.message == WM_LBUTTONDOWN
				&& msg.x > 605 && msg.x < 605 + 240
				&& msg.y > 280 && msg.y < 280 + 80) {
				flag2 = 1;
				PlaySound(_T("res/music/Bullet/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			else if (msg.message == WM_LBUTTONUP && flag2) {
				EndBatchDraw();
				GameStatus = GOING;
				save_file(0);
				load_file();
				close_music("menu.mp3");
				play_music("view.mp3", 0, 300);
				zm.InitZombie();//��ʼ����һ����ʬ
				viewScene();
				close_music("view.mp3");
				play_music("going.mp3", 1, 300);
				break;
			}

			//�˳���Ϸ
			if (msg.message == WM_LBUTTONDOWN
				&& msg.x > 832 && msg.x < 832 + 50
				&& msg.y > 510 && msg.y < 510 + 50) {
				flag3 = 1;
				PlaySound(_T("res/music/Bullet/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			else if (msg.message == WM_LBUTTONUP && flag3) {
				EndBatchDraw();
				exit(0);
				break;
			}
		}
		EndBatchDraw();
	}
}


//��Ϸ�а�������
void userClick() {
	ExMessage msg;

	if (peekmessage(&msg)) {

		if (msg.message == WM_LBUTTONDOWN) {
			//��ͣ��Ϸ
			if (msg.y > 10 && msg.y < 50 && msg.x > 840 && msg.x < 880) {
				GameStatus = PAUSE;
			}
		}

		if (GetAsyncKeyState('D') & 0x8000) {
			P1.MoveRight();
		}
		else if (GetAsyncKeyState('A') & 0x8000) {
			P1.MoveLeft();
		}
		else if (GetAsyncKeyState('W') & 0x8000) {
			P1.MoveUp();
		}
		else if (GetAsyncKeyState('S') & 0x8000) {
			P1.MoveDown();
		}
		else if (GetAsyncKeyState('P') & 0x8000) {
			GameStatus = PAUSE;
		}
		else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			GameStatus = PAUSE;
		}
	}
}


//��ͣʱ��������
void userClick_pause() {
	ExMessage msg;

	if (peekmessage(&msg)) {
		if (msg.message == WM_LBUTTONDOWN) {

			//�������˵�
			if (msg.x > 300 && msg.x < 600 && msg.y > 370 && msg .y < 400) {
				PlaySound(_T("res/music/Bullet/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				save_file();
				GameStatus = MENU;
			}
			//������Ϸ
			else if(msg.x > 300 && msg.x < 600 && msg.y > 415 && msg.y < 450){
				PlaySound(_T("res/music/Bullet/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				GameStatus = GOING;
			}
		}
	}
}


//����ʱ��������
void userClick_up() {
	ExMessage msg;

	if (peekmessage(&msg)) {
		if (msg.message == WM_LBUTTONDOWN) {

			//���漤��
			if (msg.x > 150 && msg.x < 370) {
				PlaySound(_T("res/music/Bullet/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				card[0].activate();
				GameStatus = GOING;
			}
			else if (msg.x > 400 && msg.x < 620) {
				PlaySound(_T("res/music/Bullet/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				card[1].activate();
				GameStatus = GOING;
			}
			else if (msg.x > 650 && msg.x < 870) {
				PlaySound(_T("res/music/Bullet/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				card[2].activate();
				GameStatus = GOING;
			}
		}
	}
}


//��һ��ʱ��������
void userClick_next() {
	ExMessage msg;

	if (peekmessage(&msg)) {
		if (msg.message == WM_LBUTTONDOWN) {

			//�������˵�
			if (msg.x > 300 && msg.x < 600 && msg.y > 370 && msg.y < 400) {
				PlaySound(_T("res/music/Bullet/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				save_file();//�浵
				GameStatus = MENU;
			}
			//��һ��
			else if (msg.x > 300 && msg.x < 600 && msg.y > 415 && msg.y < 450) {
				PlaySound(_T("res/music/Bullet/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
				save_file();//�浵
				GameStatus = GOING;
			}
		}
	}
}


//ʧ��ʱ��������
void userClick_fail() {
	ExMessage msg;

	if (peekmessage(&msg)) {
		if (msg.message == WM_LBUTTONDOWN) {

			//�������˵�
			if (msg.x > 260 && msg.x < 600 && msg.y > 220 && msg.y < 450) {
				save_file(0);//�浵����
				GameStatus = MENU;
			}
		}
	}
}