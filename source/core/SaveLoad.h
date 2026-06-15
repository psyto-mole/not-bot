#pragma once
/* === ゲームデータのセーブ・ロードを管理するヘッダファイル === */

#include "DxLib.h"
#include "GameManager.h"


#define PathDataFile	".\\Game_Data\\Game_Data.dat"


extern errno_t errorCode;									// 
extern int round_robin[CharacterNumber * CharacterNumber];	// 
extern bool alreadySaved;									// 
extern bool alreadyConfirmedSave;							// 
extern bool initialized;									// 


extern void Data_Init();										// ゲームデータの初期化関数
extern void Data_Save();										// ゲームデータをセーブする関数
extern void Data_Load();										// ゲームデータをロードする関数
extern void Data_Update(int playerNumber, int enemyNumber);		// ゲームデータを更新する関数
extern void Data_Delete();										// ゲームデータを消去する関数