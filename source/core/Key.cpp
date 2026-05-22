/* === キー入力処理のソースファイル === */

#include "Key.h"

int i, errorChecker;	// このソースファイルの中だけで利用するint型変数
int nowKey[256];		// キーの現在の入力状態の格納配列
int oldKey[256];		// キーの過去の入力状態の格納配列
char key_buf[256];		// キーの入力状態を調べるための配列

/* --- キー処理の初期化 --- */
void Key_Init(void)
{
	errorChecker = 0;	// エラー確認のための変数の初期化

	/* +++ key配列の初期化 +++ */
	for (i = 0; i < 256; i++)
	{
		nowKey[i] = 0;
		oldKey[i] = 0;
	}
}

/* --- キー入力の取得関数 --- */
int Key_Update(void)
{
	

	errorChecker = GetHitKeyStateAll(key_buf);	// 全てのキーの入力状態を調べる

	if (errorChecker == -1)		// キー入力のチェックに失敗したら
	{
		/* +++ エラーメッセージを表示 +++ */
		MessageBox(
			GetMainWindowHandle(),
			"Key Error Envoked",
			"Error",
			MB_OK
		);

		return -1;	// キー入力のチェック失敗(-1を返す)
	}

	/* +++ キー入力の調査結果をもとに入力状態の格納配列の各要素に値を設定 +++ */
	for (i = 0; i < 256; i++)
	{
		oldKey[i] = nowKey[i];

		if (key_buf[i] != 0)	// キー入力がなされている
		{
			nowKey[i] = 1;		// 対応する格納配列の要素の値を1にする
		}
		else					// キー入力がなされていない
		{
			nowKey[i] = 0;		// 対応する格納配列の要素の値を0にする
		}
	}

	return 0;	// キー入力のチェックの終了(0を返す)
}

/* --- 特定のキーが押されているかのチェック関数(引数はチェックしたいキー) --- */
bool Key_Check_Press(int KEY_INPUT_)
{
	if (nowKey[KEY_INPUT_] == 1)	// 現在キーが押されているなら
	{
		return true;	// trueを返す
	}
	
	return false;	// falseを返す
}

/* --- 特定のキーがクリックされたかのチェック関数 --- */
bool Key_Check_Click(int KEY_INPUT_)
{
	if (nowKey[KEY_INPUT_] == 0 && oldKey[KEY_INPUT_] == 1)		// 過去にキーが押されて現在キーが離されている
	{
		return true;	// trueを返す
	}

	return false;
}