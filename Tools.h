#pragma once
#include <graphics.h>
#include<cstring>
#include<iostream>
#include <fstream>

//���ֿ���
#include<Windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

/*һЩ�������ܵĺ���ʵ��*/


//͸����ͼʵ��
void putimagePNG(int  picture_x, int picture_y, IMAGE* picture);

//��ȡ��ʱʱ��
int getDelay();

//��ȡ�����ʱ
int getshoot_delay(int shootspeed);

//�ж��ļ��Ƿ����
bool fileExists(const std::string& filename);

//������ֵ�ָ��λ��
void out_txt(const char* format, int value, float x, float y, int size = 24);

//���ֲ��ſ���
void play_music(const char* music, int repeat = 0, int sound = 50);
void close_music(const char* music);