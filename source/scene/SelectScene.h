#pragma once
/* === キャラセレクトシーン処理のヘッダファイル === */

#ifndef SELECTSCENE_H	// 2重インクルード防止

#define SELECTSCENE_H

#include "DxLib.h"
#include "Geometry.h"


#define CharacterNameLength		128	// キャラクターの名称の長さ

#define SelectBoxInterval		30	// 選択肢を選んでから次のメッセージボックス表示までのインターバル


extern int questionNumber;		// 質問の番号を格納する変数

extern char CharacterKind[CharacterNameLength];		// メッセージ用のキャラクターの種類を格納する配列


extern int SelectScene_Init();		// キャラセレクトシーンの初期化関数
extern void SelectScene_Manage();	// キャラセレクトシーンの処理の管理関数
extern void SelectScene_Process();	// キャラセレクトシーンの処理関数
extern void SelectScene_Draw();		// キャラセレクトシーンの描画関数
extern int SelectScene_End();		// セレクトシーンの終了関数


#endif