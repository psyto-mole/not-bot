#pragma once
/* === ゲームデータのセーブ・ロードを管理するヘッダファイル === */

#include "DxLib.h"
#include "GameManager.h"


#define PathDataFile	".\\Game_Data\\Game_Data.dat"	// セーブデータを保存するファイルのパス


extern errno_t errorCode;									// ファイルの読み出し・書き込みの際のエラーコードを格納する変数
extern int saveArray[CharacterNumber][CharacterNumber];		// 勝敗記録を保持する配列
extern int total_saveArray_Previous;						// セーブを行う前の勝敗記録の値の合計
extern int total_saveArray_Now;								// 現在の勝敗記録の値の合計
extern bool alreadySaved;									// セーブ済みかどうかを判定するフラグ
extern bool alreadyConfirmedSave;							// セーブするかの確認を行ったかを判定するフラグ
extern bool initialized;									// 初期化済みかどうかを判定するフラグ


extern void Data_Init();										// ゲームデータの初期化関数
extern void Data_Save();										// ゲームデータをセーブする関数
extern void Data_Load();										// ゲームデータをロードする関数
extern void Data_Update(int playerNumber, int enemyNumber);		// ゲームデータを更新する関数
extern void Data_Delete();										// ゲームデータを消去する関数