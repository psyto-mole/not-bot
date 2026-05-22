#pragma once
/* === タイトル処理のヘッダファイル === */

#ifndef TITLE_H	// 2重インクルード防止

#define TITLE_H

#include "DxLib.h"


extern int Title_Init();		// タイトルシーンの初期化関数
extern void Title_Manage();	// タイトルシーンの処理の管理関数
extern void Title_Process();	// タイトルシーンの処理関数
extern void Title_Draw();		// タイトルシーンの描画関数
extern int Title_End();		// タイトルシーンの終了関数


#endif