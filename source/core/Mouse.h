#pragma once
/* === マウス処理のヘッダファイル === */

#ifndef MOUSE_H	// 2重インクルード防止

#define MOUSE_H

#include "DxLib.h"


#define MouseKind 3				// マウスのボタンの種類
#define MouseCodeError 999		// マウスコードの変換のエラー値


extern POINT nowMousePoint;	// 現在のマウスの位置


/* --- マウス処理の初期化関数 --- */
extern void Mouse_Init(void);

/* --- マウス処理を行う関数 --- */
extern void Mouse_Update(void);

/* --- Now...系列の変数をOld...系列の変数に入れる --- */
void MouseNowIntoOld(void);

/* --- マウスのボタンコードを配列の要素数に変換する --- */
int MouseCodeToIndex(int MOUSE_INPUT_);

/* --- 現在のマウスカーソルの位置をPOINT型で取得する関数 --- */
extern POINT GetNowMousePoint(void);

/* --- マウス入力を取得する関数 --- */
extern void Mouse_Get(void);

/* --- マウスが押されたかのチェック関数(引数は入力を調べたいマウスのボタン) --- */
bool Mouse_Check_Press(int MOUSE_INPUT_);

/* --- マウスが押されたかのチェック関数(引数は入力を調べたいマウスのボタン) --- */
bool Mouse_Check_Click(int MOUSE_INPUT_);

#endif