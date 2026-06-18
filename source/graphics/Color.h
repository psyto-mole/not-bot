#pragma once
/* === カラー定義のヘッダファイル === */

#include "DxLib.h"


#define SwitchingInterval 5		// 色の切り換わりの間隔

extern int Color_White;			// 白
extern int Color_Black;			// 黒
extern int Color_Gray;			// 灰色
extern int Color_LightGray;		// 明るい灰色
extern int Color_DarkGray;		// 暗い灰色
extern int Color_Red;			// 赤
extern int Color_Green;			// 緑
extern int Color_Blue;			// 青
extern int Color_Yellow;		// 黄
extern int Color_Cyan;			// 水色
extern int Color_Violet;		// 濃い紫
extern int Color_Purple;		// 薄い紫
extern int Color_LightGreen;	// 明るい緑
extern int Color_DarkGreen;		// 暗い緑
extern int Color_LightBlue;		// 明るい青
extern int Color_DarkBlue;		// 暗い青
extern int Color_SkyBlue;		// 空色

extern int Color_switching_Rainbow;		// 時間経過で色が移り変わる虹色
extern int Color_switching_Violet;		// 時間経過で色が移り変わる紫色
extern int Color_switching_Light;		// 時間経過で明るさが移り変わる白

extern int Counter_Red;		// 赤色の割合を管理する変数
extern int Counter_Green;	// 緑色の割合を管理する変数
extern int Counter_Blue;	// 青色の割合を管理する変数
extern int Counter_Light;	// 明暗の割合を管理する変数

/* --- カラーの初期化関数 --- */
extern void Color_Init();

/* --- カラーの処理関数 --- */
extern void Color_Process();
