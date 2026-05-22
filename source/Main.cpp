/* === ゲームのメインのソースファイル === */

/* +++ ライブラリのインクルード +++ */
#include <string>
#include "DxLib.h"
#include "GameManager.h"
#include "Image.h"
#include "Font.h"
#include "Color.h"
#include "Key.h"
#include "Mouse.h"
#include "Sound.h"
#include "SceneManager.h"
#include "Geometry.h"
#include "Message.h"
#include "SaveLoad.h"
#include "Menu.h"


/* +++ プロトタイプ宣言 +++ */
int Game_Init(void);	// 諸々の初期化を行う関数
void Game_End(void);	// 諸々の終了処理を行う関数


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(false);						// Log.txtの出力の拒否
	ChangeWindowMode(true);										// ウィンドウモードに設定
	SetGraphMode(GameWindowWidth, GameWindowHeight,GameColor);	// 解像度の設定
	SetWindowSize(GameWindowWidth, GameWindowHeight);			// ウィンドウサイズの設定
	SetMainWindowText(GameTitle);								// ウィンドウのタイトル
	SetBackgroundColor(0, 0, 0);								// ウィンドウの背景色
	SetWaitVSyncFlag(true);										// 垂直同期の設定
	SetAlwaysRunFlag(true);										// 非アクティブでもゲーム実行


	/* +++ ゲームの初期化 +++ */
	if (Game_Init() == -1)	// 初期化に失敗したなら
	{
		return -1;	// ソフトを終了する
	}

	SetDrawScreen(DX_SCREEN_BACK);	// 裏画面に描画(ダブルバッファリング)

	

	/* +++ ゲームループ(無限ループ) +++ */
	while (true)
	{
		/* +++ メッセージを処理し続ける(マウスやキーの入力を受け付け続ける) +++ */
		if (ProcessMessage() != 0)		// エラー発生やウィンドウが閉じられた
		{
			break;	// ループの終了(ゲームの終了)
		}


		/* +++ 画面を書き換える(画面を消去する) +++ */
		if (ClearDrawScreen() != 0)		// エラー発生
		{
			break;	// ループの終了(ゲームの終了)
		}


		/* +++ キー入力の取得 +++ */
		if (Key_Update() != 0)
		{
			break;
		}

		/* +++ マウス入力の取得 +++ */
		Mouse_Update();

		/* +++ カラー処理 +++ */
		Color_Process();

		/* +++	シーンの処理 +++ */
		if (Scene_Manage() == -1)
		{
			break;
		}

		/* +++ 裏画面を表画面に描画 +++ */
		if (ScreenFlip() != 0)		// エラー発生
		{
			break;	// ループの終了(ゲームの終了)
		}
	}


	Game_End();		// ゲームの終了

	return 0;	// ソフト終了
}


/* +++ ゲームの初期化処理(ここに諸々の初期化処理を集める) +++ */
int Game_Init(void)
{
	/* --- Dxライブラリ初期化処理 --- */
	if (DxLib_Init() == -1)		// 初期化に失敗したなら
	{
		return -1;	// -1を返す(初期化関数を初期化失敗で終わらせる)
	}

	/* --- 画像処理の初期化 --- */
	if (Image_Init() == -1)		// 初期化に失敗した
	{
		return -1;	// -1を返す(初期化関数を初期化失敗で終わらせる)
	}

	/* --- フォント処理の初期化 --- */
	if (Font_Init() == -1)	// 初期化失敗
	{
		return -1;	// -1を返す(初期化関数を初期化失敗で終わらせる)
	}

	Color_Init();	// 色管理の初期化

	Key_Init();		// キー入力処理の初期化

	Mouse_Init();	// マウス処理の初期化

	/* --- サウンド処理の初期化 --- */
	if (Sound_Init() == -1)		// 初期化失敗
	{
		MessageBox(
			GetMainWindowHandle(),							// ウィンドウハンドル
			"An Error occurred while initializing Sound",	// エラー内容
			"Sound Error",									// エラータイトル
			MB_OK											// OKボタンのみ表示
		);

		return -1;	// -1を返す(初期化関数を初期化失敗で終わらせる)
	}

	Data_Init();

	Menu_Init();

	/* --- シーン処理の初期化 --- */
	if (Scene_Init(Game_Start) == -1)		// 初期化失敗
	{
		return -1;	// -1を返す(初期化関数を初期化失敗で終わらせる)
	}

	Geometry_Init();

	return 0;	// 諸々の初期化関数の終了(正常終了)
}

/* +++ ゲームの終了処理(ここに諸々の終了処理を集める) +++ */
void Game_End(void)
{
	DxLib_End();	// DxLibの終了

	Image_End();	// 画像処理の終了

	Font_End();		// フォント処理の終了

	Sound_End();	// サウンド処理の終了

	return;
}