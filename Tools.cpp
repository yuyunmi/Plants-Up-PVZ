#include "tools.h"

// 载入PNG图并去透明部分
void _putimagePNG(int  picture_x, int picture_y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度(EASYX)
	int picture_height = picture->getheight(); //获取picture的高度(EASYX)
	int graphWidth = getwidth();       //获取绘图区的宽度(EASYX)
	int graphHeight = getheight();     //获取绘图区的高度(EASYX)
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)
					| (sb * sa / 255 + db * (255 - sa) / 255);
			}
		}
	}
}


// 适用于 y<0 以及 x<0 的任何情况
void putimagePNG(int x, int y, IMAGE* picture) {

	IMAGE imgTmp, imgTmp2, imgTmp3;
	int winWidth = getwidth();
	int winHeight = getheight();
	if (y < 0) {
		SetWorkingImage(picture);
		getimage(&imgTmp, 0, -y,
			picture->getwidth(), picture->getheight() + y);
		SetWorkingImage();
		y = 0;
		picture = &imgTmp;
	}
	else if (y >= getheight() || x >= getwidth()) {
		return;
	}
	else if (y + picture->getheight() > winHeight) {
		SetWorkingImage(picture);
		getimage(&imgTmp, x, y, picture->getwidth(), winHeight - y);
		SetWorkingImage();
		picture = &imgTmp;
	}

	if (x < 0) {
		SetWorkingImage(picture);
		getimage(&imgTmp2, -x, 0, picture->getwidth() + x, picture->getheight());
		SetWorkingImage();
		x = 0;
		picture = &imgTmp2;
	}

	if (x > winWidth - picture->getwidth()) {
		SetWorkingImage(picture);
		getimage(&imgTmp3, 0, 0, winWidth - x, picture->getheight());
		SetWorkingImage();
		picture = &imgTmp3;
	}


	_putimagePNG(x, y, picture);
}


//获取延时
int getDelay() 
{
	static unsigned long long lastTime = 0;
	unsigned long long currentTime = GetTickCount();
	if (lastTime == 0) {
		lastTime = currentTime;
		return 0;
	}
	else {
		int ret = currentTime - lastTime;
		lastTime = currentTime;
		return ret;
	}
}


//获取射击延迟
int getshoot_delay(int shootspeed)
{
	static unsigned long long Time = 0;
	Time++;
	if (Time > shootspeed) {
		Time = 0;
	}
	return Time;
}


//文字输出在指定位置
void out_txt(const char* format, int value, float x, float y, int size)
{
	settextstyle(size, 0, _T("Consolas"));
	TCHAR buffer[30];
	sprintf_s(buffer, format, value);
	outtextxy(x, y, buffer);
}


//文件是否存在
bool fileExists(const std::string& filename) {
	std::ifstream file(filename);
	return file.good();
}


//音乐播放(路径，是否循环, 大小)
void play_music(const char* music, int repeat, int sound){

	char cmd[100] = { 0 };

	sprintf_s(cmd, "open res/music/%s", music);

	mciSendString(cmd, NULL, 0, NULL);

	sprintf_s(cmd, "setaudio res/music/%s volume to %d", music, sound);
	mciSendString(cmd, 0, 0, 0);

	if (repeat) {
		sprintf_s(cmd, "play res/music/%s repeat", music);
	}
	else {
		sprintf_s(cmd, "play res/music/%s", music);
	}
	
	mciSendString(cmd, NULL, 0, NULL);

}

//音乐停止
void close_music(const char* music){
	char cmd[100] = { 0 };
	sprintf_s(cmd, "close res/music/%s", music);
	mciSendString(cmd, NULL, 0, NULL);
}
