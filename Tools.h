#pragma once
#include <graphics.h>
#include<cstring>
#include<iostream>
#include <fstream>

//音乐控制
#include<Windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

/*一些辅助功能的函数实现*/


//透明贴图实现
void putimagePNG(int  picture_x, int picture_y, IMAGE* picture);

//获取延时时间
int getDelay();

//获取射击延时
int getshoot_delay(int shootspeed);

//判断文件是否存在
bool fileExists(const std::string& filename);

//输出文字到指定位置
void out_txt(const char* format, int value, float x, float y, int size = 24);

//音乐播放控制
void play_music(const char* music, int repeat = 0, int sound = 50);
void close_music(const char* music);