#pragma once
/* === キー入力処理のヘッダファイル === */

#include "DxLib.h"

extern int nowKey[256];			// キーの現在の入力状態の格納配列
extern int oldKey[256];			// キーの過去(1フレーム前)の入力状態の格納配列
extern char key_buf[256];		// キーの入力状態を調べるための配列

/* --- キー処理の初期化 --- */
extern void Key_Init(void);

/* --- キー入力の取得関数 --- */
extern int Key_Update(void);

/* --- 特定のキーが押されているかのチェック関数 --- */
extern bool Key_Check_Press(int KEY_INPUT_);

/* --- 特定のキーがクリックされたかのチェック関数 --- */
extern bool Key_Check_Click(int KEY_INPUT_);
