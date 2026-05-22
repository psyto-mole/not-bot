/* === マウス処理のソースファイル === */

#include "Mouse.h"
#include "Geometry.h"
#include "GameManager.h"

POINT nowMousePoint;	// 現在のマウスの位置
int mouseInput;

int NowMousePressFrame[MouseKind];		// 現在のマウスボタンを押しているフレーム数
int OldMousePressFrame[MouseKind];		// 以前のマウスボタンを押していたフレーム数

// マウスのボタンコード
int MouseCodeIndex[MouseKind]
{
	MOUSE_INPUT_LEFT,		// マウスボタン0x0001
	MOUSE_INPUT_RIGHT,		// マウスボタン0x0002
	MOUSE_INPUT_MIDDLE,		// マウスボタン0x0004
};


/* --- マウス処理の初期化関数 --- */
void Mouse_Init(void)
{
	int i;

	/* +++ 現在のマウス位置の初期化 +++ */
	nowMousePoint.x = 0;
	nowMousePoint.y = 0;


	// フレーム数の初期化
	for (i = 0; i < MouseKind; i++)
	{
		NowMousePressFrame[i] = 0;
	}

	// Old系も初期化
	MouseNowIntoOld();

	return;
}

/* --- マウス処理を行う関数 --- */
void Mouse_Update(void)
{
	int i;

	// 現在の情報を以前の情報として保存
	MouseNowIntoOld();

	nowMousePoint = GetNowMousePoint();		// 現在のマウスカーソルの位置を取得
	Mouse_Get();							// マウスの入力を取得

	/* === 各ボタンを押しているかチェック === */
	for (i = 0; i < MouseKind; i++)
	{
		if ((mouseInput & MouseCodeIndex[i]) == MouseCodeIndex[i])
		{
			NowMousePressFrame[i]++;		// 現在押しているボタンのフレーム数を1増やす
		}
		else if ((mouseInput & MouseCodeIndex[i]) != MouseCodeIndex[i])
		{
			NowMousePressFrame[i] = 0;		// ボタンのフレーム数をクリア
		}
	}

	return;
}

/* --- Now...系列の変数をOld...系列の変数に入れる --- */
void MouseNowIntoOld(void)
{
	int i;

	for (i = 0; i < MouseKind; i++)
	{
		OldMousePressFrame[i] = NowMousePressFrame[i];
	}

	return;
}

/* --- マウスのボタンコードを配列の要素数に変換する --- */
int MouseCodeToIndex(int MOUSE_INPUT_)
{
	int i;

	for (i = 0; i < MouseKind; i++)
	{
		/* --- 引数に渡されたマウスコードと紐づけされた要素数を返す --- */
		if (MouseCodeIndex[i] == MOUSE_INPUT_)
		{
			return i;
		}
	}

	// エラーを返す
	return MouseCodeError;
}

/* --- 現在のマウスカーソルの位置をPOINT型で取得する関数 --- */
POINT GetNowMousePoint()
{
	POINT mousePoint;	// マウスの位置を格納するPOINT型変数
	int getX, getY;		// 取得したマウスの座標を格納するint型変数

	GetMousePoint(&getX, &getY);		// マウスカーソルの位置を取得
	mousePoint = GetPoint(getX, getY);	// 取得したマウスカーソルの座標をPOINT型に変換

	/* === マウスの座標がゲーム画面外にあるなら画面内に収める === */
	if (mousePoint.x < 0)
	{
		mousePoint.x = 0;		// 左端に揃える
	}
	else if (mousePoint.x > GameWindowWidth)
	{
		mousePoint.x = GameWindowWidth;		// 右端に揃える
	}

	if (mousePoint.y < 0)
	{
		mousePoint.y = 0;		// 上端に揃える
	}
	else if (mousePoint.y > GameWindowHeight)
	{
		mousePoint.y = GameWindowHeight;		// 下端に揃える
	}

	return mousePoint;	// POINT型変数を戻り値として返す
}

/* --- マウス入力を取得する関数 --- */
void Mouse_Get(void)
{
	// マウスの入力を取得
	mouseInput = GetMouseInput();

	return;
}

/* --- マウスが押されたかのチェック関数(引数は入力を調べたいマウスのボタン) --- */
bool Mouse_Check_Press(int MOUSE_INPUT_)
{
	int index;

	index = MouseCodeToIndex(MOUSE_INPUT_);

	if (index != MouseCodeError)
	{
		// 現在キーが押されている(キーを押している時間が0より大きい)
		if (NowMousePressFrame[index] > 0)
		{
			return true;
		}
	}

	return false;	// falseを返す
}

/* --- マウスが押されたかのチェック関数(引数は入力を調べたいマウスのボタン) --- */
bool Mouse_Check_Click(int MOUSE_INPUT_)
{
	int index;

	index = MouseCodeToIndex(MOUSE_INPUT_);

	if (index != MouseCodeError)
	{
		if (NowMousePressFrame[index] == 0 && OldMousePressFrame[index] > 0)
		{
			return true;
		}
	}

	return false;	// falseを返す
}