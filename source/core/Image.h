#pragma once
/* === 画像処理のヘッダファイル === */

#include "DxLib.h"


#define FAKEIMAGEPATH	".\\Image\\Desktop.png"			// 偽のタイトルシーンの背景画像のパス

#define ROBOTIMAGEPATH		".\\Image\\Robot_96x96.png"			// ロボットの画像のパス
#define HUMANIMAGEPATH		".\\Image\\Human_96x96.png"			// 人間の画像のパス
#define DRAGONIMAGEPATH		".\\Image\\Dragon_96x96.png"		// ドラゴンの画像のパス
#define DIGHTMAREIMAGEPATH	".\\Image\\Dightmare_96x96.png"	// ドラゴンの画像のパス
#define NONAMEIMAGEPATH		".\\Image\\Noname_96x96.png"		// ドラゴンの画像のパス
#define SHEPPIMAGEPATH		".\\Image\\Shepp_96x96.png"			// Sheppの画像のパス



extern int FakeImageHandle;		// 偽のタイトルシーンの背景画像のハンドル

extern int RobotImageHandle;		// ロボットの画像のハンドル
extern int HumanImageHandle;		// 人間の画像のハンドル
extern int DragonImageHandle;		// ドラゴンの画像のハンドル
extern int DightmareImageHandle;	// ダイトメアの画像のハンドル
extern int NonameImageHandle;		// キューの画像のハンドル
extern int SheppImageHandle;		// Sheppの画像のハンドル


/* --- 画像の初期化関数 --- */
extern int Image_Init(void);

/* --- 画像の終了処を行う理関数 --- */
extern void Image_End(void);

/* --- キャラクターの描画関数 --- */
extern void DrawExtendGraphConditional(int x1, int y1, int x2, int y2, int characterNumber, bool isPlayer);
