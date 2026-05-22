/* === 偽のタイトルシーンのソースファイル === */

#include "FakeScene.h"
#include "GameManager.h"
#include "Color.h"
#include "Image.h"
#include "Font.h"
#include "Key.h"
#include "Message.h"
#include "Sound.h"
#include "SceneManager.h"
#include "SaveLoad.h"


/* --- 偽のタイトルシーンの初期化関数 --- */
int Fake_Init()
{
	Sound_Play(BGM_Fake);	// 偽のタイトルのBGMを再生

	return 0;	// 偽のタイトルシーンの初期化を終了(0を返す)
}

/* --- 偽のタイトルシーンの処理の管理関数 --- */
void Fake_Manage()
{
	Fake_Process();		// 偽のタイトルシーンの処理
	Fake_Draw();		// 偽のタイトルシーンの初期化

	return;
}

/* --- 偽のタイトルシーンの処理関数 --- */
void Fake_Process()
{
	// シーン切換からの時間が1秒以上経過しエンターキーが押されたら
	if (SceneChangeFrameCount >= GameFPS && Key_Check_Click(KEY_INPUT_RETURN))
	{
		NextGameScene = Select_Scene;	// 次のシーンにセレクトシーンを設定
	}

	return;
}

/* --- 偽のタイトルシーンの描画関数 --- */
void Fake_Draw()
{
	DrawExtendGraph(0, 0, GameWindowWidth + 1, GameWindowHeight + 1, FakeImageHandle, true);

	/* +++ 偽のゲームタイトルを描画 +++ */
	DrawFormatStringToHandleAlign(GameWindowWidth / 2 + 6, GameWindowHeight / 2 - 94, FAlign_AllCenter, Color_Black, MSMincho_200_9, FakeTitle);
	DrawFormatStringToHandleAlign(GameWindowWidth / 2 + 5, GameWindowHeight / 2 - 95, FAlign_AllCenter, Color_White, MSMincho_200_9, FakeTitle);
	DrawFormatStringToHandleAlign(GameWindowWidth / 2, GameWindowHeight / 2 - 100, FAlign_AllCenter, Color_Blue, MSMincho_200_9, FakeTitle);

	/* +++ 「Press Enter」を影付きで描画 +++ */
	DrawFormatStringToHandleAlign(GameWindowWidth / 2 + 4, GameWindowHeight / 2 + 104, FAlign_AllCenter, Color_Black, MSMincho_100_9, PressEnter);
	DrawFormatStringToHandleAlign(GameWindowWidth / 2 + 3, GameWindowHeight / 2 + 103, FAlign_AllCenter, Color_White, MSMincho_100_9, PressEnter);
	DrawFormatStringToHandleAlign(GameWindowWidth / 2, GameWindowHeight / 2 + 100, FAlign_AllCenter, Color_Red, MSMincho_100_9, PressEnter);


	if (GameDebug)
	{
		DrawFormatStringToHandle(0, 0, Color_Red, MSMincho_30_1, "Red ratio: %d", Counter_Red);
		DrawFormatStringToHandle(0, 30, Color_LightGreen, MSMincho_30_1, "Green ratio: %d", Counter_Green);
		DrawFormatStringToHandle(0, 60, Color_LightBlue, MSMincho_30_1, "Blue ratio: %d", Counter_Blue);
		DrawFormatStringToHandle(0, 90, Color_White, MSMincho_30_1, "Light ratio: %d", Counter_Light);
	}

	return;
}

/* --- 偽のタイトルシーンの終了関数 --- */
int Fake_End()
{
	Sound_Stop(&BGM_Fake);

	return 0;
}