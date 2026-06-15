/* === ゲームオーバー処理のソースファイル === */

#include "GameOver.h"
#include "BattleScene.h"
#include "Font.h"
#include "Color.h"
#include "Key.h"
#include "GameManager.h"
#include "Message.h"
#include "Sound.h"
#include "SaveLoad.h"


/* --- ゲームオーバーシーンの初期化関数 --- */
int GameOver_Init()
{
	Sound_Play(BGM_GameOver);

	return 0;
}

/* --- ゲームオーバーシーンの処理の管理関数 ---- */
void GameOver_Manage()
{
	GameOver_Process();		// ゲームオーバーシーンの処理
	GameOver_Draw();		// ゲームオーバーシーンの初期化

	return;
}

/* +++ ゲームオーバーシーンの処理関数 +++ */
void GameOver_Process()
{
	// シーン切換からの時間が1秒以上経過しスペースキーが押されたら
	if (SceneChangeFrameCount >= GameFPS && Key_Check_Click(KEY_INPUT_RETURN))
	{
		if (initialized)
		{
			NextGameScene = Fake_Scene;
		}
		else
		{
			NextGameScene = Title_Scene;
		}
	}

	return;
}

/* +++ ゲームオーバーシーンの描画関数 +++ */
void GameOver_Draw()
{
	DrawFormatStringToHandleAlign(GameWindowWidth/2 - 5,GameWindowHeight/2 - 105,FAlign_AllCenter,Color_Violet,MSMincho_300_9,GameOverTitle);
	DrawFormatStringToHandleAlign(GameWindowWidth/2 + 5,GameWindowHeight/2 - 95,FAlign_AllCenter,Color_Violet,MSMincho_300_9,GameOverTitle);
	DrawFormatStringToHandleAlign(GameWindowWidth/2,GameWindowHeight/2 - 100,FAlign_AllCenter,Color_Black,MSMincho_300_9,GameOverTitle);

	DrawFormatStringToHandleAlign(GameWindowWidth / 2 - 3, GameWindowHeight / 2 + 97, FAlign_AllCenter, Color_switching_Light, MSMincho_100_9, PressEnter);
	DrawFormatStringToHandleAlign(GameWindowWidth / 2 + 3, GameWindowHeight / 2 + 103, FAlign_AllCenter, Color_switching_Light, MSMincho_100_9, PressEnter);
	DrawFormatStringToHandleAlign(GameWindowWidth / 2, GameWindowHeight / 2 + 100, FAlign_AllCenter, Color_Black, MSMincho_100_9, PressEnter);

	return;
}

/* --- ゲームオーバーシーンの終了関数 --- */
int GameOver_End()
{
	Sound_Stop(&BGM_GameOver);

	return 0;
}