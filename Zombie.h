#pragma once

#include<stdlib.h>
#include"World.h"

#define WIN_Width 900
#define WIN_Hight 600

/*��ʬ���ʵ��*/

class Zombie {

public:
	int x, y;//λ��
	int frameIndex = 0;//����֡���
	bool used;//�Ƿ�ʹ��
	int speed;//�ƶ��ٶ�
	int row;//����
	int blood;//Ѫ��
	bool dead;//�Ƿ�����
	bool eating;//�Ƿ����ڹ���

	void drawZombie();//��Ⱦ��ʬ
	void updateZombie();//���½�ʬ�Ķ�̬֡
	void creatZombie();//��ʬλ������
	void InitZombie();//�ؿ���ʬ���ݳ�ʼ��
	void checkEat();//��⽩ʬ����ҵ���ײ
};

//��ʬ��
Zombie *zombies = NULL;
Zombie zm;

int killCount;//�Ѿ���ɱ���Ľ�ʬ����
int zombie_num = 0;//��ǰӦ�����ɵĽ�ʬ���

//��Ⱦ��ʬ
void Zombie::drawZombie() {

	for (int i = 0; i < kill_goal; i++) {

		if (zombies[i].used) {

			IMAGE* img = NULL;
			if (zombies[i].dead) img = imageZmDead;
			else if (zombies[i].eating) img = imageZmEat;
			else img = imageZombie;

			img += zombies[i].frameIndex;

			putimagePNG(zombies[i].x, zombies[i].y , img);

		}
	}
}



//���½�ʬ�Ķ�̬֡
void Zombie::updateZombie() {

	static int count = 0;
	count++;
	if (count > 2) {
		count = 0;
		//���½�ʬ��λ��
		for (int i = 0; i < kill_goal; i++) {

			if (zombies[i].used) {
				zombies[i].x -= zombies[i].speed;

				//��Ϸ����
				if (zombies[i].x < 56 || P1.hp <= 0) {
					GameStatus = FAIL;
				}
			}
		}
	}

	//���½�ʬ�Ķ�̬֡
	static int count2 = 0;
	count2++;
	if (count2 > 3) {
		count2 = 0;
		for (int i = 0; i < kill_goal; i++) {

			if (zombies[i].used) {

				if (zombies[i].dead) {
					zombies[i].frameIndex++;

					if (zombies[i].frameIndex >= 10) {
						zombies[i].used = false;
						killCount++;
						P1.ex += 100 * P1.getex_rate;
					}
				}
				else if (zombies[i].eating) {
					zombies[i].frameIndex = (zombies[i].frameIndex + 1) % 21;
				}

				else {
					zombies[i].frameIndex = (zombies[i].frameIndex + 1) % 22;
				}
			}
		}
	}
}


//��ʬλ������
void Zombie::creatZombie() {

	static int count = 0;
	static int fre = 0;

	if (killCount >= kill_goal) {
		zombie_num = 0;
		killCount = 0;
		GameStatus = NEXT;
		return;
	}

	count++;
	if (count >= fre) {
		count = 0;
		fre = rand() % 400 + 340;
		if (zombie_num < kill_goal) {
			zombies[zombie_num++].used = true;
		}	
	}
}


//�ؿ���ʬ���ݳ�ʼ��
void Zombie::InitZombie() {

	if (zombies != NULL) {
		delete[] zombies;
		zombies = NULL;
	}

	zombies = new Zombie[kill_goal];

	for (int i = 0; i < kill_goal; i++) {
		zombies[i].used = false;
		zombies[i].x = WIN_Width;
		zombies[i].row = rand() % 5;
		zombies[i].y = 40 + zombies[i].row * 100;
		zombies[i].speed = 1;
		zombies[i].blood = 100;
		zombies[i].dead = false;
		zombies[i].eating = false;
		zombies[i].frameIndex = 0;
	}

} 


//��⽩ʬ����ҵ���ײ
void Zombie::checkEat()
{
	for (int i = 0; i < kill_goal; i++) {

		if (zombies[i].used) {

			int x1 = P1.x + 60;
			int x2 = P1.x + 10;
			int x3 = zombies[i].x + 80;
			//��ײ��ʼ
			if (zombies[i].row == P1.line && !zombies[i].eating) {

				if (x3 > x2 && x3 < x1) {
					zombies[i].eating = true;
					zombies[i].speed = 0;
					zombies[i].frameIndex = 0;
					play_music("eat.mp3", 1, 200);
					play_music("eat_1.mp3", 1, 200);
				}
			}
			
			if (zombies[i].eating) {
				//��ײ����
				if ((zombies[i].row != P1.line) || zombies[i].x > x2 || x3 < P1.x) {
					zombies[i].eating = false;
					zombies[i].speed = 1;
					zombies[i].frameIndex = 0;
					close_music("eat.mp3");
					close_music("eat_1.mp3");
				}
				P1.hp--;
			}
		}
	}
}
