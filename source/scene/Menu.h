#pragma once
/* === システムメニューの処理を管理するヘッダファイル === */

#include "DxLib.h"


enum SystemMenu
{
	MenuOFF,		// メニューオフ
	MenuTop,		// メニュートップ
	Achievement,	// 勝敗の記録
	DeleteData,		// データ消去
	GameEnd,		// ゲーム終了
	Credit			// クレジット
};

extern SystemMenu menuKind;		// メニューの種類

extern void Menu_Init();			// システムメニューの初期化関数
extern void Menu_Manage();		// システムメニューの処理の管理関数
extern int Menu_Process();		// システムメニューの処理関数
extern void Menu_Draw();		// システムメニューの描画関数

extern void Show_WinLoseCircle(int circleNumber);	// 勝敗結果の円を描画する関数