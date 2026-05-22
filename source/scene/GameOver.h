#pragma once
/* === ゲームオーバー処理のヘッダファイル === */

#include"DxLib.h"


extern int GameOver_Init();			// ゲームオーバーシーンの初期化関数
extern void GameOver_Manage();		// ゲームオーバーシーンの処理の管理関数
extern void GameOver_Process();		// ゲームオーバーシーンの処理関数
extern void GameOver_Draw();		// ゲームオーバーシーンの描画関数
extern int GameOver_End();			// ゲームオーバーシーンの終了関数