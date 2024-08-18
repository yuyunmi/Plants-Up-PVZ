#pragma once
#include<iostream>

#include"World.h"
#include"Base.h"
#include"Control.h"
#include"Game.h"

/*游戏主循环*/

using namespace std;

#define WIN_Width 900
#define WIN_Hight 600

//主函数
int main()
{
	load_source();//资源文件加载

	while (1)
	{
		//游戏状态-主菜单
		if (GameStatus == MENU) {
			startUI();
		}
		//游戏状态-进行
		else if (GameStatus == GOING) {
			Play_Game();
		}
		//游戏状态-暂停
		else if (GameStatus == PAUSE) {
			Pause_Game();
		}
		//游戏状态-升级
		else if (GameStatus == UP) {
			Up_Game();
		}
		//游戏状态-下一关
		else if (GameStatus == NEXT) {
			Next_Game();
		}
		//游戏状态-失败
		else if (GameStatus == FAIL) {
			Fail_Game();
		}
	}

	system("pause");
	return 0;
}