#pragma once

#include"Player.h"


/*ȫ�ֱ����Լ������*/

IMAGE imgBg;//��Ϸ����
IMAGE going;//������ť
IMAGE pauseui;//��ͣ��ͼ
IMAGE upcard;//��������
IMAGE next_ui;//��һ��
IMAGE up_ex;//������
IMAGE player_ui;//��ɫui
IMAGE game_fail;//��Ϸʧ��


//��ʬ�Ķ�̬֡����
IMAGE imageZombie[22];//�����ƶ�
IMAGE imageZmDead[10];//����
IMAGE imageZmEat[21];//����
IMAGE imageZmStand[11];//��ֹ

IMAGE imgBulletNormal;//�˶��е��ӵ�ͼƬ
IMAGE imgBallBlast[4];//�ӵ����к��ͼƬ

//���1
Player P1;


enum Status { GOING, PAUSE, MENU, UP, NEXT, FAIL };
Status GameStatus;//��Ϸ״̬

int Level = 1;//�ؿ�
int Ex_limit = 100;//����������
int kill_goal = 4 * Level;//�ؿ���ɱĿ��



//�浵
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

	// д��������ļ�
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


//����
void load_file() {
	errno_t err;
	FILE* progress;
	char filename[] = "res/game_data/data.dat";

	err = fopen_s(&progress, filename, "rb");
	if (err != 0) {
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	// ���ļ���ȡ����
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






