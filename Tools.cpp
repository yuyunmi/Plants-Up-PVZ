#include "tools.h"

// ����PNGͼ��ȥ͸������
void _putimagePNG(int  picture_x, int picture_y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ��(EASYX)
	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶�(EASYX)
	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ��(EASYX)
	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶�(EASYX)
	int dstX = 0;    //���Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //���Դ������صĽǱ�
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


// ������ y<0 �Լ� x<0 ���κ����
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


//��ȡ��ʱ
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


//��ȡ����ӳ�
int getshoot_delay(int shootspeed)
{
	static unsigned long long Time = 0;
	Time++;
	if (Time > shootspeed) {
		Time = 0;
	}
	return Time;
}


//���������ָ��λ��
void out_txt(const char* format, int value, float x, float y, int size)
{
	settextstyle(size, 0, _T("Consolas"));
	TCHAR buffer[30];
	sprintf_s(buffer, format, value);
	outtextxy(x, y, buffer);
}


//�ļ��Ƿ����
bool fileExists(const std::string& filename) {
	std::ifstream file(filename);
	return file.good();
}


//���ֲ���(·�����Ƿ�ѭ��, ��С)
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

//����ֹͣ
void close_music(const char* music){
	char cmd[100] = { 0 };
	sprintf_s(cmd, "close res/music/%s", music);
	mciSendString(cmd, NULL, 0, NULL);
}
