#pragma once
/* === リザルトシーン処理のヘッダファイル === */

#ifndef RESULT_H	// 2重インクルード防止

#define RESULT_H

#include "DxLib.h"


extern int Result_Init();		// リザルトシーンの初期化関数
extern void Result_Manage();	// リザルトシーンの処理の管理関数
extern void Result_Process();	// リザルトシーンの処理関数
extern void Result_Draw();		// リザルトシーンの描画関数
extern int Result_End();		// リザルトシーンの終了関数


#endif