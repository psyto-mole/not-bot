/* === タイトル処理のソースファイル === */

#include "GameManager.h"
#include "Color.h"
#include "Font.h"
#include "Key.h"
#include "SceneManager.h"
#include "Title.h"
#include "Message.h"
#include "Sound.h"


/* --- タイトルシーンの初期化関数 --- */
int Title_Init()
{
	Sound_Play(BGM_Title);

	return 0;	// タイトルシーンの初期化の終了(0を返す)
}

/* --- タイトルシーンの処理の管理関数 ---- */
void Title_Manage()
{
	Title_Process();	// タイトルシーンの処理
	Title_Draw();		// タイトルシーンの初期化

	return;
}

/* +++ タイトルシーンの処理関数 +++ */
void Title_Process()
{
	// シーン切換からの時間が1秒以上経過しエンターキーが押されたら
	if (SceneChangeFrameCount >= GameFPS
		&& Key_Check_Click(KEY_INPUT_RETURN))
	{
		NextGameScene = Select_Scene;	// 次のシーンにセレクトシーンを設定
	}

	return;
}

/* +++ タイトルシーンの描画関数 +++ */
void Title_Draw()
{
	/* +++ ゲームタイトルを描画 +++ */
	DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 5, GameWindowHeight / 2 - 105, FAlign_AllCenter, Color_switching_Rainbow, MSMincho_300_9, GameTitle);
	DrawFormatStringToHandleAlign(GameWindowWidth / 2 + 5, GameWindowHeight / 2 - 95, FAlign_AllCenter, Color_switching_Rainbow, MSMincho_300_9, GameTitle);
	DrawFormatStringToHandleAlign(GameWindowWidth/2,GameWindowHeight/2 - 100, FAlign_AllCenter, Color_Black, MSMincho_300_9, GameTitle);

	/* +++ 「Press Enter」を影付きで描画 +++ */
	DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 3, GameWindowHeight / 2 + 97, FAlign_AllCenter, Color_switching_Light, MSMincho_100_9, PressEnter);
	DrawFormatStringToHandleAlign(GameWindowWidth / 2 + 3, GameWindowHeight / 2 + 103, FAlign_AllCenter, Color_switching_Light, MSMincho_100_9, PressEnter);
	DrawFormatStringToHandleAlign(GameWindowWidth/2, GameWindowHeight/2 + 100, FAlign_AllCenter, Color_Black, MSMincho_100_9, PressEnter);


	if (GameDebug)
	{
		DrawFormatStringToHandle(0, 0, Color_Red, MSMincho_30_1, "Red ratio: %d", Counter_Red);
		DrawFormatStringToHandle(0, 30, Color_LightGreen, MSMincho_30_1, "Green ratio: %d", Counter_Green);
		DrawFormatStringToHandle(0, 60, Color_LightBlue, MSMincho_30_1, "Blue ratio: %d", Counter_Blue);
		DrawFormatStringToHandle(0, 90, Color_White, MSMincho_30_1, "Light ratio: %d", Counter_Light);
	}

	return;
}

/* --- タイトルシーンの終了関数-- - */
int Title_End()
{
	Sound_Stop(&BGM_Title);

	return 0;
}