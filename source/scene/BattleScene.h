#pragma once
/* === バトルシーン処理のヘッダファイル === */

#include "DxLib.h"
#include "SceneManager.h"


/* --- フェイズの列挙型 --- */
enum Fase
{
	MainFase,		// メインフェイズ
	BattleFase,		// バトルフェイズ
	EndFase			// エンドフェイズ
};


extern char battleMessage1[128];	// 1行目のメッセージを格納するクラス
extern char battleMessage2[128];	// 2行目のメッセージを格納するクラス
extern char battleMessage3[128];	// 3行目のメッセージを格納するクラス
extern char battleMessage4[128];	// 4行目のメッセージを格納するクラス

extern Fase NowFase, NextFase;		// フェイズを管理する列挙型の変数

extern int BattleScene_Init();		// バトルシーンの初期化関数
extern void BattleScene_Manage();	// バトルシーンの処理の管理関数
extern void BattleScene_Process();	// バトルシーンの処理関数
extern void BattleScene_Draw();		// バトルシーンの描画関数
extern int BattleScene_End();		// バトルシーンの終了関数