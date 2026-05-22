/* === 色定義のソースファイル === */

#include "Color.h"

int Color_White;		// 白
int Color_Black;		// 黒
int Color_Gray;			// 灰色
int Color_LightGray;	// 明るい灰色
int Color_DarkGray;		// 暗い灰色
int Color_Red;			// 赤
int Color_Green;		// 緑
int Color_Blue;			// 青
int Color_Yellow;		// 黄
int Color_Cyan;			// 水色
int Color_Violet;		// 暗い紫
int Color_Purple;		// 明るい紫
int Color_LightGreen;	// 明るい緑
int Color_DarkGreen;	// 暗い緑
int Color_LightBlue;	// 明るい青
int Color_DarkBlue;		// 暗い青
int Color_SkyBlue;		// 空色

int Color_switching_Rainbow;	// 時間経過で色が移り変わる虹色
int Color_switching_Violet;		// 時間経過で色が移り変わる紫色
int Color_switching_Light;		// 時間経過で明るさが移り変わる白

int Counter_Red;	// 赤色の割合を管理する変数
int Counter_Green;	// 緑色の割合を管理する変数
int Counter_Blue;	// 青色の割合を管理する変数
int Counter_Light;	// 明暗の割合を管理する変数

bool lightSwitchingFlag;	// 明暗の増減管理フラグ(trueで増加、falseで減少)

/* --- カラーの初期化関数 --- */
void Color_Init()
{
	Color_White			= GetColor(255, 255, 255);	// 白
	Color_Black			= GetColor(0, 0, 0);		// 黒
	Color_Gray			= GetColor(100, 100, 100);	// 灰色
	Color_LightGray		= GetColor(150, 150, 150);	// 明るい灰色
	Color_DarkGray		= GetColor(50, 50, 50);		// 暗い灰色
	Color_Red			= GetColor(255, 0, 0);		// 赤
	Color_Green			= GetColor(0, 150, 0);		// 緑
	Color_Blue			= GetColor(0, 0, 255);		// 青
	Color_Yellow		= GetColor(255, 255, 0);	// 黄色
	Color_Cyan			= GetColor(0, 255, 255);	// 水色
	Color_Violet		= GetColor(150, 0, 200);	// 暗い紫色
	Color_Purple		= GetColor(255, 0, 255);	// 明るい紫色
	Color_LightGreen	= GetColor(0, 255, 0);		// 明るい緑
	Color_DarkGreen		= GetColor(0, 100, 0);		// 暗い緑
	Color_LightBlue		= GetColor(100, 100, 255);	// 明るい青
	Color_DarkBlue		= GetColor(0, 0, 100);		// 暗い青
	Color_SkyBlue		= GetColor(0, 255, 255);	// 空色

	Color_switching_Rainbow	= GetColor(255,0,0);		// 時間経過で色が移り変わる虹色
	Color_switching_Violet	= GetColor(255,0,255);		// 時間経過で色が移り変わる紫色
	Color_switching_Light	= GetColor(255,255,255);	// 時間経過で明るさが移り変わる白

	Counter_Red = 255;
	Counter_Green = 0;
	Counter_Blue = 0;
	Counter_Light = 0;

	lightSwitchingFlag = true;
}

/* --- カラーの処理関数 --- */
void Color_Process()
{
	if (Counter_Red == 255 && Counter_Green < 255)
	{
		if (Counter_Blue > 0)
		{
			Counter_Blue -= SwitchingInterval;
			if (Counter_Blue < 0)
			{
				Counter_Blue = 0;
			}
		}
		else
		{
			Counter_Green += SwitchingInterval;
			if (Counter_Green > 255)
			{
				Counter_Green = 255;
			}
		}
	}
	else if (Counter_Green == 255 && Counter_Blue < 255)
	{
		if (Counter_Red > 0)
		{
			Counter_Red -= SwitchingInterval;
			if (Counter_Red < 0)
			{
				Counter_Red = 0;
			}
		}
		else
		{
			Counter_Blue += SwitchingInterval;
			if (Counter_Blue > 255)
			{
				Counter_Blue = 255;
			}
		}
	}
	else if (Counter_Blue == 255 && Counter_Red < 255)
	{
		if (Counter_Green > 0)
		{
			Counter_Green -= SwitchingInterval;
			if (Counter_Green < 0)
			{
				Counter_Green = 0;
			}
		}
		else
		{
			Counter_Red += SwitchingInterval;
			if (Counter_Red > 255)
			{
				Counter_Red = 255;
			}
		}
	}

	if (lightSwitchingFlag)
	{
		Counter_Light += SwitchingInterval;
		if (Counter_Light >= 255)
		{
			Counter_Light = 255;
			lightSwitchingFlag = false;
		}
	}
	else
	{
		Counter_Light -= SwitchingInterval;
		if (Counter_Light <= 0)
		{
			Counter_Light = 0;
			lightSwitchingFlag = true;
		}
	}

	Color_switching_Rainbow = GetColor(Counter_Red, Counter_Green, Counter_Blue);		// 時間経過で色が移り変わる虹色
	Color_switching_Violet	= GetColor(Counter_Red, 0, Counter_Blue);					// 時間経過で色が移り変わる虹色
	Color_switching_Light	= GetColor(Counter_Light, Counter_Light, Counter_Light);	// 時間経過で明るさが移り変わる白

	return;
}